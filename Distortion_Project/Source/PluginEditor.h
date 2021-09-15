/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <functional>

//==============================================================================
/**
*/



// Derived class from LookAndFeel_V4
class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:

    /** Creates a LookAndFeel_V4 object with a default colour scheme. */
    // Default Constructor
    OtherLookAndFeel();

    /** Creates a LookAndFeel_V4 object with a given colour scheme. */
    // Custom Constructor
    OtherLookAndFeel(ColourScheme);

    /** Destructor. */
    ~OtherLookAndFeel() override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider&) override;

};

class mySlider : public juce::Slider
{
public:
    mySlider();
    ~mySlider();
    void mouseDown(const juce::MouseEvent&);


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

    // LookandFeel classes need to be implemented before the component
    OtherLookAndFeel otherLookAndFeel;

    //Create GUI objects
    mySlider inGainSlider;
    mySlider outGainSlider;
    mySlider driveSlider;
    mySlider clipSlider;   
    mySlider clipSliderNeg;
    mySlider highPassSlider;
    mySlider lowPassSlider;
    juce::ComboBox typeBox;

    // Create Label Objects
    juce::Label titleLabel;
    juce::Label NameLabel;        

    // Use namespaces to cleanup code for TreeState Attachments
    using SliderAttachments = juce::AudioProcessorValueTreeState::SliderAttachment;
    using BoxAttachments = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    // Create GUI attachment objects to connect to APVTS object in processor
    std::unique_ptr<SliderAttachments> driveSliderAttachment;
    std::unique_ptr<BoxAttachments> typeBoxAttachment;
    std::unique_ptr<SliderAttachments> clipSliderAttachment;
    std::unique_ptr<SliderAttachments> inGainSliderAttachment;
    std::unique_ptr<SliderAttachments> outGainSliderAttachment;
    std::unique_ptr<SliderAttachments> clipSliderNegAttachment;
    std::unique_ptr<SliderAttachments> highPassSliderAttachment;
    std::unique_ptr<SliderAttachments> lowPassSliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion_ProjectAudioProcessorEditor)
};
