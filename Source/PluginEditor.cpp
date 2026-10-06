#include "PluginProcessor.h"
#include "PluginEditor.h"


teleSynthAudioProcessorEditor::teleSynthAudioProcessorEditor (teleSynthAudioProcessor& p): AudioProcessorEditor (&p), audioProcessor (p){
 
    //Setup mainPage and menuPage
    mainPage = std::make_unique<MainPage>(audioProcessor);
    menuPage = std::make_unique<MenuPage>(audioProcessor);
    
    addChildComponent(*mainPage);
    addChildComponent(*menuPage);
    
    switchScreen.onClick = [this](){
        
        mainScreenActive = !mainScreenActive;
        switchPage();
    };
    
    //Switch screen button is persistant, added after so it goes on top
    addAndMakeVisible(switchScreen);
    
    switchPage();
    
    setSize(400 , 600);
}

teleSynthAudioProcessorEditor::~teleSynthAudioProcessorEditor(){
    
    
    
}

//==============================================================================
void teleSynthAudioProcessorEditor::paint (juce::Graphics& g){
    
    g.fillAll(ThemeColours::background());
    
    
}


void teleSynthAudioProcessorEditor::resized(){
    
    switchScreen.setBounds(25, 50, 100, 100);
    
    auto bounds = getLocalBounds();
    
    if(mainPage != nullptr)
        mainPage->setBounds(bounds);
    
    if(menuPage != nullptr)
        menuPage->setBounds(bounds);
    
}

void teleSynthAudioProcessorEditor::switchPage(){
    
    mainPage->setVisible(mainScreenActive);
    menuPage->setVisible(!mainScreenActive);
    
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new teleSynthAudioProcessor();
}

