#include <juce_gui_basics/juce_gui_basics.h>
 
class Slider : public juce::Slider{

public:
    
    Slider();
    //Override Paint function
    void paint(juce::Graphics &g) override;
    
private:
    
};
