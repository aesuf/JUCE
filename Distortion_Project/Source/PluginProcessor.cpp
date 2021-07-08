/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Distortion_ProjectAudioProcessor::Distortion_ProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters()) /*PUT THIS IN FOR APVTS*/
#endif
{
}

Distortion_ProjectAudioProcessor::~Distortion_ProjectAudioProcessor()
{
}

//==============================================================================
const juce::String Distortion_ProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Distortion_ProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Distortion_ProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Distortion_ProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Distortion_ProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Distortion_ProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Distortion_ProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Distortion_ProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Distortion_ProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void Distortion_ProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Distortion_ProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Distortion_ProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Distortion_ProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void Distortion_ProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //Load variables from APVTS
    auto drive = apvts.getRawParameterValue("DRIVE");
    drive->load();
  

    auto type = apvts.getRawParameterValue("TYPE");
    type->load();

    auto clip = apvts.getRawParameterValue("CLIP");
    clip->load();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        //Soft Clip
        if (*type == 0.0)
        {
            for (auto sample = 0; sample < buffer.getNumSamples(); sample++)
            {
                float val = channelData[sample];
                channelData[sample] = (2.f / juce::float_Pi) * atan(val * *drive);
            }
        }
        //Hard Clip
        else if (*type == 1.0)
        {
            for (auto i = 0; i < buffer.getNumSamples(); i++)
            {
                float val = channelData[i] * *drive;
                channelData[i] = juce::jlimit(-1 * *clip, 1 * *clip, val);
            }
        }
        /*
        //Chebyshev
        else if (*type == 2.0)
        {
            for (auto i = 0; i < buffer.getNumSamples(); i++)
            {
                float val = channelData[i] * *drive;
                channelData[i] = (4 * pow(val,3) - 3 * val) + (2 * pow(val,2) - 1) + val + 1;
            }
        }*/
    }
}

//==============================================================================
bool Distortion_ProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Distortion_ProjectAudioProcessor::createEditor()
{
    return new Distortion_ProjectAudioProcessorEditor (*this);
}

//==============================================================================
void Distortion_ProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Distortion_ProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Distortion_ProjectAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Distortion_ProjectAudioProcessor::createParameters()
{
    using RangedParam = std::vector<std::unique_ptr<juce::RangedAudioParameter>>;
    RangedParam params; //vector of RangedAudioParameter's for variables

    //Add params with ID, Name, min, max, default
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DRIVE", "Drive", 1.0f, 10.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("TYPE", "Type", 0.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CLIP", "Clip", 0.0f, 1.0f, 1.0f));

    return { params.begin(), params.end() };

}