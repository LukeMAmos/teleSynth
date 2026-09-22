#pragma once
#include <JuceHeader.h>
#include "UI/DraggableComponent/DraggableZone.h"
#include "UI/Sliders/Slider.h"
#include "UI/ThemeColours.h"

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
    
    //UI Elements
    DraggableZone draggableZone;
    DotSlider dotSlider; 
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (teleSynthAudioProcessorEditor)
};
