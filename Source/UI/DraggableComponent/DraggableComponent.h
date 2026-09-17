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
    
    void setStartFunction(std::function<void(float xpos,float ypos)> function);
    void setMoveFunction(std::function<void(float xpos,float ypos)> function);
    void setEndFunction(std::function<void()> function);
    
    void callOnDragStart(float xpos,float ypos){onDragStart(xpos , ypos);}
    void callOnDragMove(float xpos,float ypos){onDragMove(xpos , ypos);}
    void callOnDragEnd(){onDragEnd();}
    
    //Function for setting the area the slider can be dragged inside
    void setXYBounds(juce::Rectangle<int> bounds);
    
private:
    
    float diameter = 100;
    
    juce::ComponentDragger dragger;
    juce::ComponentBoundsConstrainer constrainer; 
    
    //Functions to call
    std::function<void(float xpos,float ypos)> onDragStart;
    std::function<void(float xpos,float ypos)> onDragMove;
    std::function<void()> onDragEnd;
};

