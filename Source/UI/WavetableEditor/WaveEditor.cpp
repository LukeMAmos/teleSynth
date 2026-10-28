#include "WaveEditor.h"

WaveEditor::WaveEditor(){

    waveSamples.fill(0.0f);
}

void WaveEditor::paint(juce::Graphics &g){
    
    //Background and border
    
    //orange border
    g.setColour (ThemeColours::orange());
    g.drawRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f, 5.0f);
    
    //fill background with black
    g.setColour(ThemeColours::black());
    g.fillRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f);
    
    //draw a brief line to help guide user
    g.setColour(ThemeColours::grey().withBrightness(0.7f));
    g.drawLine(drawingBounds.getX(), midHeight, drawingBounds.getRight(), midHeight);
    
    //Draw the line path
    juce::PathStrokeType stroke(3.0f, juce::PathStrokeType::JointStyle::curved,juce::PathStrokeType::EndCapStyle::rounded );
    g.setColour(ThemeColours::orange());
    g.strokePath(wavePath, stroke);
    
}

void WaveEditor::resized(){
    
    drawingBounds = getLocalBounds().reduced(5);
    
    midHeight = drawingBounds.getCentreY();
    
    xIncrement = drawingBounds.getWidth() / (float)(SynthRange::wavetableSamples - 1);
    
}


void WaveEditor::mouseDown (const juce::MouseEvent& event){
    
    wavePath.clear();
    curSample = 0;
    
    previousPoint = limitDrawing(event.position, true);
    wavePath.startNewSubPath(previousPoint);
    
    //Add new sample value
    waveSamples[(size_t)curSample] = sampleNormalise(previousPoint.getY());
    curSample++;
    
    repaint();
}


void WaveEditor::mouseDrag (const juce::MouseEvent& event){
    
    auto newPoint = limitDrawing(event.position, false);
    wavePath.lineTo(newPoint);
    
    //Add new sample value if we have moved far enough along for as many are needed
    while( curSample < SynthRange::wavetableSamples && newPoint.getX() >= samplePos(curSample)){
        
        float x = samplePos(curSample);
        float t = (x - previousPoint.getX()) / (newPoint.getX() - previousPoint.getX());
        float y = previousPoint.getY() + (newPoint.getY() - previousPoint.getY()) * t;
        
        waveSamples[(size_t)curSample] = sampleNormalise(y);
        curSample++;
    }
    
    previousPoint = newPoint;
    repaint();
}


void WaveEditor::mouseUp   (const juce::MouseEvent& event){
    
    //Make line finish at the right side of screen by adding final point
    if(event.position.getX() < drawingBounds.getRight()){
        wavePath.lineTo(drawingBounds.getRight(), midHeight);
    }
    repaint();
    
    //if it hasnt been fully filled, the rest of the values need to come from the linear interpolation between the previous sample point and 0
    
    if(curSample > 0 && curSample < SynthRange::wavetableSamples){
        
        float lastSample = waveSamples[(size_t)(curSample - 1)];
        float lastPos    = samplePos(curSample - 1);
        float targetPos  = (float)drawingBounds.getRight();
        
        for(int n = curSample ; n < SynthRange::wavetableSamples ; n++){
            
            float t = (samplePos(n) - lastPos) / (targetPos - lastPos);
            waveSamples[(size_t)n] = lastSample * (1.0f - t); 
        }
    }
    
    //Reset the sampele incrementer
    curSample = 0;
    
    //Need wrap the data points and pass them through to be analysed by the mipmapping
    //We have waveSamples which are the samples we need to pass now we need a std function to call
    if(waveComplete)
        waveComplete(waveSamples);
    
}


juce::Point<float> WaveEditor::limitDrawing(juce::Point<float> drawingPoint, bool newLine){
    
    auto limX = juce::jlimit((float)drawingBounds.getX(), (float)drawingBounds.getRight(), (float)drawingPoint.getX());
    auto limY = juce::jlimit((float)drawingBounds.getY(), (float)drawingBounds.getBottom(), (float)drawingPoint.getY());
    
    //Dont return new point if its not going forward
    if(limX < previousPoint.getX() && !newLine){
        return previousPoint;
    }else if (newLine){ //If its a new line then it has to start at the minX point
        
        return {(float)drawingBounds.getX() , midHeight }; 
    }
    
    
    return {limX , limY};
}


float WaveEditor::sampleNormalise(float yPos){
    //Normalise values between -1 and 1
    float yMin = (float)drawingBounds.getY();
    float yMax = (float)drawingBounds.getBottom();
    
    return 1.0f - 2.0f * (yPos - yMin) / (yMax - yMin);
}


void WaveEditor::setWaveComplete(std::function<void(const std::array<float, SynthRange::wavetableSamples>&)> function){
    
    waveComplete = function; 
    
}

float WaveEditor::samplePos(int n) const {
    
    return drawingBounds.getX() + n * xIncrement;
    
}
