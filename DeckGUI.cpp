#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse) : player(_player),
    waveformDisplay(formatManagerToUse, cacheToUse)
{
    DBG("Constructing a DeckGUI");
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(keySlider);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(controls);
    addAndMakeVisible(songInfo);
    addAndMakeVisible(visuals);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    keySlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.3, 3.0);
    posSlider.setRange(0.0, 1.0);
    keySlider.setRange(-12, 12, 1);

    //Make it so the sliders reflect the accurate values when starting the program
    volSlider.setValue(1.0);
    speedSlider.setValue(1.0);
    posSlider.setValue(0.0);
    keySlider.setValue(0);

    startTimer(500);
    player->setVisualsArea(&visuals);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour(juce::Colours::black);

    g.setFont(16.0f);
    g.setColour (juce::Colours::white);
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 19;


    volSlider.setBounds(0, 0, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 1, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    keySlider.setBounds(0, rowH * 3, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH * 4, getWidth(), rowH * 2);
    songInfo.setBounds(0, rowH * 6, getWidth(), rowH * 3);
    controls.setBounds(0, rowH * 9, getWidth(), rowH * 2);
    visuals.setBounds(0, rowH * 11, getWidth(), rowH * 8);
}

void DeckGUI::loadFileFromPlaylist(Track& t)
{
    DBG("Loading file " + t.name);
    player->loadURL( t );

    DBG("File loaded by player...  Now trying waveform display");
    waveformDisplay.loadURL(juce::URL{ t.file });
    t.trackLength = waveformDisplay.getTotalLength();
    songInfo.setSongLength(t.trackLength);

    DBG("File Successfully loaded from playlist");
    keySlider.setValue(0);
    speedSlider.setValue(1.0);
    posSlider.setValue(0);
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    if (slider == &keySlider)
    {
        player->setKey(slider->getValue());
        speedSlider.setValue(player->getSpeed());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    if (files.size() == 1)
    {
        Track t;
        t.file = juce::File{ files[0] };
        t.name = t.file.getParentDirectory().getFileName() + "\\" + t.file.getFileName();
        player->loadURL(t);
    }
}

int DeckGUI::getKey()
{
    return player->getKey();
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    repaint();
}

void DeckGUI::analyzeSong()
{
    player->analyzeSong();
}