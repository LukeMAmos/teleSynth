#include "SynthesiserVoice.h"
#include <JuceHeader.h>


class SliderSynthesiser{
    
public:
    
    
    //Go through each of the voices and combine the ou
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples);
    
    //Set the ADSR on each of the voices
    void setADSR(juce::ADSR::Parameters adsrParams);
    //Set the wavetable osc 
    void setOSCWavetable();
    
    
private:
    
    //Array of Voices
    SliderSynthVoice sliderVoices[5];
    //Array to hold which touch is linked to which voice, the position is the voice and the index is the Touch
    int voiceToTouch[5];
    
    int findFreeVoice(); 
    
}; 
