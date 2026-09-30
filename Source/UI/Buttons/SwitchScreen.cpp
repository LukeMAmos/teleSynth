#include "SwitchScreen.h"

SwitchScreenButton::SwitchScreenButton() : Button("Switch Screen Button"){
    
    
    
    
}

void SwitchScreenButton::resized(){

}

void SwitchScreenButton::paintButton(Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown){
    
    auto bounds = getLocalBounds().reduced(5).toFloat();
    //If we are on the main screen draw with specific method
    if(!shouldDrawButtonAsDown){
        //Orange background with black circle
        g.setColour(ThemeColours::orange());
        g.fillRoundedRectangle(bounds, 8);
        
        g.setColour(ThemeColours::black());
        g.fillEllipse(bounds.reduced(8));
        
    }else if (shouldDrawButtonAsDown){
        //Black background with orange Circle
        g.setColour(ThemeColours::black());
        g.fillRoundedRectangle(bounds, 8);
        
        g.setColour(ThemeColours::orange());
        g.fillEllipse(bounds.reduced(8));
        
        
    }
    
    
}
