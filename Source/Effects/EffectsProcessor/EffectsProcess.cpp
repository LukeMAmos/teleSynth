#include "EffectsProcess.h"


void EffectsProcessor::processEffects(juce::AudioBuffer<float>& buffer){
    //Pass the buffer through the effects processing
    
}

void EffectsProcessor::prepare(double sampleRateIn){
    
    reverb.setSampleRate(sampleRateIn);
    biquadFilter.prepare(sampleRateIn);
    
}



void EffectsProcessor::setParameters(){
    
    
}
