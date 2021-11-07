/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverberationAudioProcessorEditor::ReverberationAudioProcessorEditor (ReverberationAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    Image  knobImage;
    knobImage = GIFImageFormat::loadFrom(BinaryData::Knob_png, BinaryData::Knob_pngSize);

    TR60Slider.reset(new FilmStripKnob(knobImage, 45, false));
    addAndMakeVisible(TR60Slider.get());

    dryWetSlider.reset(new FilmStripKnob(knobImage, 45, false));
    addAndMakeVisible(dryWetSlider.get());

    addAndMakeVisible(RT60Label);
    addAndMakeVisible(dryWetLabel);
    addAndMakeVisible(RT60LabelTitle);
    addAndMakeVisible(dryWetLabelTitle);


    TR60Slider->setRange(0, 2, 0.01);
    TR60Slider->setSliderStyle(Slider::SliderStyle::Rotary);
    TR60Slider->setColour(Slider::ColourIds::rotarySliderFillColourId, Colour(Colours::blue));
    TR60Slider->setColour(Slider::ColourIds::thumbColourId, Colour(Colours::darkorange));
    TR60Slider->setValue(1);

    TR60Slider->onValueChange = [this]
    {
        float fb = TR60Slider->getValue();
        audioProcessor.LineDelayOneL.newTR60(fb);
        audioProcessor.LineDelayOneR.newTR60(fb);
        audioProcessor.LineDelayTwoL.newTR60(fb);
        audioProcessor.LineDelayTwoR.newTR60(fb);
        audioProcessor.LineDelayThreeL.newTR60(fb);
        audioProcessor.LineDelayThreeR.newTR60(fb);
        audioProcessor.LineDelayFourL.newTR60(fb);
        audioProcessor.LineDelayFourR.newTR60(fb);
        audioProcessor.LineDelayFiveL.newTR60(fb);
        audioProcessor.LineDelayFiveR.newTR60(fb);
        RT60Label.setText(String(TR60Slider->getValue(), 2), dontSendNotification);
    };


    RT60LabelTitle.setText("RT60", dontSendNotification);
    RT60LabelTitle.setColour(Label::textColourId, Colours::red);
    RT60LabelTitle.setJustificationType(Justification::centred);

    dryWetSlider->setRange(0, 1, 0.01);
    dryWetSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    dryWetSlider->setColour(Slider::ColourIds::rotarySliderFillColourId, Colour(Colours::blue));
    dryWetSlider->setColour(Slider::ColourIds::thumbColourId, Colour(Colours::darkorange));
    dryWetSlider->setValue(0.5);

    dryWetSlider->onValueChange = [this]
    {
        float DW = dryWetSlider->getValue();
        audioProcessor.Wet = DW;
        dryWetLabel.setText(String(dryWetSlider->getValue(), 2), dontSendNotification);
    };

    dryWetLabelTitle.setText("Dry & Wet", dontSendNotification);
    dryWetLabelTitle.setColour(Label::textColourId, Colours::darkorange);
    dryWetLabelTitle.setJustificationType(Justification::centred);

    TR60Slider->setBounds(25, 100, 66, 66);
    RT60Label.setBounds(40, 136, 66, 66);
    RT60LabelTitle.setBounds(25, 55, 66, 66);
    dryWetSlider->setBounds(111, 100, 66, 66);
    dryWetLabel.setBounds(127, 136, 66, 66);
    dryWetLabelTitle.setBounds(113, 55, 66, 66);

    setSize(200, 200);
}

ReverberationAudioProcessorEditor::~ReverberationAudioProcessorEditor()
{
    TR60Slider = nullptr;
    dryWetSlider = nullptr;
}

//==============================================================================
void ReverberationAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);


    {
        int x = 8, y = 8, width = 184, height = 184;
        Colour fillColour = Colour(Colours::black);
        Colour strokeColour = Colour(Colours::blue);
        g.setColour(fillColour);
        g.fillRect(x, y, width, height);
        g.setColour(strokeColour);
        g.drawRect(x, y, width, height, 3);
    }

    {
        int x = 22, y = 19, width = 155, height = 40;
        String text(TRANS("Reverb"));
        Colour fillColour = Colours::greenyellow;
        g.setColour(fillColour);
        g.setFont(Font(Font::getDefaultSansSerifFontName(), 43.50f, Font::plain).withTypefaceStyle("Regular"));
        g.drawText(text, x, y, width, height,
            Justification::centred, true);
    }
}

void ReverberationAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
