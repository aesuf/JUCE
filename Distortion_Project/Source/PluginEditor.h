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
class Distortion_ProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                private juce::ComboBox::Listener
{
public:
    Distortion_ProjectAudioProcessorEditor (Distortion_ProjectAudioProcessor&);
    ~Distortion_ProjectAudioProcessorEditor() override;
    void comboBoxChanged(juce::ComboBox*) override; //Combo box function

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Distortion_ProjectAudioProcessor& audioProcessor;

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion_ProjectAudioProcessorEditor)
};
