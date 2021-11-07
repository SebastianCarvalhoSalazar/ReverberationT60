/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "filmStrip.h"

//==============================================================================
/**
*/
class ReverberationAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ReverberationAudioProcessorEditor (ReverberationAudioProcessor&);
    ~ReverberationAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<FilmStripKnob> TR60Slider, timeSlider, dryWetSlider, FrequencySlider;
    Label RT60Label, dryWetLabel, RT60LabelTitle, dryWetLabelTitle;

    ReverberationAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverberationAudioProcessorEditor)
};
