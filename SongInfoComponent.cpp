/*
  ==============================================================================

    SongInfoComponent.cpp
    Created: 4 Mar 2021 11:14:54am
    Author:  Colin

  ==============================================================================
*/

#include "SongInfoComponent.h"

SongInfoComponent::SongInfoComponent(DJAudioPlayer* player) :
    player(player)
{

}

SongInfoComponent::~SongInfoComponent()
{

}

void SongInfoComponent::paint(juce::Graphics& g)
{
    juce::Font myFont{16.0};
    g.setFont(myFont);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    juce::String toDraw = std::to_string(player->getPositionRelative() * songLength) + " \\ " + std::to_string(songLength);
    g.drawText(toDraw, getLocalBounds(), juce::Justification::centredBottom);

    toDraw = player->getFileName();
    int stringWidth = myFont.getStringWidth(toDraw);
    int stringHeight = myFont.getHeight();
    if (stringWidth > getWidth())
    {
        double scrollSpeed = .2;
        textX -= scrollSpeed;

        if (textX < -stringWidth)
            textX = getWidth();
    }
    else textX = getWidth() / 10;
    g.drawText(toDraw, textX, getLocalBounds().getCentreY(), stringWidth, stringHeight, juce::Justification::centred);

    toDraw = "Current BPM: " + std::to_string(player->getBPM());
    stringWidth = myFont.getStringWidth(toDraw);
    g.drawText(toDraw, getWidth() * .1, getHeight() * .2, stringWidth, stringHeight, juce::Justification::left);
    
    toDraw = "Key: " + std::to_string(player->getKey());
    stringWidth = myFont.getStringWidth(toDraw);
    g.drawText(toDraw, getWidth() * .8, getHeight() * .2, stringWidth, stringHeight, juce::Justification::left);
    repaint();
}

void SongInfoComponent::setSongLength(double totalLengthInSeconds)
{
    songLength = totalLengthInSeconds;
    repaint();
}