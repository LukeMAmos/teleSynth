#pragma once
#include <JuceHeader.h>
#include "UI/DraggableComponent/DraggableZone.h"
#include "UI/Sliders/Slider.h"
#include "UI/ThemeColours.h"
#include "UI/Buttons/SwitchScreen.h"
#include "UI/adsrSlider/adsrSlider.h"
#include "UI/WaveformViewer/WaveformViewer.h"
#include "UI/WavetableEditor/WaveEditor.h"

//Forward declaration
class teleSynthAudioProcessorEditor;

//Need to implement two different pages, one for the menu screen and one for the main playing screen

//Main page with its components
class MainPage : public juce::Component{
    
public:
    
    MainPage(teleSynthAudioProcessor& p): audioProcessor(p){
        
        addAndMakeVisible(draggableZone);
        addAndMakeVisible(waveformViewer);
        
        draggableZone.setStartFunction(audioProcessor.getSynthStartNote());
        draggableZone.setMoveFunction(audioProcessor.getSynthMoveNote());
        draggableZone.setEndFunction(audioProcessor.getSynthStopNote());
    }
    
    void resized() override {
        auto fullBounds = getBounds().reduced(5, 15);
        
        //Bottom area used by the draggable Zone
        auto bottomArea = fullBounds.removeFromBottom((int)(getHeight() * 0.6f));
        draggableZone.setBounds(bottomArea);

        const int dialThickness = 100;
        
        //Top and left areas are for dials and buttons
        auto topArea = fullBounds.removeFromTop(dialThickness + 50);
        auto leftArea = fullBounds.removeFromLeft(dialThickness + 15);
        
        //Waveform fills the remaining area
        waveformViewer.setBounds(fullBounds.reduced(5));
        
    }
    
    //Allows the audio processor to call the function 
    void setWaveformSamples(const float* data , int numSamples){
        waveformViewer.setSamples(data , numSamples);
    }
private:
    
    teleSynthAudioProcessor& audioProcessor;
    
    //UI Components
    DraggableZone draggableZone;
    DotSlider dotSlider;
    WaveformViewer waveformViewer;
    
};

//menu page with its components
class MenuPage : public juce::Component{
    
public:
    
    MenuPage(teleSynthAudioProcessor& p): audioProcessor(p){
        
        addAndMakeVisible(adsrSlider);
        adsrSlider.setCallOnChange(audioProcessor.getAdsrUpdate());
        
        addAndMakeVisible(waveEditor);
        
        
    }
    void resized() override {
        
        adsrSlider.setBounds(125, 50, 250, 150); 
        
        waveEditor.setBounds(50, 300, getWidth() - 100 , (int)(getHeight() * 0.25f));
    }
    
private:
    
    teleSynthAudioProcessor& audioProcessor;
    AdsrSlider adsrSlider;
    WaveEditor waveEditor;
    
};


class teleSynthAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    teleSynthAudioProcessorEditor (teleSynthAudioProcessor& p);
    ~teleSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    void switchPage();
    
    //Timer Callback to update data for drawing
    void timerCallback() override;
    
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
    
    std::vector<float> scratch; //all the FIFO
    std::vector<float> history; // the data that actually gets shown 
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (teleSynthAudioProcessorEditor)
};
