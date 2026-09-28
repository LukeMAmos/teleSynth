#include "SwitchScreen.h"

SwitchScreenButton::SwitchScreenButton(){
    
    
    
    
}

void SwitchScreenButton::paint(juce::Graphics &g){
    
    //If we are on the main screen draw with specific method 
    if(onMainScreen){
        //Orange background with black circle
        
        
    }else{
        //Black background with orange Circle 
        
        
    }
    
    
}

void SwitchScreenButton::resized(){

}

//Control touch events
void SwitchScreenButton::mouseDown (const juce::MouseEvent& event){
    
    //Update the isDown flag
    isDown = true;
    
    
}

void SwitchScreenButton::mouseUp   (const juce::MouseEvent& event){
    
    //Update the isDown flag
    isDown = false;
    
    //This function being called means the press is finished, therefore update the onMainScreenFlag by flipping its bool value
    onMainScreen = !onMainScreen;

}
