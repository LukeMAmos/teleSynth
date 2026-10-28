#pragma once
#include <juce_core/juce_core.h>

enum FilterTypeBiquad{
    
    lowpass,
    highpass,
    bandpass,
    bandreject
};

//Biquad Filter implementation , allows for multiple filter types depending on the coefficiensts
class BiquadFilter{
    
public:
    
    void prepare(double sampleRateIn);
    void setParameters(float cutoffFreqIn , float resonanceIn , FilterTypeBiquad filterTypeIn);
    float process(float input);
    
private:
    
    //For a biquad filter need to know maximum 2 samples prior
    float x1 = 0.0f;
    float x2 = 0.0f;

    float y1 = 0.0f;
    float y2 = 0.0f;
    
    FilterTypeBiquad filterType; //Select between lowpass and highPassFilter, flipped signs on highpassfilter
    float sampleRate;
    float cutoffFrequency; //Fc
    float resonance; //(Q)
    
    //Filter Coefficients and variables for calculating
    float a0 = 0.0f;
    float a1 = 0.0f;
    float a2 = 0.0f;
    
    float b1 = 0.0f;
    float b2 = 0.0f;
    
    float theta = 0.0f;
    
};
