#include "SynthesiserVoice.h"


SliderSynthVoice::SliderSynthVoice(){
    
    
    
}

void SliderSynthVoice::startNote(float freqeuncy, float velocity){
    
    
    
}

void SliderSynthVoice::stopNote(){
    
    
    
}

void SliderSynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples){
    
    juce::ScopedNoDenormals noDenormals;
    
    juce::dsp::AudioBlock<float> block(outputBuffer);
    auto subBlock = block.getSubBlock(0, (size_t)numSamples);
    juce::dsp::ProcessContextReplacing<float> context(subBlock);
    
    OSC.process(context);
    ADSR.applyEnvelopeToBuffer(outputBuffer, 0, numSamples);
        
}

void SliderSynthVoice::updateOSCWavetable(){
    
    
    
}

void SliderSynthVoice::setADSR(juce::ADSR::Parameters adsrParamsIn){
    
    adsrParams = adsrParamsIn;
    
    ADSR.setParameters(adsrParams); 
    
}

bool SliderSynthVoice::isActive(){
    //if the ADSR is not active then the voice is fine to be freed up and used by a different touch
    return ADSR.isActive();
}
