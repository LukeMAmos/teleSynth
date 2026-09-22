#include <juce_gui_basics/juce_gui_basics.h>
 
class DotSlider : public juce::Slider{

public:
    
    DotSlider();
    //Override Paint function
    void paint(juce::Graphics &g) override;
    
private:
    
};
