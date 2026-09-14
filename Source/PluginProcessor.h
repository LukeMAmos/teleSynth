#pragma once
#include <JuceHeader.h>



class teleSynthAudioProcessor : public juce::AudioProcessor
{
    
public:
    
    teleSynthAudioProcessor();
    ~teleSynthAudioProcessor() override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    
    ContinousSynth& getSynth(int index) { return Synth[index]; }

    
private:
    
    juce::dsp::Oscillator<float> testOsc;
    
    static constexpr int numVoices = 5;
    ContinousSynth Synth[numVoices];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (teleSynthAudioProcessor)
};

