#include "SynthesiserVoice.h"


SliderSynthVoice::SliderSynthVoice(){
    
    
}

void SliderSynthVoice::initaliseVoice(double sampleRate , int samplesPerBlock , int numChannels){
    
    
    this->sampleRate = sampleRate;
    //Prepare spec to setup JUCE DSP Objects
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = (juce::uint32)samplesPerBlock;
    spec.numChannels = (juce::uint32)numChannels;
    
    
    ADSR.setSampleRate(spec.sampleRate);
    
}


void SliderSynthVoice::startNote(float freqeuncy, float velocity){
    
    phase = 0.0;
    targetFreq = freqeuncy;
    targetVelocity = velocity;
    valueUpdateNeeded = true;
    ADSR.noteOn();
}

void SliderSynthVoice::stopNote(){
    
    ADSR.noteOff();
}

void SliderSynthVoice::updateValues(float frequency , float velocity){
    
    //Save the values and set the update flag to true
    valueUpdateNeeded = true;
    targetVelocity = velocity;
    targetFreq = frequency;
}

void SliderSynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples){
    
    juce::ScopedNoDenormals noDenormals;
    
    //Stop rendering if there are no current minmaps computed
    const SynthRange::Tables* tables = SynthRange::liveTable.load(std::memory_order_acquire);
    if(tables == nullptr)
        return;
    //update the values before they are used to render the next audio block
    //If Values need updating, otherwise skip block
    if(valueUpdateNeeded){
        currentTable = SynthRange::calcTableIndex(targetFreq.load()); //Calculate the table needed based on the current frequency playing
        valueUpdateNeeded = false;
        phaseIncre = ((targetFreq.load() * SynthRange::wavetableSamples) / (sampleRate)); 
    }
    //For each of the samples by interpolating between the sample positions
    auto* channelOne = outputBuffer.getWritePointer(0);
    
    for(int i = startSample; i < startSample + numSamples; i++ ){
        
        
        //Hermite interpolation
        channelOne[i] = SynthRange::hermiteInterpolation(phase, (*tables)[(size_t)currentTable]);
        
        //Increment phase
        phase += phaseIncre;
        if(phase >= SynthRange::wavetableSamples)
            phase -= SynthRange::wavetableSamples;
    }
    
    //Send signal to each channel equally 
    for(int ch = 1; ch < outputBuffer.getNumChannels() ; ch++)
        outputBuffer.copyFrom(ch , startSample , outputBuffer ,0 , startSample , numSamples );
    
    ADSR.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    outputBuffer.applyGain(targetVelocity); 
}

void SliderSynthVoice::setADSR(juce::ADSR::Parameters adsrParamsIn){
    
    adsrParams = adsrParamsIn;
    
    ADSR.setParameters(adsrParams); 
    
}

bool SliderSynthVoice::isActive(){
    //if the ADSR is not active then the voice is fine to be freed up and used by a different touch
    return ADSR.isActive();
}


