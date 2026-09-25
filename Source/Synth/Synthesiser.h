#include "SynthesiserVoice.h"
#include <JuceHeader.h>


class SliderSynthesiser{
    
public:
    
    
    void initaliseVoices(double sampleRate , int samplesPerBlock , int numChannels);
    //Start and stop notes as needed
    void startNote(float frequency, float velocity , int touch);
    void stopNote(int touch);
    
    //Go through each of the voices and combine the ou
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples);
    
    //Set the ADSR on each of the voices
    void setADSR(juce::ADSR::Parameters adsrParams);
    //Set the wavetable osc 
    void setOSCWavetable();
    
    
private:
    
    static constexpr int maxVoices = 5;
    //Array of Voices
    SliderSynthVoice sliderVoices[maxVoices];
    //Array to hold which touch is linked to which voice, the position is the voice and the index is the Touch
    int voiceToTouch[maxVoices];
    
    int findFreeVoice(); 
    
}; 
