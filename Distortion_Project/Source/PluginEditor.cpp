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
    
    // General Font and Colour Settings
    getLookAndFeel().setDefaultSansSerifTypefaceName("Roboto");
    getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, juce::Colours::antiquewhite);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::transparentWhite);

    // inGainSlider Colours
    inGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    inGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f, 0.7f, 1.0f));
    inGainSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // inGainSliderStyle and position
    inGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    inGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 1 - 25), (getHeight() / 2) + 5 - (25 / 2))), true, 50, 25);

    // outGainSlider Colours
    outGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    outGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f, 0.7f, 1.0f));
    outGainSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // outGainSlider Style and position
    outGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 2 - 25), (getHeight() / 4) + 5 - (25 / 2))), true, 50, 25);

    // driveSlider Colours
    driveSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f,0.7f,1.0f));
    driveSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // driveSlider Style and position
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 2 - 25), (getHeight() / 2) + 5 - (25 / 2))), true, 50, 25);	

    // clipSlider Colours
    clipSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    clipSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f, 0.7f, 1.0f));
    clipSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    
    // clipSlider Style and position
    clipSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    clipSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 1 - 25), (getHeight() / 4) + 5 - (25 / 2))), true, 50, 25);
    // qSlider Colours
    qSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    qSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f, 0.7f, 1.0f));
    qSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // qslider Style and position
    qSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    qSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 4 - 25), (getHeight() / 4) + 5 - (25 / 2))), true, 50, 25);
    
    // highFreqSlider Colours
    highFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    highFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f, 0.7f, 1.0f));
    highFreqSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // highFreqSlider Style and position
    highFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    highFreqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 3 - 25), (getHeight() / 4) + 5 - (25 / 2))), true, 50, 25);

    // lowFreqSlider Colours
    lowFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    lowFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::Colour(0.52f, 0.4f, 0.7f, 1.0f));
    lowFreqSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // lowFreqSlider Style and position
    lowFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowFreqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 1 - 25), (getHeight() / 6) + 5 - (25 / 2))), true, 50, 25);


    // Add items to ComboBox
    typeBox.addItem("Soft", 1);
    typeBox.addItem("Hard", 2);
    typeBox.addItem("Chebyshev", 3);
    typeBox.setJustificationType(juce::Justification::centred);  

    // Add components to GUI	
    addAndMakeVisible(driveSlider);
    addAndMakeVisible(clipSlider);
    addAndMakeVisible(inGainSlider);
    addAndMakeVisible(outGainSlider);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(highFreqSlider);
    addAndMakeVisible(lowFreqSlider);
    addAndMakeVisible(&typeBox);
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(NameLabel);
    addAndMakeVisible(audioProcessor.visualiser);

    
    // Add Listeners 
    inGainSlider.addListener(this);
    outGainSlider.addListener(this);
    driveSlider.addListener(this);
    clipSlider.addListener(this); 
    qSlider.addListener(this);
    highFreqSlider.addListener(this);
    lowFreqSlider.addListener(this);
    typeBox.addListener(this); //typeBox requires listener


    //
    driveSlider.addMouseListener(this, false);
    
    // Use custom lookandfeel 
    inGainSlider.setLookAndFeel(&otherLookAndFeel);
    outGainSlider.setLookAndFeel(&otherLookAndFeel);
    driveSlider.setLookAndFeel(&otherLookAndFeel);
    clipSlider.setLookAndFeel(&otherLookAndFeel);
    qSlider.setLookAndFeel(&otherLookAndFeel);
    highFreqSlider.setLookAndFeel(&otherLookAndFeel);
    lowFreqSlider.setLookAndFeel(&otherLookAndFeel);
    //Pimpl(Slider & s, SliderStyle sliderStyle, TextEntryBoxPosition textBoxPosition)
    

    //Conect GUI object attachments to plugin processor
    inGainSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "INGAIN", inGainSlider);
    outGainSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "OUTGAIN", outGainSlider);
    driveSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "DRIVE", driveSlider);
    typeBoxAttachment = std::make_unique<BoxAttachments>(audioProcessor.apvts,
        "TYPE", typeBox);
    clipSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "CLIP", clipSlider);
    qSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "Q", qSlider);
    highFreqSlideAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "HIGHFREQCUTOFF", highFreqSlider);
    lowFreqSlideAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "LOWFREQCUTOFF", lowFreqSlider);

    // Make sure that before the constructor has finished, you've set the	
    // editor's size to whatever you need it to be.	
    setSize(800, 600);
}

