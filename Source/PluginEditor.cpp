#include "PluginProcessor.h"
#include "PluginEditor.h"


teleSynthAudioProcessorEditor::teleSynthAudioProcessorEditor (teleSynthAudioProcessor& p): AudioProcessorEditor (&p), audioProcessor (p){
 
    setSize(400 , 600);
    
    addAndMakeVisible(draggableZone);
    addAndMakeVisible(dotSlider);
}

teleSynthAudioProcessorEditor::~teleSynthAudioProcessorEditor(){
    
    
    
}

//==============================================================================
void teleSynthAudioProcessorEditor::paint (juce::Graphics& g){
    
    g.fillAll(ThemeColours::grey());
    
    
}


void teleSynthAudioProcessorEditor::resized(){
    
    auto fullBounds = getBounds().removeFromTop(10).reduced(5);
    draggableZone.setBounds((int)fullBounds.removeFromBottom(getHeight() * 0.6));
    dotSlider.setBounds(0 ,0, 100 , 80);

    
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new teleSynthAudioProcessor();
}

