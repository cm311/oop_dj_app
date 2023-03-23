/*
  ==============================================================================

    VisualsDeck.h
    Created: 15 Feb 2021 6:17:50am
    Author:  Colin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include "Track.h"


//==============================================================================
/*
*/
class VisualsDeck  : public juce::AudioVisualiserComponent
{
public:
    VisualsDeck() : juce::AudioVisualiserComponent(2)
    {
        songVisual.resize(2);
        songVisual[0].resize(20);
        songVisual[1].resize(20);
    }
    ~VisualsDeck() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /**Finds the average value of the song visual array*/
    std::vector<float> averageSongVisual();

    /**Called from DJAudioPlayer to add values to the songVisual Array*/
    void addRangeToSongVisual(juce::Range<float> ranges);

    /**Song visual is an array of floats that represent the sum of the MAX and MIN values in a given sample.
    It is used to generate some measure of intensity so that visuals can be drawn*/
    std::vector<std::vector<float>> songVisual;

    /**Not used, might use later to draw the harmonics wheel*/
    void drawHarmonicsWheel(juce::Graphics& g);

private:

    /**TODO, make a circle class instead of having all these variables.*/
    float circleX = -1;
    float circleY = -1;
    float circleWidth = 2;
    float increaseFactor = 0;
    float xDir = 1;
    float yDir = 1;

    float othercircleX = -1;
    float othercircleY = -1;
    float otherCircleWidth = 2;
    float otherIncreaseFactor = 0;
    float otherXDir = 1;
    float otherYDir = 1;

    float sumcircleX = -1;
    float sumcircleY = -1;
    float sumCircleWidth = 2;
    float sumIncreaseFactor = 0;
    float sumXDir = 1;
    float sumYDir = 1;

    juce::Range<float> bufferRanges;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualsDeck)
};

/**Not used*/
struct harmonixCircle
{
    float centerX = 0;
    float centerY = 0;
    float radius = 0;
};
