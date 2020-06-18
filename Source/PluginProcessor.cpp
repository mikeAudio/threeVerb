
#include "PluginProcessor.h"
#include "PluginEditor.h"

ThreeVerbAudioProcessor::ThreeVerbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ThreeVerbAudioProcessor::~ThreeVerbAudioProcessor()
{
}

const String ThreeVerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ThreeVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ThreeVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ThreeVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ThreeVerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ThreeVerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ThreeVerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ThreeVerbAudioProcessor::setCurrentProgram (int index)
{
}

const String ThreeVerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void ThreeVerbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void ThreeVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    threeVerb.reset();
    threeVerb.setSampleRate(sampleRate);
    
}

void ThreeVerbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ThreeVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ThreeVerbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    

        auto const channelPointer1 = buffer.getWritePointer(0);
        auto const channelPointer2 = buffer.getWritePointer(1);
        auto const channelPointer3 = buffer.getWritePointer(2);
    
    threeVerb.processStereo(channelPointer1, channelPointer2, buffer.getNumSamples());
        

    
    
    
    
}
bool ThreeVerbAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ThreeVerbAudioProcessor::createEditor()
{
    return new ThreeVerbAudioProcessorEditor (*this);
}

void ThreeVerbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ThreeVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ThreeVerbAudioProcessor();
}
