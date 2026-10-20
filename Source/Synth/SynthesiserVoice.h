#include <JuceHeader.h>
#include "SynthRange.h"

class SliderSynthVoice {
    
public:
    //Implementing a wavetable Synth, the wave is randomly generated eachtime using 3 parameters and the original wave to morph to control the waveoutcome
    
    
    SliderSynthVoice();
    
    void initaliseVoice(double sampleRate , int samplesPerBlock , int numChannels); 
    //Note on and off functions, as well as a function to update the frequency of the note
    void startNote(float frequency , float velocity);
    void stopNote();
    void updateValues(float frequency, float velocity); //Update the values on move of the draggable component
    
    //Need to make the frequency update smooth
    void updateNoteFrequency(float frequency);
    
    //Rendering the voice
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample , int numSamples);
    void setADSR(juce::ADSR::Parameters adsrParamsIn);
    bool isActive(); //Checks if the voice is still active
    
    //Function for passing through pointer to minMapTables
    void setMinMapTables(std::array<std::array<float, SynthRange::wavetableSamples > ,SynthRange::nMinMapTables >*  tableLocations);
    
    
private:
    
    //Inital Implementation using a simple SineWave
    juce::ADSR ADSR;
    juce::ADSR::Parameters adsrParams;
    double sampleRate{0.0}; 
    
    //Pointer to the Synthesiser tables
    std::array<std::array<float, SynthRange::wavetableSamples > ,SynthRange::nMinMapTables >* minMapTablesLocation = nullptr;
    
    //Varibles needed for ech synth voice
    std::atomic<bool> valueUpdateNeeded{false};
    std::atomic<float> targetFreq{440.0f};
    std::atomic<float> targetVelocity{1.0f};
    double phase{0.0};
    double phaseIncre{0.0};
    int currentTable{1};
    
};

