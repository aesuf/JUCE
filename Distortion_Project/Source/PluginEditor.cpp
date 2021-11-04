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
    getLookAndFeel().setDefaultSansSerifTypeface(tface);
    getLookAndFeel().getComboBoxFont(typeBox).setHeight(35);
    


    
    //outline color for all the sliders
    auto sliderOutlineColor = juce::Colour(0.6305555555f, 0.38f, 1.0f, 0.3f);
   
    
    //fill Color default. should be the same as the color in
    // getFillColor() lambda function
    
    auto fillColor = juce::Colour(0.633333f, 1.0f, .7f, 1.0f);
    inGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, sliderOutlineColor);
    inGainSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColor);
    inGainSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // inGainSliderStyle and position
    inGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    inGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 1 - 25), (getHeight() / 2) + 5 - (25 / 2))), true, 50, 25);

    // outGainSlider Colours
    outGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, sliderOutlineColor);
    outGainSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColor);
    outGainSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // outGainSlider Style and position
    outGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 2 - 25), (getHeight() / 4) + 5 - (25 / 2))), true, 50, 25);

    // driveSlider Colours
    driveSlider.setColour(juce::Slider::rotarySliderOutlineColourId, sliderOutlineColor);
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColor);
    driveSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // driveSlider Style and position
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 2 - 25), (getHeight() / 2) + 5 - (25 / 2))), true, 50, 25);	

    // clipSlider Colours
    clipSlider.setColour(juce::Slider::rotarySliderOutlineColourId, sliderOutlineColor);
    clipSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColor);
    clipSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    
    // clipSlider Style and position
    clipSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    clipSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 5) * 1 - 25), (getHeight() / 4) + 5 - (25 / 2))), true, 50, 25);
    
    // clipSliderNeg Colours added for experimentation 
    clipSliderNeg.setColour(juce::Slider::rotarySliderOutlineColourId, sliderOutlineColor);
    clipSliderNeg.setColour(juce::Slider::rotarySliderFillColourId, fillColor);
    clipSliderNeg.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);

    // clipSliderNeg Style and position
    clipSliderNeg.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    clipSliderNeg.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 3) * 1 - 25), (getHeight() / 2) + 5 - (25 / 2))), true, 50, 25);
    //highPassSlider colors
    highPassSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0.52f, 0.4f, 0.3f, 1.0f));
    highPassSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0.52f, 0.4f, 0.7f, 1.0f));
    highPassSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    //highPassSlider style and position
    highPassSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    highPassSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 3) * 4 - 25), (getHeight() / 1) + 5 - (25 / 2))), true, 50, 25);
    //lowPassSlider colors
    lowPassSlider.setColour(juce::Slider::rotarySliderOutlineColourId, sliderOutlineColor);
    lowPassSlider.setColour(juce::Slider::rotarySliderFillColourId, fillColor);
    lowPassSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    //LO2PassSlider style and position
    lowPassSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowPassSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition((((getWidth() / 3) * 4 - 25), (getHeight() / 2) + 5 - (25 / 2))), true, 50, 25);
    
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
    addAndMakeVisible(&typeBox);
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(NameLabel);
    addAndMakeVisible(audioProcessor.visualiser);
    addAndMakeVisible(clipSliderNeg);
    addAndMakeVisible(highPassSlider);
    addAndMakeVisible(lowPassSlider);
    
    // Add Listeners 
    inGainSlider.addListener(this);
    outGainSlider.addListener(this);
    driveSlider.addListener(this);
    clipSlider.addListener(this); 
    clipSliderNeg.addListener(this);
    typeBox.addListener(this); //typeBox requires listener
    highPassSlider.addListener(this);
    lowPassSlider.addListener(this);
    //
    driveSlider.addMouseListener(this, false);
    
    // Use custom lookandfeel 
    inGainSlider.setLookAndFeel(&otherLookAndFeel);
    outGainSlider.setLookAndFeel(&otherLookAndFeel);
    driveSlider.setLookAndFeel(&otherLookAndFeel);
    clipSlider.setLookAndFeel(&otherLookAndFeel);
    clipSliderNeg.setLookAndFeel(&otherLookAndFeel);
    highPassSlider.setLookAndFeel(&otherLookAndFeel);
    lowPassSlider.setLookAndFeel(&otherLookAndFeel);
    
    //Pimpl(Slider & s, SliderStyle sliderStyle, TextEntryBoxPosition textBoxPosition)
    

    //Connect GUI object attachments to plugin processor
    inGainSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "INGAIN", inGainSlider);
    outGainSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "OUTGAIN", outGainSlider);
    driveSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "DRIVE", driveSlider);
    typeBoxAttachment = std::make_unique<BoxAttachments>(audioProcessor.apvts,
        "TYPE", typeBox);
    clipSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "CLIPPOS", clipSlider);
    //added for experimentation 
    clipSliderNegAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "CLIPNEG", clipSliderNeg);
    highPassSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "HIGH(Hz)", highPassSlider);
    lowPassSliderAttachment = std::make_unique<SliderAttachments>(audioProcessor.apvts,
        "LOW(Hz)", lowPassSlider);

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
    clipSliderNeg.setLookAndFeel(nullptr);
    highPassSlider.setLookAndFeel(nullptr);
    lowPassSlider.setLookAndFeel(nullptr);
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

    // Set font colour and size and typeface
    auto gFont = juce::Font(tface);
    gFont.setHeight(35);
    g.setFont(gFont);
    g.setColour(juce::Colours::whitesmoke);
    
     
    // Text for Sliders 
    //ß **********************************(Should change these to labels!!)**********************************************
    g.drawText("ingain", ((getWidth() / 5) * 1) - driveSlider.getWidth()/2, (getHeight() / 4) + driveSlider.getHeight()/20, 100, 100, juce::Justification::centred, false);
    g.drawText("drive", ((getWidth() / 5) * 2) - driveSlider.getWidth() / 2, (getHeight() / 4) + driveSlider.getHeight() / 20, 100, 100, juce::Justification::centred, false);
    g.drawText("clip pos", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("outgain", ((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("clipneg", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 1.38) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("high", ((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("low", ((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 1.38) + 5, 100, 100, juce::Justification::centred, false);

    // Label for Name of our Organization
    titleLabel.setText("U F A E S", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::right);

    // Label for Name of Plugin
    auto nameFont = juce::Font(tface);
    nameFont.setBold(true);
    nameFont.setHeight(45);
    NameLabel.setFont(nameFont);
    
    NameLabel.setText("distortion multieffect", juce::dontSendNotification);
    NameLabel.setJustificationType(juce::Justification::left);
    //shadow for visualizer
    //if you change visualizer size, change this since its hardcoded
    auto visualizerRect = juce::Rectangle<int>(getWidth()-getWidth()/2, 100, getWidth() / 3, 150);
    auto shadow = juce::DropShadow();
    shadow.drawForRectangle(g,visualizerRect);
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
    clipSliderNeg.setBounds(((getWidth() / 5) * 1) - (100 / 2),
        (getHeight() / 1.4) - (100 / 2), 100, 100);
    highPassSlider.setBounds(((getWidth() / 5) * 4) - (100 / 2),
        (getHeight() / 2) - (100 / 2), 100, 100);
    lowPassSlider.setBounds(((getWidth() / 5) * 4) - (100 / 2),
        (getHeight() / 1.4) - (100 / 2), 100, 100);
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
    float clipValueNeg = static_cast<float>(((clipSliderNeg.getValue() + 40.0) / 20.0) * 0.2 + 0.5);
    float highPassValue = static_cast<float>(((highPassSlider.getValue()))); //lisp moment
    float lowPassValue = static_cast<float>(((lowPassSlider.getValue() )));
    // Limit Brightness between specific range
    //float driveBrightness = juce::jlimit(0.5f, 0.7f, driveValue); 
    //float clipBrightness = juce::jlimit(0.5f, 0.7f, clipValue);
    //float inGainBrightness = juce::jlimit(0.5f, 0.7f, inGainValue);
    //float outGainBrightness = juce::jlimit(0.5f, 0.7f, outGainValue);
    
    /**
     lambda function that returns a color for the give slider value
     */
    
    auto getFillColor = [](auto _sliderValue) { return
        // Colour(float Hue, float Saturation, float Brightness, float Alpha)
        juce::Colour(0.633333f, 1.0f, _sliderValue, 1.0f);
    
    };
    
    
    driveSlider.setColour(juce::Slider::rotarySliderFillColourId, 
        getFillColor(driveValue));
    clipSlider.setColour(juce::Slider::rotarySliderFillColourId, 
        getFillColor(clipValue));
    inGainSlider.setColour(juce::Slider::rotarySliderFillColourId,
        getFillColor(inGainValue));
    outGainSlider.setColour(juce::Slider::rotarySliderFillColourId,
        getFillColor(outGainValue));
    clipSliderNeg.setColour(juce::Slider::rotarySliderFillColourId,
        getFillColor(clipValueNeg));
    highPassSlider.setColour(juce::Slider::rotarySliderFillColourId,
        getFillColor(highPassValue));
    lowPassSlider.setColour(juce::Slider::rotarySliderFillColourId,
        getFillColor(lowPassValue));
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
    auto shadow = juce::DropShadow();
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
    shadow.drawForPath(g,backgroundArc);
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
        shadow.drawForPath(g,valueArc);
        //COLOR OF THE ORANGE CIRCLE!!!!
        g.setColour(juce::Colour(250,70,22));

        // Set the bounds of the ellipse to be just inside the arc line of the slider
        // This is the bounds of the slider reduced by the linewidth (see the beginning of this function)
        auto ellipseBounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10+lineW);

        // Create a filled ellipse with the new bounds
        
        // fillEllipse(float x, float y, float width, float height)
        g.fillEllipse(ellipseBounds.getX(), ellipseBounds.getY(), ellipseBounds.getWidth(), ellipseBounds.getHeight());
       
        //The stick thing
        juce::Path p;
           auto pointerLength = radius * 0.68f;
           auto pointerThickness = 4.5f;
        //raduis if you want to change where the stick rotates from
        // add nothing and it will extend to the outline
        p.addRectangle (-pointerThickness * 0.5f, -radius+6.8, pointerThickness, pointerLength);
           p.applyTransform (juce::AffineTransform::rotation (toAngle).translated (bounds.getCentreX(), bounds.getCentreY()));
        g.setColour (juce::Colour(6, 7, 41));
                g.fillPath (p);
        
        shadow.drawForPath(g,p);
    }

    // This is the thumb of the slider, the circle at the end, or indicator point
    auto thumbWidth = lineW * 0.5f;
    juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

    // Sets the color of the slider thumb
    g.setColour(juce::Colours::darkorange);
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

        //const int result = m.show();
        /*
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
        }*/
    }
    else
    {       
        Slider::mouseDown(e);
    }
   
}
