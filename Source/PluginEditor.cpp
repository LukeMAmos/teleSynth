#include "PluginProcessor.h"
#include "PluginEditor.h"


teleSynthAudioProcessorEditor::teleSynthAudioProcessorEditor (teleSynthAudioProcessor& p): AudioProcessorEditor (&p), audioProcessor (p){
    
}

teleSynthAudioProcessorEditor::~teleSynthAudioProcessorEditor(){
    
    
    
}

//==============================================================================
void teleSynthAudioProcessorEditor::paint (juce::Graphics& g){
    
    
}


void teleSynthAudioProcessorEditor::resized(){
    

    
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new teleSynthAudioProcessor();
}

