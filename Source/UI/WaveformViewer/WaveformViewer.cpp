#include "WaveformViewer.h"

WaveformViewer::WaveformViewer(){
    
    
}

void WaveformViewer::paint(juce::Graphics& g ){
    
    //orange border 
    g.setColour (ThemeColours::orange());
    g.drawRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f, 5.0f);
    
    //fill background with black
    g.setColour(ThemeColours::black());
    g.fillRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f);
    
    
}

void WaveformViewer::resized(){
    
    
    
}

void WaveformViewer::setSamples(juce::AudioBuffer<float> &buffer){
    
    displaySamples = buffer;
}
