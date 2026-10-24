#include "WaveformViewer.h"

WaveformViewer::WaveformViewer(){
    
    
}

void WaveformViewer::paint(juce::Graphics& g ){
    
    g.setColour (ThemeColours::black());
    g.drawRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f, 5.0f);
    
    //fill background with grey
    g.setColour(ThemeColours::grey());
    g.fillRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f);
    
    
}

void WaveformViewer::resized(){
    
    
    
}
