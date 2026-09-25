#include "DraggableZone.h"

DraggableZone::DraggableZone(){
    
    std::fill(std::begin(touchToSlot), std::end(touchToSlot), -1);
    
}


void DraggableZone::paint(juce::Graphics &g){
    
    juce::Rectangle<int> rectArea = getLocalBounds();

    g.fillAll (juce::Colours::blueviolet);
    g.setColour (ThemeColours::black());
    g.drawRect (getLocalBounds(), 2);
    
}
void DraggableZone::resized(){
    
    auto areaLimits = getLocalBounds();
    

    
}

void DraggableZone::mouseDown (const juce::MouseEvent& event){
    
    //Get the index of the touch
    const int touchIndex = event.source.getIndex();
    if(touchIndex < 0 || touchIndex >= maxTouches) return;
    
    //Check there is a free Draggable component available
    const int slot = findFreeSlot();
    if(slot == -1) return;
    
    //Make a new active point at the index of the slot and give it a diameter
    activePoints[slot] = std::make_unique<DraggableComponent>();
    int diameter = 50;
    activePoints[slot]->setDiameter(diameter);
    
    //Map the touch to slot array to the correct slot
    touchToSlot[touchIndex] = slot;
    //Make the current touch point visible
    addAndMakeVisible(*activePoints[slot]);
    
    int radius = (int)(activePoints[slot]->getDiameter() / 2.0f);
    //Bound the point inside the DraggableZone, the minimum it can go is the radius of the circle the max is the width minus the radius in both up and down direction
    juce::Point<int> boundedPos = event.getPosition();
    boundedPos.setX(juce::jlimit(radius, getWidth() - radius, boundedPos.getX()));
    boundedPos.setY(juce::jlimit(radius, getHeight() - radius, boundedPos.getY()));
    
    //Set the position of the point using the bounded position of the touch event
    activePoints[slot]->setCentrePosition(boundedPos.getX(), boundedPos.getY());
    
    callOnDragStart(boundedPos.getX(), boundedPos.getY(), touchIndex);
}

void DraggableZone::mouseDrag (const juce::MouseEvent& event){
    
    //Get the index of the touch and check it is a valid touch
    const int touchIndex = event.source.getIndex();
    if(touchIndex < 0 || touchIndex >= maxTouches) return;
    
    //Check the slot is being used currently
    const int slot = touchToSlot[touchIndex];
    if(slot == -1 || activePoints[slot] == nullptr) return;
    
    int radius = (int)(activePoints[slot]->getDiameter() / 2.0f);
    //Bound the point inside the DraggableZone, the minimum it can go is the radius of the circle the max is the width minus the radius in both up and down direction
    juce::Point<int> boundedPos = event.getPosition();
    boundedPos.setX(juce::jlimit(radius, getWidth() - radius, boundedPos.getX()));
    boundedPos.setY(juce::jlimit(radius, getHeight() - radius, boundedPos.getY()));
    
    activePoints[slot]->setCentrePosition(boundedPos.getX() , boundedPos.getY());
    
    callOnDragMove(boundedPos.getX(), boundedPos.getY(), touchIndex);
}

void DraggableZone::mouseUp   (const juce::MouseEvent& event){
    
    //Get the index of the touch
    const int touchIndex = event.source.getIndex();
    if(touchIndex < 0 || touchIndex >= maxTouches) return;
    
    //Check the slot is being used
    const int slot = touchToSlot[touchIndex];
    if(slot == -1) return;
    
    
    activePoints[slot].reset();
    touchToSlot[touchIndex] = -1;
    
    callOnDragEnd(<#int touch#>);
}

int DraggableZone::findFreeSlot() const{
    
    //Check for available slots in maxTouches;
    for(int i = 0; i < maxTouches ; i++){
        
        if(activePoints[i] == nullptr) return i;
        
    }
    
    return -1;
}

void DraggableZone::setStartFunction(std::function<void(float xpos,float ypos, int touch )> function){
    
    onDragStart = function;
}
void DraggableZone::setMoveFunction(std::function<void(float xpos,float ypos, int touch )> function){
    
    onDragMove = function;
}
void DraggableZone::setEndFunction(std::function<void(int touch)> function){
    
    onDragEnd = function;
    
}
