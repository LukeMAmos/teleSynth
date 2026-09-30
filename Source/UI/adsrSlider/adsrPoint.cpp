#include "adsrPoint.h"


AdsrPoint::AdsrPoint(){
    
    
    
}



void AdsrPoint::paint(juce::Graphics &g){
    
    //Draw Simple Black Circle with the bounds of the point
    auto bounds = getLocalBounds().toFloat();
    
    g.setColour(ThemeColours::black());
    g.fillEllipse(bounds);
    
}
