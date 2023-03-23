/*
  ==============================================================================

    DeckGUI.h
    Created: 8 Feb 2021 9:08:42am
    Author:  Colin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaybackControls.h"
#include "SongInfoComponent.h"
#include "VisualsDeck.h"
#include "Track.h"


//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
    public juce::Slider::Listener,
    public juce::FileDragAndDropTarget,
    public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI() override;

    //Component virtual methods
    void paint (juce::Graphics&) override;
    void resized() override;

    //need to implemet cuz we are inheriting button and slider, virtual methods
    void sliderValueChanged(juce::Slider* slider) override;
    
    //FileDragAndDropTarget virtual methods
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    //Timer virual method
    void timerCallback() override;

    //========================================NON VIRTUAL METHODS=============================================

    /**Returns the key that the loaded track is currently in*/
    int getKey();

    /**Takes in a Track file and loads it into the DeckGUI for playing*/
    void loadFileFromPlaylist(Track& f);

    /**Eventually plan to use this to find the BPM and other stuff about the track*/
    void analyzeSong();

    //========================================================================================================


private:
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    juce::Slider keySlider;


    DJAudioPlayer* player;
    SongInfoComponent songInfo{player};
    PlaybackControls controls{player};
    WaveformDisplay waveformDisplay;
    VisualsDeck visuals;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
