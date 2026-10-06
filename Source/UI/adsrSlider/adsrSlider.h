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
    
    //Helper function for converting pixel distance to time / gain
    
private:
    
    static constexpr int inset = 5;
    
    int radius; //dot radius
    int margin; //keeps dots within the bounds
    int topY; //highest a dot can go
    int bottomY; //lowest a dot can go
    int leftX; //most left a dot can go
    int rightX; //most right a dot can go 
    int usable; //horizontal range
    int midY; //middle vertical 
    
    AdsrPoint AdsrPoints[4] = {Attack , Decay , Sustain , Release};
    
};
