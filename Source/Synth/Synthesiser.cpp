#include "Synthesiser.h"

SliderSynthesiser::SliderSynthesiser(){
    
    std::fill(std::begin(voiceToTouch), std::end(voiceToTouch), -1);
    
    juce::ADSR::Parameters adsrParams;
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.2f;
    adsrParams.sustain = 0.6f;
    adsrParams.release = 0.5f;
    setADSR(adsrParams);
    

}

void SliderSynthesiser::initaliseVoices(double sampleRate , int samplesPerBlock , int numChannels){
    
    for(auto& voice : sliderVoices){
        
        voice.initaliseVoice(sampleRate, samplesPerBlock, numChannels); 
        
    }
    
    this->sampleRate = sampleRate;
}
void SliderSynthesiser::startNote(float frequency, float velocity , int touch){
    
    //find a free voice , then use the position of the free voice to call start note on the voice 
    int freeVoice = findFreeVoice();
    if(freeVoice < 0 || freeVoice > maxVoices )
        //No free voices available 
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
            //Call the voice to stopNote
            sliderVoices[i].stopNote();
            voiceToTouch[i] = -1;
        }
    }

    //If no voice matches the touch then return
    if(voice == -1)
        return;
    

}

void SliderSynthesiser::updateValues(float frequency, float velocity, int touch){
    
    for(int voice = 0; voice < maxVoices ; voice++ ){
        
        if(voiceToTouch[voice] == touch){
            //Found the correct voice now need to call to update the specific values of that voice
            sliderVoices[voice].updateValues(frequency, velocity); 
        }
        
    }
    
    
}

//Go through each of the voices and combine the output, after combining effects can be processed
void SliderSynthesiser::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples){
    
    juce::ScopedNoDenormals noDenormals;
    
    juce::AudioBuffer<float> tempBuffer(outputBuffer.getNumChannels() , numSamples);
    
    for(int voice = 0 ; voice < maxVoices ; voice++){
        
        if(sliderVoices[voice].isActive()){
            
            //DBG("Currently playing" + juce::String(voice));
            
            tempBuffer.clear();
            sliderVoices[voice].renderNextBlock(tempBuffer, startSample, numSamples);
            
            for(int i = 0; i < outputBuffer.getNumChannels() ; i++){
                
                outputBuffer.addFrom(i, startSample, tempBuffer, i, 0, numSamples);
            }
        }
    }
    
    
    
}

//Set the ADSR on each of the voices
void SliderSynthesiser::setADSR(juce::ADSR::Parameters adsrParams){
    
    for(int i = 0; i < maxVoices ; i++){
        
        sliderVoices[i].setADSR(adsrParams); 
    }
    
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

//Setting up the Oscillator
void SliderSynthesiser::setWavetableSamples(std::vector<float> samples){
    
    if(samples.size() < 2048)
        return;
    
    //If the vector of samples is greater than 2048 only take the first 2048 samples
    std::copy_n(samples.begin(), 2048, fullSizeWavetableSamples.begin());
    
}

//Calls the private FFT functions and fills the array of mipmap tables
void SliderSynthesiser::setAllMipmapTables(){
    
    //Calls the forwardFFT saves the result to results array
    forwardFFTResults = computeForwardFFT(fullSizeWavetableSamples);
    
    //Then take the results and compute an inverse for each octave
    for(int table = 0; table < nMinMapTables; table++){
        //So for each table need to calculate the max frequency inside the octave, then use this to bandlimit the inverse FFT
        float highestFreq;
        
        minMapTables[(size_t)table] = computeInverseFFT(forwardFFTResults, highestFreq);
    }
    
}

//This doesnt replace the data you input it takes a copy which you can save
std::array<float ,SliderSynthesiser::fullSizeTable> SliderSynthesiser::computeForwardFFT(std::array<float, SliderSynthesiser::fullSizeTable > wavetable){
    
    //Takes the input wavetable array and returns the wavetable after the FFT has been applied to it , as an array of floats
    fft.performRealOnlyForwardTransform(wavetable.data());
    
    return wavetable; 
}

std::array<float, SliderSynthesiser::wavetableSamples> SliderSynthesiser::computeInverseFFT(std::array<float, SliderSynthesiser::fullSizeTable> wavetable , float highestFundamentalFreq){
    
    //Takes the result of the computeForwardFFT as a copy each time and then  computes the inverse FFT after zeroing the bins after the cutoff frequencey point
    //Calculate the max_harmonic
    int maxHarmonic = (int)std::floor(sampleRate / (2 * highestFundamentalFreq));
    
    //Calculate the bin position to start cutting off at and zero those bins
    int binZeroStart = maxHarmonic + 1 ;
    std::fill(wavetable.begin() + binZeroStart, wavetable.end(), 0);
    
    //Take the wavetable and perform the inverse FFT
    fft.performRealOnlyInverseTransform(wavetable.data());
    
    //Trim the first 2048 float values and return
    std::array<float, wavetableSamples> returnVal;
    std::copy_n(wavetable.begin() , wavetableSamples , returnVal.begin());
    
    return returnVal;
}



