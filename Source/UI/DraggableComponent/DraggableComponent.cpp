#include "DraggableComponent.h"

DraggableComponent::DraggableComponent(){
    
    setWantsKeyboardFocus(true);
    
    setDiameter(50.0f);
}

void DraggableComponent::paint(juce::Graphics &g){
    
    g.setColour (juce::Colours::blueviolet);

    g.fillEllipse(0, 0, diameter, diameter);
}

void DraggableComponent::mouseDown(const juce::MouseEvent &event){
    
    dragger.startDraggingComponent(this, event);

    
}

void DraggableComponent::mouseDrag(const juce::MouseEvent &event){
    
    dragger.dragComponent(this, event, &constrainer);

}

void DraggableComponent::mouseUp(const juce::MouseEvent &event){

    
}


void DraggableComponent::resized(){

}

void DraggableComponent::setDiameter(float diameterIn){
    
    diameter = diameterIn;
}

float DraggableComponent::getDiameter(){
    
    return diameter;
}

void DraggableComponent::setStartFunction(std::function<void(float xpos,float ypos)> function){
    
    onDragStart = function;
}
void DraggableComponent::setMoveFunction(std::function<void(float xpos,float ypos)> function){
    
    onDragMove = function;
}
void DraggableComponent::setEndFunction(std::function<void()> function){
    
    onDragEnd = function;
    
}

void DraggableComponent::setXYBounds(juce::Rectangle<int> bounds){
    
    constrainer.setBoundsForComponent(this, bounds, false, false, false, false);
    
}
