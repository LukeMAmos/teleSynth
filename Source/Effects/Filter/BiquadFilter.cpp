#include "BiquadFilter.h"


    
void BiquadFilter::prepare(double sampleRateIn){
    
    sampleRate = sampleRateIn;
    
    x1 = x2 = 0.0f;
    y1 = y2 = 0.0f;
    
}

void BiquadFilter::setParameters(float cutoffFreqIn , float resonanceIn , FilterTypeBiquad filterTypeIn){
    
    filterType = filterTypeIn;
    resonance = std::max(resonanceIn , (float)std::sqrt(0.5f));
    cutoffFrequency = juce::jlimit(0.0f , (sampleRate * 0.5f), cutoffFreqIn);
    
    theta = (( 2.0f * juce::MathConstants<float>::pi * cutoffFrequency ) / sampleRate);
    
    if(filterType == lowpass || filterType == highpass){
        b2 = (2.0f * resonance - sin(theta)) / (2.0f * resonance + sin(theta));
        b1 = -(1.0f + b2) * cos(theta);
    }else if (filterType == bandpass || filterType == bandreject){
        
        b2 = tan((juce::MathConstants<float>::pi)/(4.0f)-(theta / (2.0f * resonance)));
        b1 = -(1.0f + b2) * cos(theta);
    }
    switch (filterType) {
        case lowpass:
            a0 = 0.25f * (1 + b1 + b2);
            a1 = 2.0f * a0;
            a2 = a0;
            break;
            
        case highpass:
            a0 = 0.25f * (1.0f - b1 + b2);
            a1 = -2.0f * a0;
            a2 = a0;
            break;
            
        case bandpass:
            a0 = 0.5f * (1.0f-b2);
            a1 = 0.0f;
            a2 = -a0;
            break;
            
        case bandreject:
            a0 = 0.5f * (1.0f+b2);
            a1 = 0.0f;
            a2 = a0;
            break;
        
        default:
            break;
    }
    
}


float BiquadFilter::process(float input){
    
    //y(n) = a0 x(n) + a1 (n-1) + a2 (x-2) - b1 y(n-1) - b2 y(n-2)
    //Filter coeffients are calculated from cutoff , resonance and sampleRate, a biquad filter can act as both a lowpass and a highpass filter dependant on the input values
    
    float output = a0 * input +a1 * x1 +a2 * x2 -b1 * y1 - b2 * y2;
    
    x2 = x1;
    x1 = input;
    
    y2 = y1;
    y1 = output;
    
    return output;
}
    

