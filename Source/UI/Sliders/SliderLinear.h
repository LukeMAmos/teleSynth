#include <juce_gui_basics/juce_gui_basics.h>
#include "ThemeColours.h"

class LinearSlider : public juce::Slider{

public:
    
    LinearSlider();
    //Override Paint function
    void paint(juce::Graphics &g) override;
    
private:
    
};
