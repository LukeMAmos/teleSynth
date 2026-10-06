#pragma once 
#include "juce_gui_basics/juce_gui_basics.h"
#include "ThemeColours.h"

enum Stage{
  
    Attack,
    Decay,
    Sustain,
    Release
};

class AdsrPoint : public juce::Component{
    
public:
    
    AdsrPoint(Stage pointStage);
    
    void paint(juce::Graphics& g) override;
    
    //If its been pressed change its shouldBeMoved Boolean value
    void setShouldBeMoved(bool moving);
    bool getShouldBeMoved();
    float getDiameter();
    
    Stage getStage(){ return stage; }
private:
    
    bool shouldBeMoved = false; 
    Stage stage;
    
};
