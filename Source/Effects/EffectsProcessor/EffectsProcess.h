#pragma once
#include <JuceHeader.h>
#include "Filter/BiquadFilter.h"

//Class for processing the synths built in effects
//Effects, Reverb, Distortion, Biquad Filter
class EffectsProcessor{
    
public:
    
    void processEffects(juce::AudioBuffer<float>& buffer); 
    
private:
    
    //Effects Objects
    juce::Reverb reverb;
    
};
