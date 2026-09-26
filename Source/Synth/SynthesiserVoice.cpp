#include "SynthesiserVoice.h"


SliderSynthVoice::SliderSynthVoice(){
    
    OSC.initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }); 
    
}

void SliderSynthVoice::initaliseVoice(double sampleRate , int samplesPerBlock , int numChannels){
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = (juce::uint32)samplesPerBlock;
    spec.numChannels = (juce::uint32)numChannels;
    
    OSC.prepare(spec);
    ADSR.setSampleRate(spec.sampleRate);
}


void SliderSynthVoice::startNote(float freqeuncy, float velocity){
    
    OSC.setFrequency(freqeuncy);
    ADSR.noteOn();
}

void SliderSynthVoice::stopNote(){
    
    ADSR.noteOff();
    
}

void SliderSynthVoice::updateValues(float frequency , float velocity){
    
    //Save the values and set the update flag to true
    valueUpdateNeeded = true;
    xValueSlider = velocity;
    yValueSlider = frequency;
}

void SliderSynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples){
    
    juce::ScopedNoDenormals noDenormals;
    
    //update the values before they are used to render the next audio block
    if(valueUpdateNeeded){
        OSC.setFrequency(yValueSlider);
        valueUpdateNeeded = false; 
    }
    
    
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
