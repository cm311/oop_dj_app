/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 13 Feb 2021 8:34:34am
    Author:  Colin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent(std::vector<Track> files, DeckGUI *_d1, DeckGUI *_d2):
    d1(_d1),
    d2(_d2),
    playlistFiles(files)
{
    DBG("Constructing playlist component");   
    tableComponent.getHeader().addColumn("Track Title", 1, 540);
    tableComponent.getHeader().addColumn("Length", 2, 100);
    tableComponent.getHeader().addColumn("BPM", 3, 80);
    tableComponent.getHeader().addColumn("Native Key", 4, 80);
    tableComponent.setModel(this);

    juce::String playlistSave{ juce::File::getCurrentWorkingDirectory().getFullPathName() + "\\lastplaylist.dat" };
    juce::File f{ playlistSave };
    if (f.exists())
    {
        juce::StringArray songs = juce::StringArray();
        f.readLines(songs);
        std::vector<juce::String> s;

        for (int i = 0; i < songs.size(); i++)
        {
            s.push_back(songs[i]);
        }
        addPlaylistFiles(s);
        allPlaylistFiles = playlistFiles;
    }

    addAndMakeVisible(tableComponent);
    addAndMakeVisible(searchBar);

    searchBar.setReturnKeyStartsNewLine(false);
    searchBar.onTextChange = [=]()
    {
        playlistFiles.clear();
        searchTracks(searchBar.getText());
    };
}

PlaylistComponent::~PlaylistComponent()
{
    juce::String playlistSave{ juce::File::getCurrentWorkingDirectory().getFullPathName() + "\\lastplaylist.dat"};
    juce::File f{ playlistSave };
    f.deleteFile();
    f = juce::File(playlistSave);

    for (int i = 0; i < playlistFiles.size(); i++)
    {
        f.appendText(playlistFiles[i].file.getFullPathName() + "," +
        playlistFiles[i].name + "," +
        std::to_string(playlistFiles[i].trackLength) + "," +
        std::to_string(playlistFiles[i].beatsPerMin) + "," +
        std::to_string(playlistFiles[i].nativeKey) + "," + 
        std::to_string(playlistFiles[i].isMajor) + "," );
        f.appendText("\n");
    }
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillRect(getLocalBounds());
}

void PlaylistComponent::resized()
{
    tableComponent.setBounds(0, 0, getWidth(), getHeight() * .95);
    searchBar.setBounds(0, getHeight() * .95, getWidth(), getHeight() * .05);
}

int PlaylistComponent::getNumRows()
{
    return playlistFiles.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics & g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::darkorange);
    }
    else g.fillAll(juce::Colours::black);
}

void PlaylistComponent::paintCell(juce::Graphics & g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    std::vector<Track> tablePlaylist;
    if (searching == false) tablePlaylist = playlistFiles;
    if (searching == true) tablePlaylist = displayedFiles;

    juce::String toDraw;
    if (columnId == 1)
    {
        toDraw = tablePlaylist[rowNumber].name;
    }
    if (columnId == 2)
    {
        toDraw = std::to_string(tablePlaylist[rowNumber].trackLength);
    }
    if (columnId == 3)
    {
        toDraw = std::to_string(tablePlaylist[rowNumber].beatsPerMin);
    }
    if (columnId == 4)
    {
        toDraw = std::to_string(tablePlaylist[rowNumber].nativeKey);
    }
    g.setFont(16.0);
    g.setColour(juce::Colours::white);
    g.drawText(toDraw,
        2,
        0,
        width - 4,
        height,
        juce::Justification::centredLeft,
        true);

}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (false)
    {
        if (columnId == 2 || columnId == 3)
        {
            if (existingComponentToUpdate == nullptr && playlistFiles[rowNumber].file.existsAsFile())
            {
                juce::TextButton* btn = new juce::TextButton{ "ADD TO DECK" + std::to_string(columnId - 1) };
                juce::String id{ std::to_string(rowNumber) };
                btn->setComponentID(id);
                btn->addListener(this);
                existingComponentToUpdate = btn;
            }
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    if (button->getButtonText().containsChar('1'))
        d1->loadFileFromPlaylist(playlistFiles[id]);
    else
        d2->loadFileFromPlaylist(playlistFiles[id]);
}

/**Double left click for deck 1, double right click for deck 2*/
void PlaylistComponent::cellDoubleClicked(int rowNumber, int columnId, const juce::MouseEvent& e)
{
    if (e.mods.isLeftButtonDown() == 1) d1->loadFileFromPlaylist(playlistFiles[rowNumber]);
    if (e.mods.isRightButtonDown() == 1) d2->loadFileFromPlaylist(playlistFiles[rowNumber]);
}

void PlaylistComponent::deleteKeyPressed(int currentSelectedRow)
{

    playlistFiles.erase(playlistFiles.begin() + currentSelectedRow);
    tableComponent.updateContent();
    tableComponent.repaint();
}

void PlaylistComponent::returnKeyPressed(int currentSelectedRow)
{
    
    EditTrackInfoModal editTrackInfo(playlistFiles, currentSelectedRow);
    editTrackInfo.setSize(getWidth() * .6, getHeight() * .4);
    juce::DialogWindow::showModalDialog("Edit Track Details...",
        &editTrackInfo,
        this->getParentComponent(),
        juce::Colours::black,
        true);
    playlistFiles = editTrackInfo.getPlaylistFiles();
}

bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
    return true;
}

