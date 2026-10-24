#pragma once
#include "juce_gui_basics/juce_gui_basics.h"
#include "ThemeColours.h"

//Waveform viewer takes in a number of samples and displays them in a custom component using lines to indicate the amplitude
class WaveformViewer : public juce::Component{
    
public:
    
    WaveformViewer();
    
    void paint(juce::Graphics& g )override;
    void resized() override;
    
    void setSamples(const float* data , int numSamples);
    
private:
    
    std::vector<float> displaySamples;
    
    //take the sample value and then calculate the height of the line in pixels
    int sampleToLength(float sample); 
};
