/*
  ==============================================================================

    EditTrackInfoModal.cpp
    Created: 8 Mar 2021 3:41:50pm
    Author:  Colin

  ==============================================================================
*/

#include "EditTrackInfoModal.h"
EditTrackInfoModal::EditTrackInfoModal(std::vector<Track> &_playlistFiles, int currentSelectedRow)
{
    songToChange = currentSelectedRow;
    column2TextEdit.setText(std::to_string(_playlistFiles[currentSelectedRow].trackLength));
    column3TextEdit.setText(std::to_string(_playlistFiles[currentSelectedRow].beatsPerMin));
    column4TextEdit.setText(std::to_string(_playlistFiles[currentSelectedRow].nativeKey));

    column2Label.setText("Set Length", juce::NotificationType::dontSendNotification);
    column3Label.setText("Set BPM", juce::NotificationType::dontSendNotification);
    column4Label.setText("Set Native Key", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(column2Label);
    addAndMakeVisible(column3Label);
    addAndMakeVisible(column4Label);
    addAndMakeVisible(column2TextEdit);
    addAndMakeVisible(column3TextEdit);
    addAndMakeVisible(column4TextEdit);
    saveButton.addListener(this);

    playlistTracks = _playlistFiles;
}



void EditTrackInfoModal::resized()
{
    saveButton.setBounds(getWidth() * 2/ 5,
        getHeight() / 8,
        getWidth() / 5,
        getHeight() / 9);


    column2Label.setBounds(getWidth() / 5,
        getHeight() * .3,
        getWidth() / 5,
        getHeight() * .1);
    column2TextEdit.setBounds(getWidth() * 3/ 5,
        getHeight() * .3,
        getWidth() / 5,
        getHeight() * .1);

    column3Label.setBounds(getWidth() / 5,
        getHeight() * .5,
        getWidth() / 5,
        getHeight() * .1);
    column3TextEdit.setBounds(getWidth() * 3/ 5,
        getHeight() * .5,
        getWidth() / 5,
        getHeight() * .1);

    column4Label.setBounds(getWidth() / 5,
        getHeight() * .7,
        getWidth() / 5,
        getHeight() * .1);
    column4TextEdit.setBounds(getWidth() * 3/ 5,
        getHeight() * .7,
        getWidth() / 5,
        getHeight() * .1);
}

void EditTrackInfoModal::buttonClicked(juce::Button* button)
{
    if (button = &saveButton)
    {
        juce::String newLen = column2TextEdit.getText();
        std::string s = newLen.toStdString();
        playlistTracks[songToChange].trackLength = std::stof(s);

        newLen = column3TextEdit.getText();
        s = newLen.toStdString();
        playlistTracks[songToChange].beatsPerMin = std::stof(s);

        newLen = column4TextEdit.getText();
        s = newLen.toStdString();
        playlistTracks[songToChange].nativeKey = std::stof(s);
    }
}

std::vector<Track> EditTrackInfoModal::getPlaylistFiles()
{
    return playlistTracks;
}