#pragma once

#include <JuceHeader.h>
#include "DeckGUI.h"
#include "DJAudioPlayer.h"
#include "MenuBar.h"
#include "PlaylistComponent.h"
#include "EditTrackInfoModal.h"
#include "VisualsDeck.h"
#include "Track.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //=================Pure Virtuals from AudioAppComponent=========================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    //==============================================================================


    void paint (juce::Graphics& g) override;
    void resized() override;

    /**Called to set some changes to the look and feel, like changing button color and adding custom font.*/
    void updateLookAndFeel();

private:
    juce::Typeface::Ptr fontPointer = juce::Typeface::createSystemTypefaceFor(BinaryData::Ticketing_ttf, BinaryData::Ticketing_ttfSize);
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{ 100 };

    DJAudioPlayer player1{ formatManager};
    DJAudioPlayer player2{ formatManager};
    DeckGUI deckGUI1{ &player1, formatManager, thumbCache};
    DeckGUI deckGUI2{ &player2, formatManager, thumbCache};
    juce::MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent{ std::vector<Track>(), &deckGUI1, &deckGUI2 };
    MenuBar menu{&playlistComponent};

    juce::Colour veryDarkOrange = juce::Colours::darkorange.darker().darker().darker().darker();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
