#pragma once
#include <JuceHeader.h>
#include "Filter/BiquadFilter.h"

//Class for processing the synths built in effects
//Effects, Reverb, Distortion, Biquad Filter
class EffectsProcessor{
    
public:
    
    void prepare(double sampleRateIn);
    
    void processEffects(juce::AudioBuffer<float>& buffer);
    
    void setParameters();
    
private:
    
    //Effects Objects
    juce::Reverb reverb;
    BiquadFilter biquadFilter; 
    
    
};
