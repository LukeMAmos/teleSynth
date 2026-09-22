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
    
    draggableZone.setBounds(getWidth() * 0.05 , getHeight() * 0.4 , getWidth() - (getWidth() * 0.05) , getHeight() * 0.6 ); 
    dotSlider.setBounds(0 ,0, 100 , 80);

    
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new teleSynthAudioProcessor();
}