// Editor Destructor
Distortion_ProjectAudioProcessorEditor::~Distortion_ProjectAudioProcessorEditor()
{
    inGainSlider.setLookAndFeel(nullptr);
    outGainSlider.setLookAndFeel(nullptr);
    driveSlider.setLookAndFeel(nullptr);
    clipSlider.setLookAndFeel(nullptr);
    qSlider.setLookAndFeel(nullptr);
    highFreqSlider.setLookAndFeel(nullptr);
    lowFreqSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void Distortion_ProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Color Gradient for Background
    juce::Colour colorAqua = juce::Colour(0.52f, 0.4f, 0.2f, 0.8f);
    juce::Colour colorBlack = juce::Colours::black;
    juce::ColourGradient g1 = juce::ColourGradient(colorAqua, 0.0f, 0.0f, colorBlack.brighter(0.2f), static_cast<float>(getRight()), static_cast<float>(getBottom()), true);
    g.setGradientFill(g1);
    g.fillAll();

    // Set font colour and size
    g.setColour(juce::Colours::whitesmoke);
    g.setFont(20.0f);

    // Text for Sliders 
    // **********************************(Should change these to labels!!)**********************************************
    g.drawText("INGAIN", ((getWidth() / 5) * 1) - driveSlider.getWidth()/2, (getHeight() / 4) + driveSlider.getHeight()/20, 100, 100, juce::Justification::centred, false);
    g.drawText("DRIVE", ((getWidth() / 5) * 2) - driveSlider.getWidth() / 2, (getHeight() / 4) + driveSlider.getHeight() / 20, 100, 100, juce::Justification::centred, false);
    g.drawText("CLIP", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("OUTGAIN", ((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("Q", ((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("HIGHFREQCUTOFF", ((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("LOWFREQCUTOFF", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 1) + 5, 100, 100, juce::Justification::centred, false);

    // Label for Name of our Organization
    titleLabel.setText("U F A E S", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::right);

    // Label for Name of Plugin
    NameLabel.setFont(juce::Font(25.0f, juce::Font::bold));
    NameLabel.setText("T A K E 2", juce::dontSendNotification);
    NameLabel.setJustificationType(juce::Justification::left);


    
}

// Layout of subcomponents in editor
void Distortion_ProjectAudioProcessorEditor::resized()
{   
    // Slider Bounds
    inGainSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2),
        (getHeight() / 4) - (100 / 2), 100, 100);
    driveSlider.setBounds(((getWidth() / 5) * 2) - (100 / 2),
        (getHeight() / 4) - (100 / 2), 100, 100);
    clipSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2),
        (getHeight() / 2) - (100 / 2), 100, 100);  
    outGainSlider.setBounds(((getWidth() / 5) * 2) - (100 / 2), 
        (getHeight() / 2) - (100 / 2), 100, 100);
    qSlider.setBounds(((getWidth() / 5) * 4) - (100 / 2),
        (getHeight() / 2) - (100 / 2), 100, 100);
    highFreqSlider.setBounds(((getWidth() / 5) * 3) - (100 / 2),
        (getHeight() / 2) - (100 / 2), 100, 100);
    lowFreqSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2),
        (getHeight() / 1) - (100 / 2), 100, 100);

    // ComboBox Bounds
    juce::Rectangle<int> area = getLocalBounds().reduced(60);
    typeBox.setBounds(area.removeFromTop(20));

    // Label Bounds
    titleLabel.setBounds(10, 10, getWidth() - 20, 30);
    NameLabel.setBounds(10, 10, getWidth() - 20, 30);

    audioProcessor.visualiser.setBounds(getWidth()-getWidth()/2, 100, getWidth() / 3, 150);
}

// Listener Function for ComboBox (Code is purposefully empty...)
void Distortion_ProjectAudioProcessorEditor::comboBoxChanged(juce::ComboBox* box)
{
    ignoreUnused(box);
}

// Listener function for Slider
void Distortion_ProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slide)
{
    ignoreUnused(slide);
    // Get Values of sliders
    float driveValue = static_cast<float>(((driveSlider.getValue()/100.0)*0.2)+0.5);
    float clipValue = static_cast<float>(((clipSlider.getValue()+ 40.0)/40.0) * 0.2 + 0.5);
    float inGainValue = static_cast<float>(((inGainSlider.getValue() + 40.0) / 80.0) * 0.2 + 0.5);
    float outGainValue = static_cast<float>(((outGainSlider.getValue() + 40.0) / 80.0) * 0.2 + 0.5);
    float qValue = static_cast<float>(outGainSlider.getValue());
    float highPassFreqValue = static_cast<float>(highFreqSlider.getValue());
    float lowPassFreqValue = static_cast<float>(lowFreqSlider.getValue());
    // Limit Brightness between specific range
    //float driveBrightness = juce::jlimit(0.5f, 0.7f, driveValue); 
    //float clipBrightness = juce::jlimit(0.5f, 0.7f, clipValue);
    //float inGainBrightness = juce::jlimit(0.5f, 0.7f, inGainValue);
    //float outGainBrightness = juce::jlimit(0.5f, 0.7f, outGainValue);

    // Set Brightness Parameter of the Colour
    // Colour(float Hue, float Saturation, float Brightness, float Alpha)
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, 
        juce::Colour::Colour(0.52f, 0.4f, driveValue, 1.0f));
    clipSlider.setColour(juce::Slider::rotarySliderFillColourId, 
        juce::Colour::Colour(0.52f, 0.4f,clipValue, 1.0f));
    inGainSlider.setColour(juce::Slider::rotarySliderFillColourId,
        juce::Colour::Colour(0.52f, 0.4f, inGainValue, 1.0f));
    outGainSlider.setColour(juce::Slider::rotarySliderFillColourId,
        juce::Colour::Colour(0.52f, 0.4f, outGainValue, 1.0f));
    qSlider.setColour(juce::Slider::rotarySliderFillColourId,
        juce::Colour::Colour(0.52f, 0.4f, inGainValue, 1.0f));
    highFreqSlider.setColour(juce::Slider::rotarySliderFillColourId,
        juce::Colour::Colour(0.52f, 0.4f, highPassFreqValue, 1.0f));
    lowFreqSlider.setColour(juce::Slider::rotarySliderFillColourId,
        juce::Colour::Colour(0.52f, 0.4f, lowPassFreqValue, 1.0f));
}

// Default Constructor
OtherLookAndFeel::OtherLookAndFeel()
{
}

// Destructor
OtherLookAndFeel::~OtherLookAndFeel()
{
}

// DrawRotarySlider function from the OtherLookAndFeel class
void OtherLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{

    // When copying code from pre-made juce functions, you need to add 
    // the juce namespace to the front of the objects!!
    auto outline = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId);

    // This is the bounds of the slider - very useful!!
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // This is the line width of the slider - very useful!!!
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

        // Set the colour of the Ellipse to be drawn
        // Colour(float Hue, float Saturation, float Brightness, float Alpha)
        g.setColour(juce::Colour::Colour(0.52f, 0.4f, 0.19f, 0.6f));

        // Set the bounds of the ellipse to be just inside the arc line of the slider
        // This is the bounds of the slider reduced by the linewidth (see the beginning of this function)
        auto ellipseBounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10+lineW);

        // Create a filled ellipse with the new bounds
        // fillEllipse(float x, float y, float width, float height)
        g.fillEllipse(ellipseBounds.getX(), ellipseBounds.getY(), ellipseBounds.getWidth(), ellipseBounds.getHeight());
    }

    // This is the thumb of the slider, the circle at the end, or indicator point
    auto thumbWidth = lineW * 0.5f;
    juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

    // Sets the color of the slider thumb
    g.setColour(slider.findColour(juce::Slider::thumbColourId));
    g.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
}

mySlider::mySlider()
{
}

mySlider::~mySlider()
{
}

void mySlider::mouseDown(const juce::MouseEvent& e)
{
    if (juce::ModifierKeys::getCurrentModifiers().isRightButtonDown())
    {
        juce::PopupMenu m;
        m.addItem(1, "Do something Here");
        //m.addItem(2, "item 2");

        const int result = m.show();

        if (result == 0)
        {
            // user dismissed the menu without picking anything
        }
        else if (result == 1)
        {
            // user picked item 1
        }
        else if (result == 2)
        {
            // user picked item 2
        }
    }
    else
    {       
        Slider::mouseDown(e);
    }
   
}
