/*
  ==============================================================================

    VisualsDeck.cpp
    Created: 15 Feb 2021 6:17:50am
    Author:  Colin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VisualsDeck.h"

#define PI 3.14159265
//==============================================================================

VisualsDeck::~VisualsDeck()
{
}

void VisualsDeck::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::black);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.fillAll();
    g.setColour(juce::Colours::darkorange.darker());

    std::vector<float> intensities = averageSongVisual();
    
    if (circleX == -1)
    {
        circleX = getWidth() * .37;
        circleY = getHeight() * .4;
    }
    if (abs(intensities[0]) > .01)
    {
        circleWidth += 3 * increaseFactor;
    }

    g.fillEllipse(circleX, circleY, circleWidth, circleWidth);
    if (circleWidth < 8) increaseFactor = 2;
    if (circleWidth >= 8 && circleWidth < 16) increaseFactor = 1.5;
    if (circleWidth >= 16 && circleWidth < 25) increaseFactor = 1.2;
    if (circleWidth >= 25 && circleWidth < 45) increaseFactor = .9;
    if (circleWidth >= 45 && circleWidth < 90) increaseFactor = .7;
    if (circleWidth >= 90 && circleWidth < 120) increaseFactor = .3;
    if (circleWidth > 120) increaseFactor = .1;

    if(circleWidth > 4) circleWidth -= 2;
    if (circleWidth > 60) circleWidth -= 3;
    if (circleWidth > 90) circleWidth -= 4;











    g.setColour(juce::Colours::darkorange);
    float sum = abs(intensities[0]) + abs(intensities[1]);

    if (sumcircleX == -1)
    {
        sumcircleX = getWidth() * .44;
        sumcircleY = getHeight() * .4;
    }
    if (sum > .016)
    {
        sumCircleWidth += 3 * sumIncreaseFactor;
    }

    g.fillEllipse(sumcircleX, sumcircleY, sumCircleWidth, sumCircleWidth);

    if (sumCircleWidth < 8) sumIncreaseFactor = 2;
    if (sumCircleWidth >= 8 && sumCircleWidth < 16) sumIncreaseFactor = 1.5;
    if (sumCircleWidth >= 16 && sumCircleWidth < 25) sumIncreaseFactor = 1.2;
    if (sumCircleWidth >= 25 && sumCircleWidth < 45) sumIncreaseFactor = .9;
    if (sumCircleWidth >= 45 && sumCircleWidth < 90) sumIncreaseFactor = .7;
    if (sumCircleWidth >= 90 && sumCircleWidth < 120) sumIncreaseFactor = .3;
    if (sumCircleWidth > 120) sumCircleWidth = .1;

    if (sumCircleWidth > 4) sumCircleWidth -= 2;
    if (sumCircleWidth > 60) sumCircleWidth -= 3;
    if (sumCircleWidth > 90) sumCircleWidth -= 4;













    g.setColour(juce::Colours::orange);
    if (othercircleX == -1)
    {
        othercircleX = getWidth() * .51;
        othercircleY = getHeight() * .4;
    }
    if (std::abs(intensities[1]) > .01)
    {
        otherCircleWidth += 3 * otherIncreaseFactor;
    }

    g.fillEllipse(othercircleX, othercircleY, otherCircleWidth, otherCircleWidth);

    if (otherCircleWidth < 8) otherIncreaseFactor = 2;
    if (otherCircleWidth >= 8 && otherCircleWidth < 16) otherIncreaseFactor = 1.5;
    if (otherCircleWidth >= 16 && otherCircleWidth < 25) otherIncreaseFactor = 1.2;
    if (otherCircleWidth >= 25 && otherCircleWidth < 45) otherIncreaseFactor = .9;
    if (otherCircleWidth >= 45 && otherCircleWidth < 90) otherIncreaseFactor = .7;
    if (otherCircleWidth >= 90 && otherCircleWidth < 120) otherIncreaseFactor = .3;
    if (otherCircleWidth > 120) otherCircleWidth = .1;

    if (otherCircleWidth > 4) otherCircleWidth -= 2;
    if (otherCircleWidth > 60) otherCircleWidth -= 3;
    if (otherCircleWidth > 90) otherCircleWidth -= 4;












    if (circleX < 0 && xDir == -1)
        xDir = 1;
    if (circleY < 0 && yDir == -1)
        yDir = 1;
    if (othercircleX < 0 && otherXDir == -1)
        otherXDir = 1;
    if (othercircleY < 0 && otherYDir == -1)
        otherYDir = 1;
    if (sumcircleX < 0 && sumXDir == -1)
        sumXDir = 1;
    if (sumcircleY < 0 && sumYDir == -1)
        sumYDir = 1;


    //drawHarmonicsWheel(g);

    g.drawText(std::to_string(intensities[0]), getLocalBounds(), juce::Justification::bottomLeft);
    g.drawText(std::to_string(intensities[1]), getLocalBounds(), juce::Justification::bottomRight);
}

void VisualsDeck::resized()
{

}

std::vector<float> VisualsDeck::averageSongVisual()
{
    std::vector<float> minMax;
    float sumMin = 0;
    float sumMax = 0;

    for (int i = 0; i < 20; i++)
    {
        sumMin = songVisual[0][i];
        sumMax = songVisual[1][i];
    }

    minMax.push_back(sumMin / songVisual[0].size());
    minMax.push_back(sumMax / songVisual[1].size());

    return minMax;
}

void VisualsDeck::addRangeToSongVisual(juce::Range<float> ranges)
{
    bufferRanges = ranges;

    songVisual[0].push_back(ranges.getStart());
    songVisual[0].erase(songVisual[0].begin());

    songVisual[1].push_back(ranges.getEnd());
    songVisual[1].erase(songVisual[1].begin());
}

void VisualsDeck::drawHarmonicsWheel(juce::Graphics& g)
{
    //Now I'm going to draw the Harmonix wheel...
    harmonixCircle c{ getWidth() / 2 - (getWidth() * .4),
        getHeight() / 10,
        getWidth() * .4 };

    //outer circle
    g.drawEllipse(c.centerX, c.centerY, 2 * c.radius, 2 * c.radius, 2);

    //inner circle
    g.drawEllipse(c.centerX + c.radius / 2.8, c.centerY + c.radius / 2.8, c.radius * 1.3, c.radius * 1.3, 2);

    g.drawLine(c.centerX + c.radius + c.radius * cos(30 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(30 * PI / 180.0),
        c.centerX + c.radius + c.radius * cos(210 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(210 * PI / 180.0),
        1);

    g.drawLine(c.centerX + c.radius + c.radius * cos(60 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(60 * PI / 180.0),
        c.centerX + c.radius + c.radius * cos(240 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(240 * PI / 180.0),
        1);

    //vertical line
    g.drawLine(c.centerX + c.radius + c.radius * cos(90 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(90 * PI / 180.0),
        c.centerX + c.radius + c.radius * cos(270 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(270 * PI / 180.0),
        1);

    g.drawLine(c.centerX + c.radius + c.radius * cos(120 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(120 * PI / 180.0),
        c.centerX + c.radius + c.radius * cos(300 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(300 * PI / 180.0),
        1);

    g.drawLine(c.centerX + c.radius + c.radius * cos(150 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(150 * PI / 180.0),
        c.centerX + c.radius + c.radius * cos(330 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(330 * PI / 180.0),
        1);

    g.drawLine(c.centerX + c.radius + c.radius * cos(180 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(180 * PI / 180.0),
        c.centerX + c.radius + c.radius * cos(360 * PI / 180.0),
        c.centerY + c.radius + c.radius * sin(360 * PI / 180.0),
        1);
}
