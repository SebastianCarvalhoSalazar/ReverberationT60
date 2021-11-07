/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverberationAudioProcessor::ReverberationAudioProcessor():
    Dry(0.5), Wet(0.5)
#ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ReverberationAudioProcessor::~ReverberationAudioProcessor()
{
}

//==============================================================================
const juce::String ReverberationAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReverberationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReverberationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReverberationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReverberationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReverberationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReverberationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReverberationAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ReverberationAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReverberationAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ReverberationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    LineDelayOneL.updateSampleRate(sampleRate);
    LineDelayOneL.resetBuffer();
    LineDelayOneL.updateTimedelay(4000 / sampleRate);
    LineDelayOneL.newD(4000);

    LineDelayOneR.updateSampleRate(sampleRate);
    LineDelayOneR.resetBuffer();
    LineDelayOneR.updateTimedelay(4000 / sampleRate);
    LineDelayOneR.newD(4000);

    LineDelayTwoL.updateSampleRate(sampleRate);
    LineDelayTwoL.resetBuffer(); 
    LineDelayTwoL.updateTimedelay(3000 / sampleRate);
    LineDelayTwoL.newD(3000);

    LineDelayTwoR.updateSampleRate(sampleRate);
    LineDelayTwoR.resetBuffer();
    LineDelayTwoR.updateTimedelay(3000 / sampleRate);
    LineDelayTwoR.newD(3000);

    LineDelayThreeL.updateSampleRate(sampleRate);
    LineDelayThreeL.resetBuffer();
    LineDelayThreeL.updateTimedelay(2000 / sampleRate);
    LineDelayThreeL.newD(2000);

    LineDelayThreeR.updateSampleRate(sampleRate);
    LineDelayThreeR.resetBuffer();
    LineDelayThreeR.updateTimedelay(2000 / sampleRate);
    LineDelayThreeR.newD(2000);

    LineDelayFourL.updateSampleRate(sampleRate);
    LineDelayFourL.resetBuffer();
    LineDelayFourL.updateTimedelay(1000 / sampleRate);
    LineDelayFourL.newD(1000);

    LineDelayFourR.updateSampleRate(sampleRate);
    LineDelayFourR.resetBuffer();
    LineDelayFourR.updateTimedelay(1000 / sampleRate);
    LineDelayFourR.newD(1000);

    LineDelayFiveL.updateSampleRate(sampleRate);
    LineDelayFiveL.resetBuffer();
    LineDelayFiveL.updateTimedelay(6000 / sampleRate);
    LineDelayFiveL.newD(6000);

    LineDelayFiveR.updateSampleRate(sampleRate);
    LineDelayFiveR.resetBuffer();
    LineDelayFiveR.updateTimedelay(6000 / sampleRate);
    LineDelayFiveR.newD(6000);

    LineDelaySixL.updateSampleRate(sampleRate);
    LineDelaySixL.resetBuffer();
    LineDelaySixL.updateTimedelay(5000 / sampleRate);
    LineDelaySixL.newD(5000);

    LineDelaySixR.updateSampleRate(sampleRate);
    LineDelaySixR.resetBuffer();
    LineDelaySixR.updateTimedelay(5000 / sampleRate);
    LineDelaySixR.newD(5000);

    LineDelaySevenL.updateSampleRate(sampleRate);
    LineDelaySevenL.resetBuffer();
    LineDelaySevenL.updateTimedelay(1500 / sampleRate);
    LineDelaySevenL.newD(1500);

    LineDelaySevenR.updateSampleRate(sampleRate);
    LineDelaySevenR.resetBuffer();
    LineDelaySevenR.updateTimedelay(1500 / sampleRate);
    LineDelaySevenR.newD(1500);

    LineDelayEightL.updateSampleRate(sampleRate);
    LineDelayEightL.resetBuffer();
    LineDelayEightL.updateTimedelay(2500 / sampleRate);
    LineDelayEightL.newD(2500);

    LineDelayEightR.updateSampleRate(sampleRate);
    LineDelayEightR.resetBuffer();
    LineDelayEightR.updateTimedelay(2500 / sampleRate);
    LineDelayEightR.newD(2500);  

}

void ReverberationAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReverberationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ReverberationAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    Dry = 1 - Wet;

    for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        for (auto channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelN = buffer.getWritePointer(channel);

            if (channel == 0)
            {
                channelN[sample] = (Dry * channelN[sample]) + (Wet * (LineDelayOneL.getNextDelay(channelN[sample])
                                                               + LineDelayTwoL.getNextDelay(-channelN[sample])
                                                               + LineDelayThreeL.getNextDelay(channelN[sample])
                                                               + LineDelayFourL.getNextDelay(-channelN[sample])
                                                               + LineDelayFiveL.getNextDelay(channelN[sample])
                                                               + LineDelaySixL.getNextDelay(-channelN[sample])
                                                               + LineDelaySevenL.getNextDelay(channelN[sample])
                                                               + LineDelayEightL.getNextDelay(-channelN[sample])))/4;
            }
            else if (channel == 1)
            {
                channelN[sample] = (Dry * channelN[sample]) + (Wet * (LineDelayOneR.getNextDelay(channelN[sample])
                                                               + LineDelayTwoR.getNextDelay(-channelN[sample])
                                                               + LineDelayThreeR.getNextDelay(channelN[sample])
                                                               + LineDelayFourR.getNextDelay(-channelN[sample])
                                                               + LineDelayFiveR.getNextDelay(channelN[sample])
                                                               + LineDelaySixR.getNextDelay(-channelN[sample])
                                                               + LineDelaySevenR.getNextDelay(channelN[sample])
                                                               + LineDelayEightR.getNextDelay(-channelN[sample])))/4;
            }
            else
            {
                buffer.clear(channel, 0, buffer.getNumSamples());
            }
        }

    }
}


//==============================================================================
bool ReverberationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ReverberationAudioProcessor::createEditor()
{
    return new ReverberationAudioProcessorEditor (*this);
}

//==============================================================================
void ReverberationAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReverberationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverberationAudioProcessor();
}
