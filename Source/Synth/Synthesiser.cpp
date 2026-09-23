#include "Synthesiser.h"

void SliderSynthesiser::startNote(float frequency, float velocity , int touch){
    
    //find a free voice , then use the position of the free voice to call start note on the voice 
    int freeVoice = findFreeVoice();
    if(freeVoice < 0 || freeVoice > maxVoices )
        return;
    
    sliderVoices[freeVoice].startNote(frequency, velocity);
    
    //Also update the voiceToTouch variable to keep track of which voices are being called by which touch
    voiceToTouch[freeVoice] = touch;
    
}

void SliderSynthesiser::stopNote(int touch){
    
    //Call the stop note on the specific touch, dont free the voice here as the release stage may still be active
    
    int voice = -1;
    for(int i = 0; i < maxVoices ; i++){
        
        if(voiceToTouch[i] == touch){
            //Find the voice we need to release
            voice = i;
        }
    }
    //If no voice matches the touch then release
    if(voice == -1)
        return;
    
    //Call the voice to stopNote
    sliderVoices[voice].stopNote();
}

//Go through each of the voices and combine the output, after combining effects can be processed 
void SliderSynthesiser::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples){
    
    juce::ScopedNoDenormals noDenormals;
    
    
    
    
    
}

//Set the ADSR on each of the voices
void SliderSynthesiser::setADSR(juce::ADSR::Parameters adsrParams){
    
    for(int i = 0; i < maxVoices ; i++){
        
        sliderVoices[i].setADSR(adsrParams); 
    }
    
}


//Set the wavetable osc
void SliderSynthesiser::setOSCWavetable(){
    
    
    
}


int SliderSynthesiser::findFreeVoice(){
    
    for(int i = 0; i < maxVoices ; i++){
        
        if(!sliderVoices[i].isActive()){
            //if the voice is inactive then return i
            return i;
        }
    }
    
    //If no voices are available return minus 1
    return -1;
}

