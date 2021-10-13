/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define MAXDEL_S 5
#define MAX_FS 96000

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
    juce::LinearSmoothedValue<float> DelGainL{ 0.0 };
    juce::LinearSmoothedValue<float> DelAmntL{ 0.0 };
    juce::LinearSmoothedValue<float> DelGainR{ 0.0 };
    juce::LinearSmoothedValue<float> DelAmntR{ 0.0 };
    float del_buf[MAXDEL_S * MAX_FS][2];
    int buf_size = MAXDEL_S * MAX_FS;
    int readIndex[2] = { 0 };
    int writeIndex[2] = { 0 };
    int buf_inc(int,int);
    int buf_dec_am(int,int,int);
    //float Get_Gain(int);
    //float Get_Delay(int);
    
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
