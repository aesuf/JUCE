/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Distortion_ProjectAudioProcessorEditor::Distortion_ProjectAudioProcessorEditor (Distortion_ProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    getLookAndFeel().setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::transparentWhite);
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::aqua);
    driveSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::aqua);
    driveSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.5f, 0.4f, 0.3f, 1.0f));
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.5f, 0.4f,0.7f,1.0f));
    
    getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, juce::Colours::antiquewhite);
    
    
    getLookAndFeel().setDefaultSansSerifTypefaceName("Roboto");

    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 1 - 25), (getHeight() / 2) + 5 - (25 / 2))), true, 50, 25);
    //Set GUI element parameters	

    clipSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::aqua);
    clipSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.5f, 0.2f, 0.7f, 1.0f));
    
    clipSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    clipSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 25);

    
    
    
    typeBox.addItem("Soft", 1);
    typeBox.addItem("Hard", 2);
    
    typeBox.setJustificationType(juce::Justification::centred);
    //Add parts to GUI	
    addAndMakeVisible(driveSlider);
    addAndMakeVisible(clipSlider);
    addAndMakeVisible(&typeBox);
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(NameLabel);
    
    driveSlider.addListener(this);
    clipSlider.addListener(this);
    typeBox.addListener(this); //typeBox uses listener	
    
    driveSlider.setLookAndFeel(&otherLookAndFeel);
    clipSlider.setLookAndFeel(&otherLookAndFeel);

    driveSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    clipSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    
    
    //Conect GUI object attachments to plugin processor	
    driveSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "DRIVE", driveSlider);
    typeBoxAttachment = std::make_unique<BoxAttachments>(audioProcessor.apvts,
        "TYPE", typeBox);
    clipSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "CLIP", clipSlider);
    // Make sure that before the constructor has finished, you've set the	
    // editor's size to whatever you need it to be.	
    setSize(600, 400);
}

Distortion_ProjectAudioProcessorEditor::~Distortion_ProjectAudioProcessorEditor()
{
}

//==============================================================================
void Distortion_ProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)	
    juce::Colour c1 = juce::Colour(0.52f, 0.4f, 0.2f, 0.8f);
    juce::Colour c2 = juce::Colours::black;
    juce::ColourGradient g1 = juce::ColourGradient(c1, 0.0f, 0.0f, c2.brighter(0.2f), static_cast<int>(getRight()), static_cast<int>(getBottom()), true);
    g.setGradientFill(g1);
    g.fillAll();
    g.setColour(juce::Colours::whitesmoke);
    g.setFont(20.0f);

    //g.setFont(juce::Font(40.0f).withHorizontalScale(0.5f));
    g.drawText("DRIVE", ((getWidth() / 5) * 1) - driveSlider.getWidth()/2, (getHeight() / 2) + driveSlider.getHeight()/20, 100, 100, juce::Justification::centred, false);
    g.drawText("CLIP", ((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    //g.drawText("U F A E S", 500, 0, 100, 100, juce::Justification::centred, false);
    //g.drawEllipse(getWidth() / 5  - (25), getHeight() / 2 - 25, driveSlider.getWidth()/2, driveSlider.getHeight()/2, 0.5f);

    titleLabel.setText("U F A E S", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::right);

    NameLabel.setFont(juce::Font(25.0f, juce::Font::bold));
    NameLabel.setText("T A K E 1", juce::dontSendNotification);
    NameLabel.setJustificationType(juce::Justification::left);
    
}


void Distortion_ProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any	
       // subcomponents in your editor..	
    driveSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    clipSlider.setBounds(((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    juce::Rectangle<int> area = getLocalBounds().reduced(60);
    typeBox.setBounds(area.removeFromTop(20));

    titleLabel.setBounds(10, 10, getWidth() - 20, 30);
    NameLabel.setBounds(10, 10, getWidth() - 20, 30);

}

void Distortion_ProjectAudioProcessorEditor::comboBoxChanged(juce::ComboBox* box)
{
}

void Distortion_ProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slide)
{
    float driveValue = driveSlider.getValue()/10.0;
    float clipValue = clipSlider.getValue();
    float driveBrightness = juce::jlimit(0.5f, 0.7f, driveValue); 
    float clipBrightness = juce::jlimit(0.5f, 0.7f, clipValue);
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f, driveBrightness, 1.0f));
    clipSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f,clipBrightness, 1.0f));
    
    
}


OtherLookAndFeel::OtherLookAndFeel()
{
}

OtherLookAndFeel::~OtherLookAndFeel()
{
}


//namespace juce
//{
    void OtherLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
    {
        auto outline = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
        auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId);

        auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);

        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = juce::jmin(4.0f, radius * 0.2f);
        auto arcRadius = radius - lineW * 0.5f;

        juce::Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            juce::Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);
            g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

            g.setColour(juce::Colour::Colour(0.52f, 0.4f, 0.5f, 0.2f));
            auto bounds1 = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10+lineW);
            g.fillEllipse(bounds1.getX(), bounds1.getY(), bounds1.getWidth(), bounds1.getHeight());
        }

        auto thumbWidth = lineW * 0.5f;
        juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
            bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

        g.setColour(slider.findColour(juce::Slider::thumbColourId));
        g.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
    }
//}

