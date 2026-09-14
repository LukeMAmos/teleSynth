#pragma once
#include <JuceHeader.h>

class teleSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    teleSynthAudioProcessorEditor (teleSynthAudioProcessor& p);
    ~teleSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    teleSynthAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (teleSynthAudioProcessorEditor)
};
