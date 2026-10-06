#include "adsrSlider.h"


AdsrSlider::AdsrSlider(){

    //Add all the points and make them visible
    for(auto& point : AdsrPoints){
        addAndMakeVisible(point);
        point.setInterceptsMouseClicks(false, false);
        point.setSize(16, 16);
    }
    
    radius = (int)(AdsrPoints[0].getDiameter() / 2.0f);
    margin = radius + 5;
    topY = margin;
    leftX = margin;
    
}

void AdsrSlider::paint(juce::Graphics& g){
    
    //black border with grey centre 
    auto bounds = getLocalBounds().reduced(inset).toFloat();
    g.setColour(ThemeColours::black());
    g.fillRoundedRectangle(bounds, 8);
    
    //draw all the dots and lines between them
    g.setColour(ThemeColours::orange());
    
    auto centrePoint = [this](int i ){return AdsrPoints[i].getBounds().getCentre().toFloat();};//lambda for getting the centre of a point
    //From bottom corner to attack
    juce::Point<float> start(leftX, bottomY);
    g.drawLine(juce::Line<float>(start , centrePoint(0)), 2.0f);
    
    for(int point = 0 ; point < 3 ; point++){
        g.drawLine(juce::Line<float>(centrePoint(point), centrePoint(point+1)), 2.0f);
    }
    
    
}


void AdsrSlider::resized(){
    
    radius  = (int)(AdsrPoints[0].getDiameter() / 2.0f);
    margin  = radius + inset;
    leftX   = margin;
    rightX  = getWidth() - margin;
    topY    = margin;
    bottomY = getHeight() - margin;
    midY    = getHeight() / 2;
    usable  = rightX - leftX;
    
    //Set the correct positions for all of the points
    AdsrPoints[0].setCentrePosition(margin + (int)(usable * 0.2f), topY);
    AdsrPoints[1].setCentrePosition(margin+ (int)(usable * 0.4f), midY);
    AdsrPoints[2].setCentrePosition(margin + (int)(usable * 0.7f), midY);
    AdsrPoints[3].setCentrePosition(getWidth()-margin, bottomY);

}

void AdsrSlider::mouseDown (const juce::MouseEvent& event){
    
    //Where was the press? was it within 10 pixels of a point if so we set that points move to true and move with drag 
    auto pressX = event.getMouseDownX();
    auto pressY = event.getMouseDownY();
    

    //Check its within 25 pixels of any dot
    
    for(auto& point: AdsrPoints){
        
        auto centre = point.getBounds().getCentre();
        auto dx = pressX - centre.x;
        auto dy = pressY - centre.y;
        
        if((dx*dx) + (dy*dy) <=250){
            //target pressed
            point.setShouldBeMoved(true);
            //Once found the right point leave this function 
            return;
        }
        
    }
    
}

