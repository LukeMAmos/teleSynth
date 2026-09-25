#include "PluginProcessor.h"
#include "PluginEditor.h"


teleSynthAudioProcessorEditor::teleSynthAudioProcessorEditor (teleSynthAudioProcessor& p): AudioProcessorEditor (&p), audioProcessor (p){
 
    setSize(400 , 600);
    
    addAndMakeVisible(draggableZone);
    addAndMakeVisible(dotSlider);
    
    draggableZone.setStartFunction(<#std::function<void (float, float, int)> function#>);
    draggableZone.setMoveFunction(<#std::function<void (float, float, int)> function#>);
    draggableZone.setEndFunction(<#std::function<void (int)> function#>);
    
}

teleSynthAudioProcessorEditor::~teleSynthAudioProcessorEditor(){
    
    
    
}

//==============================================================================
void teleSynthAudioProcessorEditor::paint (juce::Graphics& g){
    
    g.fillAll(ThemeColours::grey());
    
    
}


void teleSynthAudioProcessorEditor::resized(){
    
    auto fullBounds = getBounds().removeFromTop(10).reduced(5);
    draggableZone.setBounds(fullBounds.removeFromBottom((int)(getHeight() * 0.6f)));
    dotSlider.setBounds(0 ,0, 100 , 80);

    
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new teleSynthAudioProcessor();
}

