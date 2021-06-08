/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);

    typeBox.addItem("ArcTan", 1);
    typeBox.addItem("Tape", 2);
    typeBox.addItem("Hard", 3);

    bitSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    bitSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);

    foldSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    foldSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);

    typeBox.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(driveSlider);
    addAndMakeVisible(&typeBox);
    addAndMakeVisible(bitSlider);
    addAndMakeVisible(foldSlider);
    typeBox.addListener(this);

    driveSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts, 
        "DRIVE", driveSlider);

    typeBoxAttachment = std::make_unique<BoxAttachments>(audioProcessor.apvts,
        "TYPE", typeBox);

    bitSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "BITS", bitSlider);

    foldSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "FOLD", foldSlider);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 400);
}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    g.drawText("Drive", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("Bitcrusher", ((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("Fold", ((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
}

void DistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    driveSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - (100/2), 100, 100);

    bitSlider.setBounds(((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);

    foldSlider.setBounds(((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    typeBox.setBounds(area.removeFromTop(20));

    //typeBox.setBounds(((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 5) - (100 / 2), 100, 100);
}

void DistortionAudioProcessorEditor::comboBoxChanged(juce::ComboBox* box)
{
  
}
