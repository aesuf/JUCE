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
class DistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        private juce::ComboBox::Listener
{                       
public:
    DistortionAudioProcessorEditor (DistortionAudioProcessor&);
    ~DistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox*) override;

private:
    

    juce::Slider driveSlider;
    juce::ComboBox typeBox;

    // Attachment namespace to cleanup code
    using SliderAttachments = juce::AudioProcessorValueTreeState::SliderAttachment;

    // attachment must destroy itself before the driveslider (bottom up)
    std::unique_ptr<SliderAttachments> driveSliderAttachment;

    using BoxAttachments = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    std::unique_ptr<BoxAttachments> typeBoxAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};
