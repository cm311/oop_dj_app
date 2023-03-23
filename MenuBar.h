/*
  ==============================================================================

    MenuBar.h
    Created: 15 Feb 2021 6:16:46am
    Author:  Colin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "playlistComponent.h"


class MenuBar : public juce::Component,
    public juce::Button::Listener
{
public:
    MenuBar(PlaylistComponent* _pList_display);
    ~MenuBar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /**Depending on the button clicked interactions with the playlistComponent
    addFolderButton clicked - Opens a File browser dialog to add a folder to the playlist.  Only loads mp3 files
    analyzeButton clicked - Will analyze the playlist and get BPM and other stuff.  Not implemented atm.
    clearButton clicked - Clears the current playlist
    saveButton clicked - Opens a File Save dialog to save the current playlist as an .m3u file.
    loadButton clicked - Opens a file browser dialog to load a playlist file (.m3u)
    singleSongButton clicked - Opens a file browser to add a single song to the playlist.  Only accepts mp3s.
    */
    void buttonClicked(juce::Button* button) override;

private:
    PlaylistComponent* pList_display;
    juce::FileSearchPath f;
    juce::TextButton addFolderButton{"Add Folder"};
    juce::TextButton analyzeButton{"Analyze Playlist"};
    juce::TextButton clearButton{"Clear Playlist"};
    juce::TextButton saveButton{"Save Playlist"};
    juce::TextButton loadButton{"Load Playlist"};
    juce::TextButton singleSongButton{ "Load Song" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuBar)
};
