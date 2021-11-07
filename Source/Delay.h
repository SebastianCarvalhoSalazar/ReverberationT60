/*
  ==============================================================================

    Delay.h
    Created: 23 Oct 2020 2:14:13pm
    Author:  SEBASTIAN

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;

class Delay
{
public:
	Delay()
		: sampleRate(44100), maxTime(2), rdIdx(0), wrIdx(0), timeDelay(0), numSamples(0), feedBack(0), D(0), TR60(1)

	{
		TmpBuffer.resize(maxTime * sampleRate);
		memset(TmpBuffer.getRawDataPointer(), 0, sizeof(float) * sampleRate * maxTime);
		numSamples = timeDelay * sampleRate;

		rdIdx = wrIdx - numSamples;
		if (rdIdx < 0) { rdIdx = rdIdx + TmpBuffer.size(); }
	}

	void updateTimedelay(float newTimeDelay)
	{
		timeDelay = newTimeDelay;
		numSamples = timeDelay * sampleRate;
	}

	void updateSampleRate(float newSampleRate)
	{
		sampleRate = newSampleRate;
		numSamples = timeDelay * sampleRate;
		TmpBuffer.resize(maxTime * sampleRate);
		memset(TmpBuffer.getRawDataPointer(), 0, sizeof(float) * sampleRate * maxTime);
	}

	void updateMaxTime(float newMaxTime)
	{
		maxTime = newMaxTime;
	}

	void resetBuffer()
	{
		TmpBuffer.resize(maxTime * sampleRate);
		memset(TmpBuffer.getRawDataPointer(), 0, sizeof(float) * sampleRate * maxTime);
	}

	void newTR60(float newTR60)
	{
		TR60 = newTR60;
	}

	void newD(float newD)
	{
		D = newD;
	}

	float getNextDelay(float xn)
	{

		feedBack = pow(10,(-3*D)/(TR60*sampleRate));

		float yn = TmpBuffer[rdIdx];

		TmpBuffer.set(wrIdx, xn + yn * feedBack);
		if (++wrIdx >= TmpBuffer.size()) { wrIdx = 0; }

		rdIdx = wrIdx - numSamples;
		if (rdIdx < 0) { rdIdx = rdIdx + TmpBuffer.size(); }

		return yn;
	}

	~Delay() {}

	
private:
	float sampleRate, maxTime, rdIdx, wrIdx, D;
	std::atomic<float> timeDelay, feedBack, numSamples, TR60;
	Array<float> TmpBuffer;

};