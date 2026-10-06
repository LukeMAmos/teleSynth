#pragma once 
#include "juce_gui_basics/juce_gui_basics.h"
#include "ThemeColours.h"
#include "adsrPoint.h"


class AdsrSlider : public juce::Component {
    
public:
    
    AdsrSlider();
    
    void paint(juce::Graphics& g) override ;
    void resized() override;
    
    //Event press and move functions 
    void mouseDown (const juce::MouseEvent& event) override;
    void mouseDrag (const juce::MouseEvent& event) override;
    void mouseUp   (const juce::MouseEvent& event) override;
    
    
    //Get specifc values
    float getAttack();
    float getDecay();
    float getSustain();
    float getRelease();
    
    //Get the whole group of values spefically ready to passed through
    juce::ADSR::Parameters getADSRParameters();
    
private:
    
    AdsrPoint AdsrPoints[4] = {Attack , Decay , Sustain , Release};
    
};
