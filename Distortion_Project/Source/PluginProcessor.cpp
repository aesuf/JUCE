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
                       ), apvts(*this, nullptr, "Parameters", createParameters()), visualiser() /*PUT THIS IN FOR APVTS*/

#endif
{
    apvts.state.addListener(this);
    init();
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
    juce::ignoreUnused(index);
}

const juce::String Distortion_ProjectAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused(index);
    return {};
}

void Distortion_ProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(newName);
    juce::ignoreUnused(index);
}

//==============================================================================
void Distortion_ProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need.
    prepare(sampleRate, samplesPerBlock);
    update();
    reset();
    isActive = true;
    
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
    // This is to update the variables
    juce::ignoreUnused(midiMessages);
    if (!isActive)
    {
        return;
    }
    if (mustUpdateProcessing)
    {
        update();
    }

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    /*
    You have access to the following variables in the process block:
        driveNormal     - drive slider
        clipNormal      - hard clip threshold
        inGainNormal    - input gain
        outGainNormal   - output gain
        typeNormal      - type of distortion (comboBox)   


        *** You do not need to use pointers on the variables ***
    */

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //driveNormal.applyGain(buffer, buffer.getNumSamples());
    //clipNormal.applyGain(buffer, buffer.getNumSamples());
    inGainNormal.applyGain(buffer, buffer.getNumSamples());
    


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        //Soft Clip
        if (typeNormal == 0.0)
        {
            for (auto sample = 0; sample < buffer.getNumSamples(); sample++)
            {
                float val = channelData[sample];
                channelData[sample] = (2.f / juce::float_Pi) * atan(val * driveNormal.getCurrentValue());
            }
        }
        //Hard Clip
        else if (typeNormal == 1.0)
        {
            for (auto i = 0; i < buffer.getNumSamples(); i++)
            {
                float val = channelData[i] * driveNormal.getCurrentValue();
                channelData[i] = juce::jlimit(-1 * clipNormal.getCurrentValue(), 1 * clipNormal.getCurrentValue(), val);
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
    outGainNormal.applyGain(buffer, buffer.getNumSamples());
    visualiser.pushBuffer(buffer);
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
    juce::ValueTree copyState = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml = copyState.createXml();
    copyXmlToBinary(*xml.get(), destData);

    // juce::ignoreUnused(destData);
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Distortion_ProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //juce::ignoreUnused(data);
    //juce::ignoreUnused(sizeInBytes);

    std::unique_ptr<juce::XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    juce::ValueTree copyState = juce::ValueTree::fromXml(*xml.get());
    apvts.replaceState(copyState);
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void Distortion_ProjectAudioProcessor::init()
{
}

void Distortion_ProjectAudioProcessor::prepare(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate);
    juce::ignoreUnused(samplesPerBlock);
}

void Distortion_ProjectAudioProcessor::update()
{
    mustUpdateProcessing = false;

    //Load variables from APVTS
    auto drive = apvts.getRawParameterValue("DRIVE");
    driveNormal = drive->load();

    auto type = apvts.getRawParameterValue("TYPE");
    typeNormal = type->load();

    auto clip = apvts.getRawParameterValue("CLIP");
    clipNormal = juce::Decibels::decibelsToGain(clip->load());

    auto inGain = apvts.getRawParameterValue("INGAIN");
    inGainNormal.setTargetValue(juce::Decibels::decibelsToGain(inGain->load()));

    auto outGain = apvts.getRawParameterValue("OUTGAIN");
    outGainNormal.setTargetValue(juce::Decibels::decibelsToGain(outGain->load()));
}

void Distortion_ProjectAudioProcessor::reset()
{
    driveNormal.reset(getSampleRate(), 0.050);
    clipNormal.reset(getSampleRate(), 0.050);
    inGainNormal.reset(getSampleRate(), 0.050);
    outGainNormal.reset(getSampleRate(), 0.050);
    visualiser.clear();
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

    std::function<juce::String(float, int)> valueToTextFunction = [](float x, int l) 
    { 
        juce::ignoreUnused(l);
        return juce::String(x, 1, false); 
    }; 
    std::function<float (const juce::String &str)> textToValueFunction = [](const juce::String& str) { return str.getFloatValue(); };

    auto inGainParam = std::make_unique<juce::AudioParameterFloat>("INGAIN", "Input Gain", 
        juce::NormalisableRange<float>(-40.0f,40.0f, 0.1f), 0.0f, "dB", juce::AudioProcessorParameter::genericParameter, valueToTextFunction, textToValueFunction);

    auto outGainParam = std::make_unique<juce::AudioParameterFloat>("OUTGAIN", "Output Gain",
        juce::NormalisableRange<float>(-40.0f, 40.0f, 0.1f), 0.0f, "dB", juce::AudioProcessorParameter::genericParameter, valueToTextFunction, textToValueFunction);

    auto driveParam = std::make_unique<juce::AudioParameterFloat>("DRIVE", "Drive",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 20.0f, "%", juce::AudioProcessorParameter::genericParameter, valueToTextFunction, textToValueFunction);
    auto clipParam = std::make_unique<juce::AudioParameterFloat>("CLIP", "Threshold",
        juce::NormalisableRange<float>(-40.0f, 0.0f, 0.1f), 0.0f, "dB", juce::AudioProcessorParameter::genericParameter, valueToTextFunction, textToValueFunction);

    juce::StringArray choices;
    choices.add("Soft");
    choices.add("Hard");

    auto typeParam = std::make_unique<juce::AudioParameterChoice>("TYPE", "Type", choices, 0, "Type", valueToTextFunction, textToValueFunction);

    params.push_back(std::move(inGainParam));
    params.push_back(std::move(outGainParam));
    params.push_back(std::move(driveParam));
    params.push_back(std::move(clipParam));
    params.push_back(std::move(typeParam));

    
    

    

    return { params.begin(), params.end() };

}