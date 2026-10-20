#pragma once


namespace SynthRange {

    //Shared variables across all synth objects
    const float freqMin = 50.0f;
    const float freqMax = 3200.0f;

    const int maxVoices = 5;
    const int wavetableSamples = 2048;
    const int fullSizeTable = wavetableSamples * 2;
    const int nMinMapTables = 6; // which is 5 octaves between 50 and 2500 hertz frequency range

    //Take normalised value and convert to frequency range
    static float normToFreq(float n){
        return freqMin * std::pow(freqMax/freqMin, n);
    }
    
    //Take the frequency of the note and calculate the table that should be used
    static int calcTableIndex(float freq){
        
        int idx = (int) std::floor(std::log2(freq / freqMin));
        return juce::jlimit(0, nMinMapTables-1 , idx); 
    }

    //Saw wave generator, taking period in number of samples
    static std::vector<float> generateSaw(int numSamples , int period){
        
        std::vector<float> wave((size_t)numSamples);
        for(int i = 0; i < numSamples; i++){
            int phase = i % period;
            wave[(size_t)i] = 2.0f * ((float)phase / (float)period) - 1.0f;
        }
        return wave;
    }

}
