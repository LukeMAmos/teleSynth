#include <JuceHeader.h>

class SliderSynthVoice {
    
public:
    //Implementing a wavetable Synth, the wave is randomly generated eachtime using 3 parameters and the original wave to morph to control the waveoutcome
    
    
    SliderSynthVoice();
    
    void startNote(float frequency);
    void stopNote();
    
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples);
    
    void updateOscillators();
    
    
private:
    
    //Inital Implementation using a simple SineWave
    juce::dsp::Oscillator<float> oscillator;
    juce::ADSR ADSR;
    juce::ADSR::Parameters adsrParams;
    

};

