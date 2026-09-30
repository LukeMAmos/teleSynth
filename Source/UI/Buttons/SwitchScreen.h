#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "ThemeColours.h"
class SwitchScreenButton : public juce::Button {
    

public:
    
    SwitchScreenButton(); 
    void resized() override;
    
    void paintButton(Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
private:
    
    
};
