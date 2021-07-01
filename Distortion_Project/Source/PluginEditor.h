/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                private juce::ComboBox::Listener
{
public:
    SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor&);
    ~SimpleDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox*) override; //Combo box function

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDistortionAudioProcessor& audioProcessor;

    //Create GUI objects
    juce::Slider driveSlider;
    juce::ComboBox typeBox;
    juce::Slider clipSlider;

    // Use namespaces to cleanup code
    using SliderAttachments = juce::AudioProcessorValueTreeState::SliderAttachment;
    using BoxAttachments = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    // Create GUI attachment objects to connect to APVTS object in processor
    std::unique_ptr<SliderAttachments> driveSliderAttachment;
    std::unique_ptr<BoxAttachments> typeBoxAttachment;
    std::unique_ptr<SliderAttachments> clipSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistortionAudioProcessorEditor)
};
