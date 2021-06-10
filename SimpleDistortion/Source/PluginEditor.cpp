/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDistortionAudioProcessorEditor::SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    //Set GUI element parameters
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);

    typeBox.addItem("Soft", 1);
    typeBox.addItem("Hard", 2);

    clipSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    clipSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);

    typeBox.setJustificationType(juce::Justification::centred);

    //Add parts to GUI
    addAndMakeVisible(driveSlider);
    addAndMakeVisible(&typeBox);
    addAndMakeVisible(clipSlider);
    typeBox.addListener(this); //typeBox uses listener

    //Conect GUI object attachments to plugin processor
    driveSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "DRIVE", driveSlider);

    typeBoxAttachment = std::make_unique<BoxAttachments>(audioProcessor.apvts,
        "TYPE", typeBox);

    clipSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "CLIP", clipSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

SimpleDistortionAudioProcessorEditor::~SimpleDistortionAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawText("Drive", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("Clip", ((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
}

void SimpleDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    driveSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);

    clipSlider.setBounds(((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    typeBox.setBounds(area.removeFromTop(20));
}

void SimpleDistortionAudioProcessorEditor::comboBoxChanged(juce::ComboBox* box)
{

}