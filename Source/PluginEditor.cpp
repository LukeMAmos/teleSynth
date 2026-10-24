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
    
    //Resize the vectors 
    scratch.resize(p.getWaveFifo().capacity);
    history.assign(512, 0.0f);
    
    //Update the waveform viewer every 30Hz
    startTimerHz(30);
    
    setSize(400 , 600);
}

teleSynthAudioProcessorEditor::~teleSynthAudioProcessorEditor(){
    
    
    
}

//==============================================================================
void teleSynthAudioProcessorEditor::paint (juce::Graphics& g){
    
    g.fillAll(ThemeColours::background());
    
    
}


void teleSynthAudioProcessorEditor::resized(){
    
    switchScreen.setBounds(15, 50, 100, 100);
    
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

void teleSynthAudioProcessorEditor::timerCallback(){
    
    const int n = audioProcessor.getWaveFifo().pull(scratch.data() , (int)scratch.size());
    if(n == 0)
        return;
    
    const int N = (int)history.size();
    
    if(n >= N){
        std::copy(scratch.begin() + (n- N)  , scratch.begin() + n  , history.begin()); // keep the newest N samples
    } else{
        
        std::copy(history.begin() + n, history.end(), history.begin()); //shift left
        std::copy(scratch.begin() , scratch.begin() + n , history.end() -n); // append new data
    }
    
    mainPage->setWaveformSamples(history.data(), N); 
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new teleSynthAudioProcessor();
}

