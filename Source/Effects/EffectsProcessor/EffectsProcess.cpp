#include "EffectsProcess.h"


void EffectsProcessor::processEffects(juce::AudioBuffer<float>& buffer){
    //Pass the buffer through the effects processing
    
    juce::ScopedNoDenormals noDenormals;
    
    //Max num channels is two
    for(int ch = 0 ; ch < juce::jmin((int)buffer.getNumChannels() , 2 ); ch++){
        
        for(int s = 0; s < buffer.getNumSamples() ; s++){
            
            //Process biquad filter and then set sample
            buffer.setSample(ch, s, biquadFilters[ch].process(buffer.getSample(ch, s)));
        }
    }
}

void EffectsProcessor::prepare(double sampleRateIn){
    
    reverb.setSampleRate(sampleRateIn);
    for(auto& filter : biquadFilters)
        filter.prepare(sampleRateIn);
    
}



void EffectsProcessor::setLinearEffectControl(float sliderValue){
    //Slider value is a value from 0 to 1,
    //Need to save which effect was last recently clicked because thats what we need to update with this slider
    
    float cutoffValue = 20.0f * std::pow(1000.0f, sliderValue);
    
    for(auto& filter : biquadFilters)
        filter.setCutoff(cutoffValue);
}

