/*
  ==============================================================================

    EditTrackInfoModal.h
    Created: 8 Mar 2021 3:41:50pm
    Author:  Colin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "Track.h"


class EditTrackInfoModal : public juce::Component,
    juce::Button::Listener
{
public:
    EditTrackInfoModal(std::vector<Track> &playlistFiles, int currentSelectedRow);
    void buttonClicked(juce::Button* button) override;
    void resized() override;

    /**returns the playlist files including the track that was edited in this window*/
    std::vector<Track> getPlaylistFiles();

private:
    juce::TextButton saveButton{ "Save Changes" };
    juce::Label column2Label;
    juce::Label column3Label;
    juce::Label column4Label;
    juce::TextEditor column2TextEdit;
    juce::TextEditor column3TextEdit;
    juce::TextEditor column4TextEdit;

    std::vector<Track> playlistTracks;
    int songToChange;
};