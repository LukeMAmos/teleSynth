#include "Synthesiser.h"

void SliderSynthesiser::startNote(float frequency, float velocity , int touch){
    
    //find a free voice , then use the position of the free voice to call start note on the voice 
    
    
}

void SliderSynthesiser::stopNote(int touch){
    
    
    
}

//Go through each of the voices and combine the ou
void SliderSynthesiser::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples){
    
    
    
    
}

//Set the ADSR on each of the voices
void SliderSynthesiser::setADSR(juce::ADSR::Parameters adsrParams){
    
    
    
}


//Set the wavetable osc
void SliderSynthesiser::setOSCWavetable(){
    
    
    
}


int SliderSynthesiser::findFreeVoice(){
    
    
    return 0;
}
