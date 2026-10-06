#include "adsrSlider.h"


AdsrSlider::AdsrSlider(){

    //Add all the points and make them visible
    for(auto& point : AdsrPoints){
        addAndMakeVisible(point);
        point.setInterceptsMouseClicks(false, false);
    }
    
}

void AdsrSlider::paint(juce::Graphics& g){
    
    //black border with grey centre 
    auto bounds = getLocalBounds().reduced(5).toFloat();
    g.setColour(ThemeColours::black());
    g.fillRoundedRectangle(bounds, 8);
    
    //draw all the dots and lines between them
    g.setColour(ThemeColours::orange());
    //From bottom corner to attack
    g.drawLine(getX(), getBottom(), AdsrPoints[0].getX(), AdsrPoints[0].getX());
    
    for(int point = 0 ; point < 4 ; point++){
        
        g.drawLine(AdsrPoints[point].getX(), AdsrPoints[point].getX(), AdsrPoints[point + 1].getX(), AdsrPoints[point + 1 ].getX());
    }
    
    
}


void AdsrSlider::resized(){
    
    auto yMiddle = (getHeight()/2.0f);
    auto xStart = getX()+10;
    
    for(auto& point : AdsrPoints){
        point.setBounds(xStart, yMiddle, 20, 20);
        xStart = xStart + 15;
    }

}

void AdsrSlider::mouseDown (const juce::MouseEvent& event){
    
    //Where was the press? was it within 10 pixels of a point if so we set that points move to true and move with drag 
    auto pressX = event.getMouseDownX();
    auto pressY = event.getMouseDownY();
    
    //Check its within 10 pixels of any dot
    
    for(auto& point: AdsrPoints){
        
        auto dx = pressX - point.getX();
        auto dy = pressY - point.getY();
        
        if((dx*dx) + (dy*dy) <=150){
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
            
            int radius = (int)(point.getDiameter() / 2.0f);
            //Bound the point inside the DraggableZone, the minimum it can go is the radius of the circle the max is the width minus the radius in both up and down direction
            juce::Point<int> boundedPos = event.getPosition();
            //Margins for positioning the ADSR slider points correctly
            const int margin = radius + 5;
            const int topY = margin;
            const int bottomY = getHeight() - margin;
            
            //Lambda Functions for getting the centre of a specific point
            std::function<int(int i)> getXAt = [this](int i){return AdsrPoints[i].getBounds().getCentreX(); };
            std::function<int(int i)> getYAt = [this](int i){return AdsrPoints[i].getBounds().getCentreY(); };
            
            switch (point.getStage()) {
                    
                    //Bound so it cant go lower than the corner or further than decay
                case Attack:
                {
                    int maxX = juce::jmax(margin, getXAt(1) - (radius * 2)); //work out the furtherest right the attack point can go, this pre-jmax ensures that the next jlimit always has a smaller then larger number
                    point.setCentrePosition(juce::jlimit(margin, maxX, boundedPos.getX()), topY);
                    break;
                }
                    //Bound so cant go less than attack , cant go past release, Y position is equal to sustain
                case Decay:
                {
                    int minX = getXAt(0) + 1;
                    int maxX = juce::jmax(minX , getXAt(2) + 1 );
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
    
    
}

void AdsrSlider::mouseUp   (const juce::MouseEvent& event){
    
    //After mouse up need to reset all the point down boolean values to false to stop unwanted dragging
    //Also need to update the ADSR params, within the synthesiser
    
    for(auto& point : AdsrPoints){
        
        //set all points to false
        point.setShouldBeMoved(false);
    }
}
