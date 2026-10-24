#include "Synthesiser.h"

SliderSynthesiser::SliderSynthesiser(){
    
    std::fill(std::begin(voiceToTouch), std::end(voiceToTouch), -1);
    
    //ADSR Paramters INIT
    juce::ADSR::Parameters adsrParams;
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.2f;
    adsrParams.sustain = 0.6f;
    adsrParams.release = 0.5f;
    setADSR(adsrParams);
    
    //Fill on initalisation with a saw Wave
    auto generatedWave = SynthRange::generateSaw(SynthRange::wavetableSamples, (int)(SynthRange::wavetableSamples));
    std::copy(generatedWave.begin(), generatedWave.end(), fullSizeWavetableSamples.begin());
}

void SliderSynthesiser::initaliseVoices(double sampleRateIn , int samplesPerBlock , int numChannels){
    
    tempBuffer.setSize(numChannels, samplesPerBlock);
    
    this->sampleRate = sampleRateIn;
    
    for(auto& voice : sliderVoices){
        
        voice.initaliseVoice(sampleRate, samplesPerBlock, numChannels);
    }
    //Initalised the wave to be a saw wave and now need to compute the mipmap waves
    setAllMipmapTables();
    
}
void SliderSynthesiser::startNote(float frequency, float velocity , int touch){
    
    //find a free voice , then use the position of the free voice to call start note on the voice 
    int freeVoice = findFreeVoice();
    if(freeVoice < 0 || freeVoice >= SynthRange::maxVoices )
        //No free voices available 
        return;
    
    sliderVoices[freeVoice].startNote(frequency, velocity);
    
    //Also update the voiceToTouch variable to keep track of which voices are being called by which touch
    voiceToTouch[freeVoice] = touch;
    
}

void SliderSynthesiser::stopNote(int touch){
    
    //Call the stop note on the specific touch, dont free the voice here as the release stage may still be active
    int voice = -1;
    for(int i = 0; i < SynthRange::maxVoices ; i++){
        
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
    
    for(int voice = 0; voice < SynthRange::maxVoices ; voice++ ){
        
        if(voiceToTouch[voice] == touch){
            //Found the correct voice now need to call to update the specific values of that voice
            sliderVoices[voice].updateValues(frequency, velocity); 
        }
        
    }
    
    
}

//Go through each of the voices and combine the output, after combining effects can be processed
void SliderSynthesiser::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples){
    
    juce::ScopedNoDenormals noDenormals;
    
    
    for(int voice = 0 ; voice < SynthRange::maxVoices ; voice++){
        
        if(sliderVoices[voice].isActive()){
            
            
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
    
    for(int i = 0; i < SynthRange::maxVoices ; i++){
        
        sliderVoices[i].setADSR(adsrParams); 
    }
    
}


int SliderSynthesiser::findFreeVoice(){
    
    for(int i = 0; i < SynthRange::maxVoices ; i++){
        
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
    
    const SynthRange::Tables* live = SynthRange::liveTable.load(std::memory_order_acquire);
    SynthRange::Tables& spare = (live == &SynthRange::tablesA) ? SynthRange::tablesB : SynthRange::tablesA; //Find the spare table
    
    //Then take the results and compute an inverse for each octave
    for(int table = 0; table < SynthRange::nMinMapTables; table++){
        //So for each table need to calculate the max frequency inside the octave, then use this to bandlimit the inverse FFT
        float highestFreq = (SynthRange::freqMin) * std::pow(2.0f, (float)(table + 1));
        
        spare[(size_t)table] = computeInverseFFT(forwardFFTResults, highestFreq);
    }
    //and then store the data
    SynthRange::liveTable.store(&spare , std::memory_order_release); 
    
}




//__Used by the set all mipmapTables function__

//This doesnt replace the data you input it takes a copy which you can save
std::array<float ,SynthRange::fullSizeTable> SliderSynthesiser::computeForwardFFT(std::array<float, SynthRange::fullSizeTable > wavetable){
    
    //Takes the input wavetable array and returns the wavetable after the FFT has been applied to it , as an array of floats
    fft.performRealOnlyForwardTransform(wavetable.data());
    
    return wavetable; 
}

std::array<float, SynthRange::wavetableSamples> SliderSynthesiser::computeInverseFFT(std::array<float, SynthRange::fullSizeTable> wavetable , float highestFundamentalFreq){
    
    //Takes the result of the computeForwardFFT as a copy each time and then  computes the inverse FFT after zeroing the bins after the cutoff frequencey point
    //Calculate the max_harmonic
    int maxHarmonic = (int)std::floor(sampleRate / (2 * highestFundamentalFreq));
    
    //Calculate the bin position to start cutting off at and zero those bins
    int binZeroStart = (maxHarmonic + 1) * 2 ;
    std::fill(wavetable.begin() + binZeroStart, wavetable.end(), 0);
    
    //Take the wavetable and perform the inverse FFT
    fft.performRealOnlyInverseTransform(wavetable.data());
    
    //Trim the first 2048 float values and return
    std::array<float, SynthRange::wavetableSamples> returnVal;
    std::copy_n(wavetable.begin() , SynthRange::wavetableSamples , returnVal.begin());
    
    return returnVal;
}



