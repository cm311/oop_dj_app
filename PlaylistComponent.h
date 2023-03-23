/*
  ==============================================================================

    PlaylistComponent.h
    Created: 13 Feb 2021 8:34:34am
    Author:  Colin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeckGUI.h"
#include <vector>
#include <string>
#include "Track.h"
#include "EditTrackInfoModal.h"


class PlaylistComponent  : public juce::Component,
    public juce::TableListBoxModel,
    public juce::FileDragAndDropTarget,
    public juce::Button::Listener
{
public:
    PlaylistComponent(std::vector<Track> files, DeckGUI *d1, DeckGUI *d2);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //TableListBoxModel pure virtuals
    int getNumRows() override;
    void paintRowBackground(juce::Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    void paintCell(juce::Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    //Allows us to add a juce::component to the table
    juce::Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component *existingComponentToUpdate) override;

    //Button listened virtual
    void buttonClicked(juce::Button* button) override;

    /**When the Cell is double clicked, the song that is in that cell is added to a DeckGUI.
    If left mouse was double clicked, its added to the left DeckGUI.
    If right mouse was double clicked, its added to the right DeckGUI*/
    void cellDoubleClicked(int rowNumber, int columnId, const juce::MouseEvent&) override;

    /**If the delete key is pressed, the track that is currently highlighted in the table is removed from the playlist*/
    void deleteKeyPressed(int currentSelectedRow) override;

    /**Opens an EditTrackInfoModal to edit the info of the selected cell*/
    void returnKeyPressed(int currentSelectedRow) override;

    bool isInterestedInFileDrag(const juce::StringArray& files);
    void filesDropped(const juce::StringArray& files, int x, int y);

    /**Returns a vector of all the Files that are currently in the playlist.  Used by MenuBar*/
    std::vector<Track> getPlaylistFiles();

    /**Adds the tracks that are in "files" to the playlist*/
    void addPlaylistFiles(std::vector<juce::String> t);

    /**Set the playlistFiles to newTracks*/
    void setPlaylistFiles(std::vector<Track> newTracks);

    /**Add a single track to playlist files*/
    void addTrackToPlaylistFiles(juce::String fileName, float length, float beats, int key, int isMajor, int id1, int id2, bool displayed);

    /**Adds the track that "file" holds to the playlist*/
    void addSingleSong(juce::File file);

    /**Playlist is cleared completely*/
    void clearPlaylist();

    /**Searches the current playlist for the string that is passed*/
    void searchTracks(juce::String s);

    /**TODO, will analyze a song and get its BPM etc.  not implemented currently*/
    void analyzeSong();


private:
    juce::TableListBox tableComponent;
    std::vector<Track> playlistFiles;
    std::vector<Track> displayedFiles;
    std::vector<Track> allPlaylistFiles;
    bool searching = false;
    DeckGUI* d1;
    DeckGUI* d2;
    juce::TextEditor searchBar{ "Search Here" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};



