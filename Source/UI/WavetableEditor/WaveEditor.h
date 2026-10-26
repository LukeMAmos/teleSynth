#include "juce_gui_basics/juce_gui_basics.h"
#include "ThemeColours.h"

class WaveEditor : public juce::Component
{
public:
    
    WaveEditor();
    
    void paint(juce::Graphics &g) override;
    void resized() override;
    
    //Control multitouch events
    void mouseDown (const juce::MouseEvent& event) override;
    void mouseDrag (const juce::MouseEvent& event) override;
    void mouseUp   (const juce::MouseEvent& event) override;
    
private:
    
    //Drawing path
    juce::Path wavePath;
    //Bounds to keep the drawing inside of, holding previous positon to ensure the wave is a legal wave only goes forward
    juce::Rectangle<int> drawingBounds;
    juce::Point<float> previousPoint; 
    
    juce::Point<float> limitDrawing(juce::Point<float> drawingPoint , bool newLine); 
};