void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (int i = 0; i < files.size(); i++)
    {
        addSingleSong(files[i]);
    }
}

std::vector<Track> PlaylistComponent::getPlaylistFiles()
{
    return playlistFiles;
}

void PlaylistComponent::setPlaylistFiles(std::vector<Track> newTracks)
{
    playlistFiles = newTracks;
}

void PlaylistComponent::addPlaylistFiles(std::vector<juce::String> tracksFromFile)
{
    juce::String wholeString;
    char delimiter = ',';
    int lastCommaIndex = 0;

    juce::String fileName;
    juce::String trackName;
    float trackLength;
    float beats;
    int key;
    int isMajor;

    for (int i = 0; i < tracksFromFile.size(); i++)
    {
        if (tracksFromFile[i].length() > 1)
        {
            lastCommaIndex = 0;
            wholeString = tracksFromFile[i];
            fileName = wholeString.substring(lastCommaIndex, wholeString.indexOfChar(lastCommaIndex, delimiter));

            lastCommaIndex = wholeString.indexOfChar(0, delimiter) + 1;
            trackName = wholeString.substring(lastCommaIndex, wholeString.indexOfChar(lastCommaIndex, delimiter));

            lastCommaIndex = wholeString.indexOfChar(lastCommaIndex, delimiter) + 1;
            trackLength = wholeString.substring(lastCommaIndex, wholeString.indexOfChar(lastCommaIndex, delimiter)).getFloatValue();

            lastCommaIndex = wholeString.indexOfChar(lastCommaIndex, delimiter) + 1;
            beats = wholeString.substring(lastCommaIndex, wholeString.indexOfChar(lastCommaIndex, delimiter)).getFloatValue();

            lastCommaIndex = wholeString.indexOfChar(lastCommaIndex, delimiter) + 1;
            key = wholeString.substring(lastCommaIndex, wholeString.indexOfChar(lastCommaIndex, delimiter)).getIntValue();

            lastCommaIndex = wholeString.indexOfChar(lastCommaIndex, delimiter) + 1;
            isMajor = wholeString.substring(lastCommaIndex, wholeString.indexOfChar(lastCommaIndex, delimiter)).getIntValue();

            addTrackToPlaylistFiles(fileName, trackLength, beats, key, isMajor, -1, -1, true);
        }
    }

    tableComponent.updateContent();
    tableComponent.repaint();
}

void PlaylistComponent::addTrackToPlaylistFiles(juce::String fileName, float length, float beats, int key, int _isMajor, int id1, int id2, bool displayed)
{

    juce::File f(fileName);

    if (f.getFileExtension().equalsIgnoreCase(".mp3"))
    {
        Track newTrack;
        newTrack.file = f;
        newTrack.name = f.getParentDirectory().getFileName() + "\\" + f.getFileName();
        newTrack.trackLength = length;
        newTrack.beatsPerMin = beats;
        newTrack.nativeKey = key;
        newTrack.isMajor = _isMajor;
        newTrack.buttonID1 = id1;
        newTrack.buttonID1 = id2;
        newTrack.displayed = displayed;
        playlistFiles.push_back(newTrack);
        allPlaylistFiles = playlistFiles;
    }
}

void PlaylistComponent::clearPlaylist()
{
    playlistFiles.clear();
    allPlaylistFiles.clear();
    tableComponent.updateContent();
    tableComponent.repaint();
}

void PlaylistComponent::addSingleSong(juce::File file)
{
    Track newTrack;
    newTrack.file = file;
    newTrack.name = file.getParentDirectory().getFileName() + "\\" + file.getFileName();
    newTrack.nativeKey = 0;
    newTrack.isMajor = 0;
    newTrack.trackLength = -1;
    newTrack.beatsPerMin = -1;
    newTrack.displayed = true;

    playlistFiles.push_back(newTrack);
    allPlaylistFiles = playlistFiles;
    tableComponent.updateContent();
    tableComponent.repaint();
}

void PlaylistComponent::searchTracks(juce::String s)
{
    for (int i = 0; i < allPlaylistFiles.size(); i++)
    {
        if (allPlaylistFiles[i].name.containsIgnoreCase(s))
        {
            playlistFiles.push_back(allPlaylistFiles[i]);
        }

    }
    tableComponent.updateContent();
    tableComponent.repaint();
}

void PlaylistComponent::analyzeSong()
{
    d1->analyzeSong();
}