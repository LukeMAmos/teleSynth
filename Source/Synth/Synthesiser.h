#include "SynthesiserVoice.h"
#include <JuceHeader.h>
#include "SynthRange.h"


class SliderSynthesiser{
    
public:
    
    SliderSynthesiser();
    
    void initaliseVoices(double sampleRateIn , int samplesPerBlock , int numChannels);
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
    
    double sampleRate;
    //FFT object
    static constexpr int fftOrder = 11; //2048, the length of the wavetable Samples
    juce::dsp::FFT fft{fftOrder};
    
    //array of samples for the original wavetable samples, 2*size to perform the forward and inverse FFT
    std::array<float, SynthRange::fullSizeTable> fullSizeWavetableSamples;
    std::array<float, SynthRange::fullSizeTable> forwardFFTResults;
    
    //Final Samples
    std::array<std::array<float, SynthRange::wavetableSamples > ,SynthRange::nMinMapTables > minMapTables;
    
    //Array of Voices
    SliderSynthVoice sliderVoices[SynthRange::maxVoices];
    //Array to hold which touch is linked to which voice, the position is the voice and the index is the Touch
    int voiceToTouch[SynthRange::maxVoices];
    
    //Function for finding and returning the place of the free voice 
    int findFreeVoice();
    
    //Functions for performing the forward and Inverse FFTs to build an array of bandlimited sample arrays
    std::array<float ,SynthRange::fullSizeTable> computeForwardFFT(std::array<float, SynthRange::fullSizeTable > wavetable);
    std::array<float, SynthRange::wavetableSamples> computeInverseFFT(std::array<float, SynthRange::fullSizeTable> wavetable , float highestFundamentalFreq);
    
    
    
}; 
