/*
  ==============================================================================

    MenuBar.cpp
    Created: 15 Feb 2021 6:16:46am
    Author:  Colin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MenuBar.h"

MenuBar::MenuBar(PlaylistComponent* _pList_display) :
    pList_display(_pList_display)
{
    addAndMakeVisible(addFolderButton);
    addAndMakeVisible(clearButton);
    addAndMakeVisible(analyzeButton);
    addAndMakeVisible(singleSongButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(loadButton);

    //Add button listeners
    addFolderButton.addListener(this);
    clearButton.addListener(this);
    analyzeButton.addListener(this);
    singleSongButton.addListener(this);
    saveButton.addListener(this);
    loadButton.addListener(this);

    DBG("Constructing menu bar");
}

MenuBar::~MenuBar()
{
}

void MenuBar::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colours::black);   // clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.drawText ("MenuBar", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void MenuBar::resized()
{
    addFolderButton.setBounds(0, 0, getWidth() / 6, getHeight());
    clearButton.setBounds(1 * getWidth() / 6, 0, getWidth() / 6, getHeight());
    saveButton.setBounds(2 * getWidth() / 6, 0, getWidth() / 6, getHeight());
    loadButton.setBounds(3 * getWidth() / 6, 0, getWidth() / 6, getHeight());
    analyzeButton.setBounds(4 * getWidth() / 6, 0, getWidth() / 6, getHeight());
    singleSongButton.setBounds(5 * getWidth() / 6, 0, getWidth() / 6, getHeight());
}

void MenuBar::buttonClicked(juce::Button* button)
{
    if (button == &addFolderButton)
    {
        juce::FileChooser chooser{ "Select Folder...", juce::File(), juce::String(), false };
        if (chooser.browseForDirectory())
        {
            juce::Array<juce::File> juceFiles = chooser.getResult().findChildFiles(juce::File::TypesOfFileToFind::findFiles, false);
            std::vector<juce::String> files;
            for (juce::File f : juceFiles)
            {
                files.push_back(
                    f.getFullPathName() + "," + 
                    f.getParentDirectory().getFileName() + "\\" + f.getFileName() + "," +
                    std::to_string(-1) + "," +
                    std::to_string(-1) + "," +
                    std::to_string(13) + "," +
                    std::to_string(1) + ",");
            }
            pList_display->addPlaylistFiles(files);
        }
    }
    if (button == &clearButton)
    {
        pList_display->clearPlaylist();
    }
    if (button == &analyzeButton)
    {
        DBG("Button working, analyze the playlist");
        pList_display->analyzeSong();
    }
    if (button == &singleSongButton)
    {
        juce::FileChooser chooser{ "Select File...", juce::File(), "*.mp3", false };
        if (chooser.browseForFileToOpen())
        {
            juce::File f(chooser.getResult().getFullPathName());
            pList_display->addSingleSong(f);
        }
    }
    if (button == &loadButton)
    {
        juce::FileChooser chooser{ "SelectFile", juce::File(), "*.dat", false };
        if (chooser.browseForFileToOpen())
        {
            juce::File f(chooser.getResult().getFullPathName());
            juce::StringArray songs = juce::StringArray();
            f.readLines(songs);
            std::vector<juce::String> s;

            for (int i = 0; i < songs.size(); i++)
            {
                s.push_back(songs[i]);
            }
            pList_display->addPlaylistFiles(s);
        }
    }
    if (button == &saveButton)
    {
        juce::FileChooser chooser{ "Choose Save Location", juce::File(), "*.dat", false };
        chooser.browseForFileToSave(true);
        chooser.getResult().getFullPathName();

        juce::File f(chooser.getResult().getFullPathName());
        f.deleteFile();
        f.create();


        //Need fully qualified path names to save, get rid of track titles, save as dat
        auto tracks = pList_display->getPlaylistFiles();
        for (int i = 0; i < tracks.size(); i++)
        {
            f.appendText(tracks[i].file.getFullPathName() + "," +
                tracks[i].name + "," +
                std::to_string(tracks[i].trackLength) + "," +
                std::to_string(tracks[i].beatsPerMin) + "," +
                std::to_string(tracks[i].nativeKey) + "," +
                std::to_string(tracks[i].isMajor) + ",");
            f.appendText("\n");
        }
    }
}
