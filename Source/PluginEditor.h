#pragma once
#include <JuceHeader.h>
#include "UI/DraggableComponent/DraggableZone.h"
#include "UI/Sliders/Slider.h"
#include "UI/ThemeColours.h"
#include "UI/Buttons/SwitchScreen.h"
#include "UI/adsrSlider/adsrSlider.h"

//Forward declaration
class teleSynthAudioProcessorEditor;

//Need to implement two different pages, one for the menu screen and one for the main playing screen

//Main page with its components
class MainPage : public juce::Component{
    
public:
    
    MainPage(teleSynthAudioProcessor& p): audioProcessor(p){
        
        addAndMakeVisible(draggableZone);
        
        draggableZone.setStartFunction(audioProcessor.getSynthStartNote());
        draggableZone.setMoveFunction(audioProcessor.getSynthMoveNote());
        draggableZone.setEndFunction(audioProcessor.getSynthStopNote());
    }
    
    void resized() override {
        auto fullBounds = getBounds().reduced(5, 15);
        draggableZone.setBounds(fullBounds.removeFromBottom((int)(getHeight() * 0.6f)));
        
        
    }
    
private:
    
    teleSynthAudioProcessor& audioProcessor;
    
    DraggableZone draggableZone;
    DotSlider dotSlider;
    
};

//menu page with its components
class MenuPage : public juce::Component{
    
public:
    
    MenuPage(teleSynthAudioProcessor& p): audioProcessor(p){
        
        addAndMakeVisible(adsrSlider);
        
        
    }
    
    void resized() override {
        
        adsrSlider.setBounds(125, 50, 250, 150); 
        
    }
    
private:
    
    teleSynthAudioProcessor& audioProcessor;
    AdsrSlider adsrSlider; 
    
};


class teleSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    teleSynthAudioProcessorEditor (teleSynthAudioProcessor& p);
    ~teleSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    void switchPage();
    
private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    teleSynthAudioProcessor& audioProcessor;
    
    //UI Element switcher
    SwitchScreenButton switchScreen;
    bool mainScreenActive = true; 
    
    //Main Page
    std::unique_ptr<MainPage> mainPage;
    //Menu Page
    std::unique_ptr<MenuPage> menuPage;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (teleSynthAudioProcessorEditor)
};
