#include "WaveEditor.h"

WaveEditor::WaveEditor(){
    
    drawingBounds = getBounds().reduced(5);
    
}

void WaveEditor::paint(juce::Graphics &g){
    
    //Background and border
    
    //orange border
    g.setColour (ThemeColours::orange());
    g.drawRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f, 5.0f);
    
    //fill background with black
    g.setColour(ThemeColours::black());
    g.fillRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f);
    
    
    juce::PathStrokeType stroke(3.0f, juce::PathStrokeType::JointStyle::curved,juce::PathStrokeType::EndCapStyle::rounded );
    g.setColour(ThemeColours::orange());
    g.strokePath(wavePath, stroke);
    
}

void WaveEditor::resized(){
    
    drawingBounds = getLocalBounds().reduced(5);
    
}


void WaveEditor::mouseDown (const juce::MouseEvent& event){
    
    wavePath.clear();
    
    previousPoint = limitDrawing(event.position, true);
    wavePath.startNewSubPath(previousPoint);
    
    repaint();
}


void WaveEditor::mouseDrag (const juce::MouseEvent& event){
    
    previousPoint = limitDrawing(event.position, false);
    wavePath.lineTo(previousPoint);
    
    repaint();
}


void WaveEditor::mouseUp   (const juce::MouseEvent& event){
    
    //Need wrap the data points and pass them through to be analysed by the mipmapping 
    
}


juce::Point<float> WaveEditor::limitDrawing(juce::Point<float> drawingPoint, bool newLine){
    
    auto limX = juce::jlimit((float)drawingBounds.getX(), (float)drawingBounds.getRight(), (float)drawingPoint.getX());
    auto limY = juce::jlimit((float)drawingBounds.getY(), (float)drawingBounds.getBottom(), (float)drawingPoint.getY());
    
    //Dont return new point if its not going forward
    if(limX < previousPoint.getX() && !newLine){
        return previousPoint;
    }
    return {limX , limY};
}
