#include <JuceHeader.h>
#include "ThemeColours.h"

class DraggableComponent : public juce::Component
{
    
public:
    DraggableComponent();
    
    void paint(juce::Graphics& g )override;
    
    void resized() override;
    
    //Get the position of the circle
    float getPositionXCentre(){return (float)getX() + diameter / 2.0f;}
    float getPositionYCentre(){return (float)getY() + diameter / 2.0f;}
    
    bool mDown = false;
    
    //Set and get the size of the circle
    void setDiameter(float diameterIn);
    float getDiameter();
    
    
private:
    
    float diameter = 100;
    
    juce::ComponentDragger dragger;
    juce::ComponentBoundsConstrainer constrainer; 
    

};

