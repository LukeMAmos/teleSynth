#include "SynthesiserVoice.h"
#include <JuceHeader.h>


class SliderSynthesiser{
    
public:
    
    SliderSynthesiser();
    
    void initaliseVoices(double sampleRate , int samplesPerBlock , int numChannels);
    //Start and stop notes as needed
    void startNote(float frequency, float velocity , int touch);
    void stopNote(int touch);
    void updateValues(float frequency, float velocity ,int touch);
    
    //Go through each of the voices and combine the ou
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples);
    
    //Set the ADSR on each of the voices
    void setADSR(juce::ADSR::Parameters adsrParams);
    
    //Set the wavetable osc , should take any size samples and downsize to the first wavetableSamples samples
    void setWavetableSamples(std::vector<float> samples);
    //Calls the private FFT functions and fills the array of mipmap tables
    void setAllMipmapTables();
    
    //Called by the voices to calculate which index in the array to use to playback 
    
private:
    
    static constexpr int maxVoices = 5;
    static constexpr int wavetableSamples = 2048;
    static constexpr int fullSizeTable = wavetableSamples * 2;
    
    //array of samples for the original wavetable samples, 2*size to perform the forward and inverse FFT
    
    //Array of Voices
    SliderSynthVoice sliderVoices[maxVoices];
    //Array to hold which touch is linked to which voice, the position is the voice and the index is the Touch
    int voiceToTouch[maxVoices];
    
    int findFreeVoice();
    
    //Functions for performing the forward and Inverse FFTs to build an array of bandlimited sample arrays
    std::array<float ,fullSizeTable> computeForwardFFT(std::array<float, fullSizeTable > wavetable);
    std::array<float, wavetableSamples> computeInverseFFT(std::array<float, fullSizeTable> wavetable , float cutoffFreq);
    
    
    
}; 
