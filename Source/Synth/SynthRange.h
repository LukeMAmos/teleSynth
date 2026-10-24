#pragma once


namespace SynthRange {
    
    
    //Shared variables across all synth objects
    const float freqMin = 50.0f;
    const float freqMax = 3200.0f;

    const int maxVoices = 5;
    const int wavetableSamples = 2048;
    const int fullSizeTable = wavetableSamples * 2;
    const int nMinMapTables = 6; // which is 5 octaves between 50 and 2500 hertz frequency range

    using Tables = std::array<std::array<float , wavetableSamples>, nMinMapTables>;

    //Final Samples, using two tables so that switching can happen whilst keeping the audio playing
    inline Tables tablesA{} , tablesB{};
    inline std::atomic<const Tables*> liveTable {nullptr}; 

    //Take normalised value and convert to frequency range
    inline float normToFreq(float n){
        return freqMin * std::pow(freqMax/freqMin, n);
    }
    
    //Take the frequency of the note and calculate the table that should be used
    inline int calcTableIndex(float freq){
        
        int idx = (int) std::floor(std::log2(freq / freqMin));
        return juce::jlimit(0, nMinMapTables-1 , idx); 
    }

    //Saw wave generator, taking period in number of samples
    inline std::vector<float> generateSaw(int numSamples , int period){
        
        std::vector<float> wave((size_t)numSamples);
        for(int i = 0; i < numSamples; i++){
            int phase = i % period;
            wave[(size_t)i] = 2.0f * ((float)phase / (float)period) - 1.0f;
        }
        return wave;
    }

    //Position is a value ranging from 0 to wavetable Samples, the current phase
    inline float hermiteInterpolation(double position, const std::array<float, wavetableSamples>& table){
        float sampleValue = 0.0f;
        
        //The lower int position and the fractional position after
        size_t x0 = (size_t)std::floor(position);
        size_t xm1 = ((size_t)(x0 + wavetableSamples - 1) % wavetableSamples);
        size_t x1 = ((size_t)(x0 + 1) % wavetableSamples);
        size_t x2 = ((size_t)(x0 + 2) % wavetableSamples);
        
        float d = (float)position - (float)x0;
        
        //Coefficent values
        float c0 = table[x0];
        float c1 = 0.5f * (table[x1] - table[xm1]);
        float c2 = table[xm1] - 2.5f * table[x0] + 2.0f * table[x1] - 0.5f * table[x2];
        float c3 = 0.5f * (table[x2] - table[xm1]) + 1.5f * (table[x0] -table[x1]);
        
        sampleValue = ((c3 * d + c2) * d + c1) * d + c0;
        return sampleValue;
    }

}
