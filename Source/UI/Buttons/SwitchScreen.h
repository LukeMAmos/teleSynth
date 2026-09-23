#include <juce_gui_basics/juce_gui_basics.h>

class SwitchScreenButton : public juce::Component {
    

public:
    
    SwitchScreenButton();
    
    void paint(juce::Graphics &g) override;
    void resized() override;
    
    //Control touch events
    void mouseDown (const juce::MouseEvent& event) override;
    void mouseUp   (const juce::MouseEvent& event) override;
    
    
    
private:
    
    //On initialisation open to the main screen, then use touch events to control what happens afterwards
    bool onMainScreen = true;
    
};
