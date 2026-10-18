#pragma once


namespace SynthRange {

    const float freqMin = 50.0f;
    const float freqMax = 2500.0f;
    
    float normToFreq(float n){        
        return fMin * std::pow(fMax/fMin, n);
    }

}
