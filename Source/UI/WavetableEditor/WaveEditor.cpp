#include "WaveEditor.h"

WaveEditor::WaveEditor(){
    
    
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
    wavePath.startNewSubPath(event.position);
    
    repaint();
}


void WaveEditor::mouseDrag (const juce::MouseEvent& event){
    
    wavePath.lineTo(event.position);
    
    repaint();
}


void WaveEditor::mouseUp   (const juce::MouseEvent& event){
    
    
}
