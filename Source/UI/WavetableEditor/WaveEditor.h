#include "juce_gui_basics/juce_gui_basics.h"
#include "Synth/SynthRange.h"
#include "ThemeColours.h"

class WaveEditor : public juce::Component
{
public:
    
    WaveEditor();
    
    void paint(juce::Graphics &g) override;
    void resized() override;
    
    //Control touch events
    void mouseDown (const juce::MouseEvent& event) override;
    void mouseDrag (const juce::MouseEvent& event) override;
    void mouseUp   (const juce::MouseEvent& event) override;
    
    //set the function to call on waveComplete
    void setWaveComplete(std::function<void(const std::array<float, SynthRange::wavetableSamples>&)>);
    
private:
    
    //Drawing path
    juce::Path wavePath;
    
    //Middle point used for calculting samples and for drawing
    float midHeight = 0.0f;
    std::array<float, SynthRange::wavetableSamples> waveSamples;
    //Increment for adding the next value to the array, if the x value is above pos in array * incre add it to teh list so we get 2048 evenly spaced
    float xIncrement = 0.0f;
    int curSample = 0;
    
    //Function to call when wave is drawn so that mipmapping process can take place
    std::function<void(const std::array<float, SynthRange::wavetableSamples>&)> waveComplete;
    
    //Bounds to keep the drawing inside of, holding previous positon to ensure the wave is a legal wave only goes forward
    juce::Rectangle<int> drawingBounds;
    juce::Point<float> previousPoint; 
    //Limit the line drawn to stay in the box
    juce::Point<float> limitDrawing(juce::Point<float> drawingPoint , bool newLine);
    
    //Return the Y value as a number between -1 and 1
    float sampleNormalise(float yPos);

    float samplePos(int n) const; 
    
};
