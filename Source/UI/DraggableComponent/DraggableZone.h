#pragma once
#include <JuceHeader.h>
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
    
    
private:
    
    static constexpr int maxTouches = 5;
    int touchToSlot[maxTouches];
    std::unique_ptr<DraggableComponent> activePoints[maxTouches];
    
    int findFreeSlot() const;
};
