
#pragma once

#include <JuceHeader.h>

class WaveformDisplay  : public juce::Component,
    public juce::ChangeListener
{
public:
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /**Loads a file location, also used to set the song info's length*/
    void loadURL(juce::URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

    /**used to get the private variable totalLength so that DeckGUI and its other children can interact with it*/
    double getTotalLength();

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    double totalLength = 0;
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
