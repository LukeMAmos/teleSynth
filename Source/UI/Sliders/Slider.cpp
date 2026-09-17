#include "SmallSlider.h"
#include <numbers>

Slider::Slider(){
    
    //Set the slider style and the rotary parameters of the slider
    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, true);
}


//Override Paint function
void Slider::paint(juce::Graphics &g){
    
    //Get the bounds of the slider and the Sliders current value normalised between 0 and 1 to make drawing easier
    auto wholeBounds = getLocalBounds().reduced(5);
    float SliderPos = (float)((getValue() - getMinimum())/(getMaximum() - getMinimum()));
    
    //Get the start and end angle of the rotary slider to use to calculate the angle step inbetween each of the dots
    float rotaryStartAngle = getRotaryParameters().startAngleRadians;
    float rotaryEndAngle = getRotaryParameters().endAngleRadians;
    
    auto angleStep = (rotaryStartAngle - rotaryEndAngle) / 10.0f;
    auto radius = juce::jmin(wholeBounds.getWidth(), wholeBounds.getHeight()) / 2;
    
    //Calculate the dot width and use to set the path of the dots
    auto dotWidth = juce::jmin(8.0f, radius * 0.5f);
    auto dotPath = radius - dotWidth * 0.5f;
    
    //The max dot for this slider, this is used to decide the brightness of the dots that come before and after
    int maxDotPosition = (int)(SliderPos * 10.0f);
    
    //Drawing the dots
    for(int i = 0; i < 10 ; i++){
        
        //Get the angle to be drawn for this specific dot
        auto dotAngle = rotaryStartAngle + (i * angleStep);
        
        //Calculate the position to draw the dot using the path from the centre
        juce::Point<float> dotLocation (wholeBounds.getCentreX() + dotPath * std::sin(dotAngle) , wholeBounds.getCentreY() + dotPath * std::cos(dotAngle));
        
        //Set the colour used for the dot and draw it
        if(i <= maxDotPosition){
            g.setColour (juce::Colours::grey.withBrightness(0.2f + SliderPos));
            g.fillEllipse (juce::Rectangle<float> (dotWidth, dotWidth).withCentre (dotLocation));
        }else {
            g.setColour (juce::Colours::grey.withBrightness(0.15f));
            g.fillEllipse (juce::Rectangle<float> (dotWidth, dotWidth).withCentre (dotLocation));
        }
        
        
    }
    
}
