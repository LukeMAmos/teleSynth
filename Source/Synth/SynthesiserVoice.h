#include <JuceHeader.h>

class SliderSynthVoice {
    
public:
    //Implementing a wavetable Synth, the wave is randomly generated eachtime using 3 parameters and the original wave to morph to control the waveoutcome
    
    
    SliderSynthVoice();
    //Note on and off functions, as well as a function to update the frequency of the note
    void startNote(float frequency , float velocity);
    void stopNote();
    
    //Need to make the frequency update smooth
    void updateNoteFrequency(float frequency);
    
    //Rendering the voice
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples);
    
    //update the oscillator used from the random Wavetable generator 
    void updateOSCWavetable();
    
    void setADSR(juce::ADSR::Parameters adsrParamsIn);
    
    bool isActive(){return voiceActive;}
    
private:
    
    //Inital Implementation using a simple SineWave
    juce::dsp::Oscillator<float> OSC;
    juce::ADSR ADSR;
    juce::ADSR::Parameters adsrParams;
    
    bool voiceActive = false;

};

