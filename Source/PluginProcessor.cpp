#include "PluginProcessor.h"
#include "PluginEditor.h"

teleSynthAudioProcessor::teleSynthAudioProcessor(): AudioProcessor (BusesProperties()
.withOutput ("Output", juce::AudioChannelSet::stereo(), true)){
    
    
    
}
teleSynthAudioProcessor::~teleSynthAudioProcessor() {}

//==============================================================================
void teleSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    
    sliderSynthesiser.initaliseVoices(sampleRate, samplesPerBlock, getNumOutputChannels());
    effectsProcessor.prepare(sampleRate);
    
    
}
void teleSynthAudioProcessor::releaseResources() {
    
}

bool teleSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void teleSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) {
    
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();
    
    sliderSynthesiser.renderNextBlock(buffer, 0, buffer.getNumSamples());
    
    effectsProcessor.processEffects(buffer); 
    
    //Push data into the waveFifo, used ot draw the output 
    if(buffer.getNumChannels() > 0)
        waveFifo.push(buffer.getReadPointer(0), buffer.getNumSamples());
}

//==============================================================================
juce::AudioProcessorEditor* teleSynthAudioProcessor::createEditor() {
    
    return new teleSynthAudioProcessorEditor (*this);
}

bool teleSynthAudioProcessor::hasEditor() const {
    return true;
}

//==============================================================================
const juce::String teleSynthAudioProcessor::getName() const {
    return "iphone Audio";
}

bool teleSynthAudioProcessor::acceptsMidi() const {
    return true;
}
bool teleSynthAudioProcessor::producesMidi() const {
    return false;
}
bool teleSynthAudioProcessor::isMidiEffect() const {
    return false;
}
double teleSynthAudioProcessor::getTailLengthSeconds() const {
    return 0.0f;
}

//==============================================================================
int teleSynthAudioProcessor::getNumPrograms() {
    return 1;
}
int teleSynthAudioProcessor::getCurrentProgram() {
    return 0;
}

void teleSynthAudioProcessor::setCurrentProgram (int index) {
    
}

const juce::String teleSynthAudioProcessor::getProgramName (int index) {
    return {};
}
void teleSynthAudioProcessor::changeProgramName (int index, const juce::String& newName) {
    
}

//==============================================================================
void teleSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    
}
void teleSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    
}

std::function<void(float x, float y , int touch)> teleSynthAudioProcessor::getSynthStartNote(){
    
    return [this](float x, float y, int touch) {
        
        float frequency = SynthRange::normToFreq(y);
        float velocity = x;
        
        sliderSynthesiser.startNote(frequency, velocity, touch);
        };
    
}

std::function<void(int touch)> teleSynthAudioProcessor::getSynthStopNote(){
    
    return [this](int touch){
        
        sliderSynthesiser.stopNote(touch);
    }; 
}


std::function<void(float x, float y , int touch)> teleSynthAudioProcessor::getSynthMoveNote(){
    
    return [this](float x, float y, int touch){
        
        float frequency = SynthRange::normToFreq(y);
        float velocity = x;
        
        sliderSynthesiser.updateValues(frequency, velocity, touch);
        
    };
}

std::function<void(juce::ADSR::Parameters adsrParams)> teleSynthAudioProcessor::getAdsrUpdate(){
    
    return [this](juce::ADSR::Parameters adsrParams){
        
        sliderSynthesiser.setADSR(adsrParams);
    };
}


SliderSynthesiser& teleSynthAudioProcessor::getSliderSynthesiser(){
    
    return sliderSynthesiser; 
}

