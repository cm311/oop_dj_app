/*
  ==============================================================================

    SongInfoComponent.h
    Created: 4 Mar 2021 11:14:54am
    Author:  Colin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/**A class that is used to display the track file name.  Will eventually hold more information like the BPM (once that is working), and
   the length of the song.*/
class SongInfoComponent : public juce::Component
{
public:
    SongInfoComponent(DJAudioPlayer* player);
    ~SongInfoComponent();

    void paint(juce::Graphics&) override;

    /**Allows the length of the currently loaded track in the deckGUI to display in the songinfocomponent*/
    void setSongLength(double totalLengthInSeconds);

private:
    double songLength = 0;
    double textX = 0;
    DJAudioPlayer* player;
    juce::String songName;
    juce::DrawableText drawBox;
};