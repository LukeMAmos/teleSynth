#pragma once
#include <array>
#include <juce_audio_basics/juce_audio_basics.h>

//FIFO class for handling passing buffer data to the waveform viewer from the main output
class WaveFIFO{

public:
    //Audio Thread  pushes data into the fifo
    void push(const float* data , int numSamples){
        
        const auto wave = fifo.write(numSamples);
        
        //Copying both blocks of data into the buffer
        if(wave.blockSize1 > 0)
            juce::FloatVectorOperations::copy(buffer.data() + wave.startIndex1, data, wave.blockSize1);
        if(wave.blockSize2 > 0)
            juce::FloatVectorOperations::copy(buffer.data() + wave.startIndex2, data, wave.blockSize2);
        
    }
    
    //UI pulls data from the Fifo to diaplay
    int pull(float* dest , int maxSamples){
        
        const auto wave = fifo.read(maxSamples);
        
        //copying  ot blocks of data into the buffer
        if(wave.blockSize1 > 0)
            juce::FloatVectorOperations::copy(dest, buffer.data() + wave.startIndex1 , wave.blockSize1);
        if(wave.blockSize2 > 0)
            juce::FloatVectorOperations::copy(dest + wave.blockSize1,buffer.data() + wave.startIndex2 , wave.blockSize2);
        
        //return the  total number of samples
        return wave.blockSize1 + wave.blockSize2;
    }
    
    
    static constexpr int capacity = 16384; // roughly 1600 samples inbetween ticks at 30Hz and 48kHz
private:
    
    juce::AbstractFifo fifo{capacity};
    std::array<float , capacity> buffer{};
};
