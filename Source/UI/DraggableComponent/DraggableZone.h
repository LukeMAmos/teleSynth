#pragma once
#include "juce_gui_basics/juce_gui_basics.h"
#include "DraggableComponent.h"

class DraggableZone : public juce::Component{
    
public:
    
    DraggableZone();
    
    void paint(juce::Graphics &g) override;
    void resized() override;
    
    //Control multitouch events
    void mouseDown (const juce::MouseEvent& event) override;
    void mouseDrag (const juce::MouseEvent& event) override;
    void mouseUp   (const juce::MouseEvent& event) override;
    
    //Set the functions to call
    void setStartFunction(std::function<void(float xpos,float ypos, int touch )> function);
    void setMoveFunction(std::function<void(float xpos,float ypos, int touch )> function);
    void setEndFunction(std::function<void(int touch)> function);
    
    //Call the functions with specific values 
    void callOnDragStart(float xpos,float ypos, int touch){onDragStart(xpos , ypos , touch );}
    void callOnDragMove(float xpos,float ypos, int touch ){onDragMove(xpos , ypos , touch);}
    void callOnDragEnd(int touch ){onDragEnd(touch);}
    
private:
    //Max touches  , max number of voices at one time
    static constexpr int maxTouches = 5;
    int touchToSlot[maxTouches];
    std::unique_ptr<DraggableComponent> activePoints[maxTouches];
    
    //Diameter of the dots 
    int diameter = 50;
    int radius = (int)(diameter / 2.0f);
    
    int findFreeSlot() const;
    
    //Functions to call
    std::function<void(float xpos,float ypos, int touch )> onDragStart;
    std::function<void(float xpos,float ypos, int touch )> onDragMove;
    std::function<void(int touch)> onDragEnd;
    
    //Normalising function used by start and drag
    void normXY(float& XVal , float& YVal ); 
};
