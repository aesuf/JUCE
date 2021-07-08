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
class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:

    /** Creates a LookAndFeel_V4 object with a default colour scheme. */
    OtherLookAndFeel();

    /** Creates a LookAndFeel_V4 object with a given colour scheme. */
    OtherLookAndFeel(ColourScheme);

    /** Destructor. */
    ~OtherLookAndFeel() override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider&) override;

};

class Distortion_ProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                private juce::ComboBox::Listener,
                                                private juce::Slider::Listener
{
public:
    Distortion_ProjectAudioProcessorEditor (Distortion_ProjectAudioProcessor&);
    ~Distortion_ProjectAudioProcessorEditor() override;
    void comboBoxChanged(juce::ComboBox*) override; //Combo box function
    void sliderValueChanged(juce::Slider*); // Slider function

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Distortion_ProjectAudioProcessor& audioProcessor;

    OtherLookAndFeel otherLookAndFeel;

    //Create GUI objects
    juce::Slider driveSlider;
    juce::ComboBox typeBox;
    juce::Slider clipSlider;

    juce::Label titleLabel;
    juce::Label NameLabel;

    

    // Use namespaces to cleanup code
    using SliderAttachments = juce::AudioProcessorValueTreeState::SliderAttachment;
    using BoxAttachments = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    // Create GUI attachment objects to connect to APVTS object in processor
    std::unique_ptr<SliderAttachments> driveSliderAttachment;
    std::unique_ptr<BoxAttachments> typeBoxAttachment;
    std::unique_ptr<SliderAttachments> clipSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion_ProjectAudioProcessorEditor)
};
