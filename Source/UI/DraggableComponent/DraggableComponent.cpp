#include "DraggableComponent.h"

DraggableComponent::DraggableComponent(){
    
    setWantsKeyboardFocus(true);
    setDiameter(50.0f);
}

void DraggableComponent::paint(juce::Graphics &g){
    
    g.setColour (ThemeColours::orange());
    g.fillEllipse(0, 0, diameter, diameter);
    g.setColour (ThemeColours::black());
    g.fillEllipse(4 ,4, diameter-8, diameter-8);
}

void DraggableComponent::resized(){

}

void DraggableComponent::setDiameter(float diameterIn){
    
    diameter = diameterIn;
    setSize((int)diameter, (int)diameter);
}

float DraggableComponent::getDiameter(){
    
    return diameter;
    
}


