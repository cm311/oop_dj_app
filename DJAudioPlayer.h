/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 8 Feb 2021 6:38:52am
    Author:  Colin

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "VisualsDeck.h"
#include "Track.h"

class DJAudioPlayer : public juce::AudioSource,
                      public juce::AudioPlayHead
{
    
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    //========Pure virtuals from AudioSource===========
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    //=================================================

    //=======Pure virtuals from AudioPlayHead==========
    bool getCurrentPosition(CurrentPositionInfo& result) override;
    //=================================================

    /**Takes in a Track and sets the transport source to its file, so that it can be played
    Also sets the currentTrack variable to the name so that it can be displayed in the DeckGUI*/
    void loadURL(Track trackToLoad);

    /**Sets the volume of the transport source to gain*/
    void setGain(double gain);

    /**Sets the speed of the transport source to ratio
    For example: ratio of 2.2 means it will play at 2.2 speed*/
    void setSpeed(double ratio);

    /**Set the position of the song in seconds*/
    void setPosition(double posInSecs);

    /**Set the relative position of the transport source
    For example: pos of .5 will have the transport source half way through the song*/
    void setPositionRelative(double pos);

    /**returns the relative position of the transport source*/
    double getPositionRelative();

    /**Changes the speed of the track to reflect the new key*/
    void setKey(int newKey);

    /**Returns the key of the track*/
    int getKey();

    /**returns the current beats per minute of the track*/
    float getBPM();

    /**Returns the ratio of the current track*/
    float getSpeed();

    /**Starts playing the transport source*/
    void start();

    /**Pauses the transport source*/
    void pause();

    /**Stops the transport source, and resets the position*/
    void stop();

    /**returns true if the transport source is playing, false if not*/
    bool isPlaying();

    /**returns a String of the name of the track currently playing*/
    juce::String getFileName();

    /**Method that will analyze the BPM of the current track etc.  Not currently implemented, TODO*/
    void analyzeSong();

    /**Sets the visuals area for this player object*/
    void setVisualsArea(VisualsDeck* vis);

    /** Get the relative position of the playhead*/
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
    Track currentTrack;
    float actualBPM = -1;
    int actualKey = -1;
    bool isMajor = true;
    VisualsDeck* visuals;
};