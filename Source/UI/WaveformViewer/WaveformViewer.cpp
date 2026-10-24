#include "WaveformViewer.h"

WaveformViewer::WaveformViewer(){
    
    
}

void WaveformViewer::paint(juce::Graphics& g ){
    
    //orange border 
    g.setColour (ThemeColours::orange());
    g.drawRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f, 5.0f);
    
    //fill background with black
    g.setColour(ThemeColours::black());
    g.fillRoundedRectangle(getLocalBounds().reduced(5.0f).toFloat(), 10.0f);
    
    //Drawing the individual samples

    
    //Dont diplay the samples if they havent been filled yet
    const int numSamples = (int)displaySamples.size();
    if(numSamples< 2)
        return;
    
    const float left = 5.0f;
    const float drawWidth = (float)getWidth() - 10.0f;
    const float pixelsPer = (drawWidth / (float)(numSamples));
    const float barWidth = juce::jmax(1.0f, pixelsPer);
    const float midPoint = (getHeight() / 2);
    const float halfHeight = midPoint - 5.0f;
                       
    g.setColour(ThemeColours::orange());
    
    for(int s = 0; s < (int)displaySamples.size() ; s++){
        
        const float sample = juce::jlimit(-1.0f , 1.0f, displaySamples[(size_t)s]); // get the value of the sample at index s and  then change it to a size
        const float length = sample * halfHeight;
        const float x = left + ((float)s * pixelsPer);
        
        if(sample > 0.0f){ //positive sample, start from mid go up
            
            g.fillRoundedRectangle(x, midPoint-length, barWidth, length, 4);
            
        }else if (sample < 0.0f ){ //negative sample start from negative sample pos and go up
            
            g.fillRoundedRectangle(x, midPoint, barWidth, -length, 4);
            
        }
    }
}

void WaveformViewer::resized(){
    
    
    
}

void WaveformViewer::setSamples(const float* data , int numSamples){
    
    displaySamples.assign(data , data + numSamples);
    repaint(); 
}

int WaveformViewer::sampleToLength(float sample){
    //Use the height of the component to turn the sample value into a lenghth, sample is already normalised between 0 and 1
    return (int)std::floor(sample * getHeight());
}
