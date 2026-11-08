#include "SliderLinear.h"

LinearSlider::LinearSlider(){
    
    setSliderStyle(juce::Slider::LinearHorizontal);
    setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

}

//Override Paint function
void LinearSlider::paint(juce::Graphics &g){
    
    
    //Get the bounds of the slider and the Sliders current value normalised between 0 and 1 to make drawing easier
    auto wholeBounds = getLocalBounds().reduced(10);
    g.setColour(ThemeColours::black());
    g.fillRoundedRectangle(wholeBounds.getX(), wholeBounds.getY(), wholeBounds.getWidth(), wholeBounds.getHeight(), 8);
    
    float SliderPos = (float)((getValue() - getMinimum())/(getMaximum() - getMinimum()));
    
    //Calculate the dot width and use to set the path of the dots
    auto dotWidth = juce::jmax(8.0f, (float)wholeBounds.getHeight() * 0.15f );
    auto slotWidth = ((float)wholeBounds.getWidth() / 10.0f);
    
    //The max dot for this slider, this is used to decide the brightness of the dots that come before and after
    int maxDotPosition = (int)(SliderPos * 10.0f);
    
    //Drawing the dots
    for(int i = 0; i < 10 ; i++){
        
        //Get the angle to be drawn for this specific dot
        auto dotPosX = wholeBounds.getX() + slotWidth * (i + 0.5f);
        
        //Calculate the position to draw the dot using the path from the centre
        juce::Point<float> dotLocation ( dotPosX , wholeBounds.getCentreY());
        
        //Set the colour used for the dot and draw it
        if(i <= maxDotPosition){
            g.setColour (ThemeColours::orange().withBrightness(0.2f + SliderPos));
            g.fillEllipse (juce::Rectangle<float> (dotWidth, dotWidth).withCentre (dotLocation));
        }else {
            g.setColour (ThemeColours::orange().withBrightness(0.15f));
            g.fillEllipse (juce::Rectangle<float> (dotWidth, dotWidth).withCentre (dotLocation));
        }
        
        
    }
    
}
