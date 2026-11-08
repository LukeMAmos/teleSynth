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
    void setParameters(double cutoffFreqIn , double resonanceIn , FilterTypeBiquad filterTypeIn);
    float process(float input);
    
    void setCutoff(float cutoffFreqIn); 
private:
    
    //For a biquad filter need to know maximum 2 samples prior
    float x1 = 0.0f;
    float x2 = 0.0f;

    float y1 = 0.0f;
    float y2 = 0.0f;
    
    FilterTypeBiquad filterType = lowpass; //Select between lowpass and highPassFilter, flipped signs on highpassfilter
    double sampleRate = 44100.0;
    double cutoffFrequency = 200.0; //Fc
    double resonance = 0.7071; //(Q)
    
    //Filter Coefficients and variables for calculating
    double a0 = 0.0f;
    double a1 = 0.0f;
    double a2 = 0.0f;
    
    double b1 = 0.0f;
    double b2 = 0.0f;
    
    double theta = 0.0f;
    
};
