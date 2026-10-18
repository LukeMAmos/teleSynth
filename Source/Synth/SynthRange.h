#pragma once


namespace SynthRange {

    const float freqMin = 50.0f;
    const float freqMax = 2500.0f;
    
    static float normToFreq(float n){        
        return freqMin * std::pow(freqMax/freqMin, n);
    }

}
