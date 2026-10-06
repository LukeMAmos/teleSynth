#include "adsrPoint.h"


AdsrPoint::AdsrPoint(Stage pointStage){
    
    stage = pointStage;

}



void AdsrPoint::paint(juce::Graphics &g){
    
    //Draw Simple orange Circle with the bounds of the point
    auto bounds = getLocalBounds().toFloat();
    
    g.setColour(ThemeColours::orange());
    g.fillEllipse(bounds);
    
}

void AdsrPoint::setShouldBeMoved(bool moving){
    shouldBeMoved = moving;
}

bool AdsrPoint::getShouldBeMoved(){
    return shouldBeMoved;
}

float AdsrPoint::getDiameter(){
    
    return getWidth(); 
}
