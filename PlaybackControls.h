/*
  ==============================================================================

    PlaybackControls.h
    Created: 4 Mar 2021 4:24:01am
    Author:  Colin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class PlaybackControls : public juce::Component
{
public:
    PlaybackControls(DJAudioPlayer* player);
    ~PlaybackControls();
    void paint(juce::Graphics& g) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseMove(const juce::MouseEvent& event) override;

private:
    DJAudioPlayer* player;
    bool playing = false;

    //A variable to eat up the extra mouse count that happens in the mouseDown event
    int mouseCount = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackControls)
};