void AdsrSlider::mouseDrag (const juce::MouseEvent& event){
    
    //set the x and y positions of the dot so that thye move with teh mouseDrag, it needs to be bounded within its specifc bounds 
    for(auto& point: AdsrPoints){
        
        //if the point should be the point getting moved right now, then follow the mouse drag
        if(point.getShouldBeMoved()){
            
            //Bound the point inside the DraggableZone, the minimum it can go is the radius of the circle the max is the width minus the radius in both up and down direction
            juce::Point<int> boundedPos = event.getPosition();
            //Margins for positioning the ADSR slider points correctly
            
            //Lambda Functions for getting the centre of a specific point
            std::function<int(int i)> getXAt = [this](int i){return AdsrPoints[i].getBounds().getCentreX(); };
            std::function<int(int i)> getYAt = [this](int i){return AdsrPoints[i].getBounds().getCentreY(); };
            
            switch (point.getStage()) {
                    
                    //Bound so it cant go lower than the corner or further than decay
                case Attack:
                {
                    int maxX = juce::jmax(leftX, getXAt(1) - (radius * 2)); //work out the furtherest right the attack point can go, this pre-jmax ensures that the next jlimit always has a smaller then larger number
                    point.setCentrePosition(juce::jlimit(leftX, maxX, boundedPos.getX()), topY);
                    break;
                }
                    //Bound so cant go less than attack , cant go past release, Y position is equal to sustain
                case Decay:
                {
                    int minX = getXAt(0) + 1;
                    int maxX = juce::jmax(minX , getXAt(2) - 1 );
                    point.setCentrePosition(juce::jlimit(minX, maxX, boundedPos.getX()), getYAt(2));
                    break;
                }
                    //Bound so its Y is equal to decay, these need to be linked, cannont be less than decay or more than attack
                case Sustain:
                {
                    int minX = getXAt(1) + 1; // X at Decay
                    int maxX = juce::jmax(minX , getXAt(3) -1 ); //whichever is larger X at decay or X at attack
                    int newY = juce::jlimit(topY, bottomY, boundedPos.getY());
                    
                    point.setCentrePosition(juce::jlimit(minX, maxX, boundedPos.getX()), newY);
                    AdsrPoints[1].setCentrePosition(getXAt(1), newY);
                    break;
                }
                    //Bound so that its Y position is always at the bottom of the adsr slider , and its furtherst X positon cant go beyond the wall
                case Release:
                {
                    int minX = getXAt(2) + 1;
                    int maxX = juce::jmax(minX , getWidth() - margin);
                    point.setCentrePosition(juce::jlimit(minX, maxX, boundedPos.getX()), bottomY);
                    break;
                }
                    
                default:
                    break;
            }
        }
        
    }
    repaint();
    
}

void AdsrSlider::mouseUp   (const juce::MouseEvent& event){
    
    //After mouse up need to reset all the point down boolean values to false to stop unwanted dragging
    //Also need to update the ADSR params, within the synthesiser
    
    for(auto& point : AdsrPoints){
        
        if(point.getShouldBeMoved()){
            //if there was a movement
            callOnChange(getADSRParameters());
        }
        
        //set all points to false
        point.setShouldBeMoved(false);
    }
}

juce::ADSR::Parameters AdsrSlider::getADSRParameters(){
    
    juce::ADSR::Parameters AdsrParams;
    AdsrParams.attack = getAttack();
    AdsrParams.decay = getDecay();
    AdsrParams.sustain = getSustain();
    AdsrParams.release = getRelease();

    return AdsrParams; 
}


//Helper functions used by the getADSRParameters function

float AdsrSlider::getAttack(){
    float attack = 0.15f;
    //Attack is the distance between start and attack point
    auto pixelDif = AdsrPoints[0].getBounds().getCentreX() - leftX;
    attack = pixelsToTime(pixelDif, 0.1f, 6.0f);
    return attack;
}

float AdsrSlider::getDecay(){
    float decay = 0.0f;
    
    //difference between attack and decay
    auto pixelDif = (AdsrPoints[1].getBounds().getCentreX())-(AdsrPoints[0].getBounds().getCentreX());
    decay = pixelsToTime(pixelDif, 0.01f, 4.0f);
    return decay;
}

float AdsrSlider::getSustain(){
    float sustain = 0.1f;
    //y height from bottom
    sustain = juce::jmap((float)AdsrPoints[2].getBounds().getCentreY(), (float)bottomY, (float)topY, 0.01f, 1.0f);
    return sustain;
}

float AdsrSlider::getRelease(){
    float release = 0.0f;
    //distance between sustain and release
    auto pixelDif = AdsrPoints[3].getBounds().getCentreX() - AdsrPoints[2].getBounds().getCentreX(); 
    release = pixelsToTime(pixelDif, 0.15f, 6.0f);
    return release;
}



float AdsrSlider::pixelsToTime(float pixels, float minSeconds , float maxSeconds){
    
    float time =juce::jlimit(0.0f, 1.0f, pixels / (float)juce::jmax(1 , usable)); //Normalises the range to 0 to 1
    time = time * time;
    
    return juce::jmap(time , minSeconds , maxSeconds);
}

void AdsrSlider::setCallOnChange(std::function<void (juce::ADSR::Parameters)> function){
    
    callOnChange = function;
}
