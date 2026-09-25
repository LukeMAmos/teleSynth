#include "PluginProcessor.h"
#include "PluginEditor.h"

teleSynthAudioProcessor::teleSynthAudioProcessor(): AudioProcessor (BusesProperties()
.withOutput ("Output", juce::AudioChannelSet::stereo(), true)){
    
    
    
}
teleSynthAudioProcessor::~teleSynthAudioProcessor() {}

//==============================================================================
void teleSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    
    sliderSynthesiser.initaliseVoices(sampleRate, samplesPerBlock, getNumOutputChannels());
    
    
}
void teleSynthAudioProcessor::releaseResources() {
    
}

bool teleSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void teleSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) {
    
    juce::ScopedNoDenormals noDenormals;
    
    sliderSynthesiser.renderNextBlock(buffer, 0, buffer.getNumSamples()); 
    
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

