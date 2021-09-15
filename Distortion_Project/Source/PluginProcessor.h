/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Visualiser : public juce::AudioVisualiserComponent
{
public:
    Visualiser() : AudioVisualiserComponent(2)
    {
        setBufferSize(128);
        setSamplesPerBlock(16);
        setColours(juce::Colours::dimgrey, juce::Colours::antiquewhite);
        setRepaintRate(16);
    }
private:
};

class Distortion_ProjectAudioProcessor  : public juce::AudioProcessor,
                                          public juce::ValueTree::Listener
{
public:
    //==============================================================================
    Distortion_ProjectAudioProcessor();
    ~Distortion_ProjectAudioProcessor() override;

   

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
    void releaseResources() override;
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void init(); // Called once -- give initial values to DSP
    void prepare(double sampleRate, int samplesPerBlock); // Pass sample rate/buffer size to DSP
    void update(); // Update DSP when a user changes parameters
    void reset() override; // Reset DSP parameters
    juce::AudioProcessorValueTreeState apvts; //Create APVTS object to connect to editor
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    Visualiser visualiser;
private:    
    bool isActive{ false };
    bool mustUpdateProcessing{ false };
    float typeNormal { 0.0 };
    juce::LinearSmoothedValue<float> inGainNormal{ 0.0 };
    juce::LinearSmoothedValue<float> outGainNormal { 0.0 };
    juce::LinearSmoothedValue<float> driveNormal { 0.0 };
    juce::LinearSmoothedValue<float> clipNormal { 0.0 };
    juce::LinearSmoothedValue<float> clipNeg{ 0.0 };
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> hiPassCutoffFrequency{};
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> lowPassCutoffFrequency{};
    juce::dsp::StateVariableTPTFilter<float> highPass;
    
    juce::dsp::StateVariableTPTFilter<float> lowPass;
    
    //juce::dsp::ProcessSpec processSpec;
    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override
    {
        ignoreUnused(property);
        ignoreUnused(treeWhosePropertyHasChanged);
        // Detect when a user changes params
        mustUpdateProcessing = true;
    }
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion_ProjectAudioProcessor)
};
