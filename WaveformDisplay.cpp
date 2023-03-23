
#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse) : 
        fileLoaded(false),
        audioThumb(1000, formatManagerToUse, cacheToUse),
        position(0)
{
    audioThumb.addChangeListener(this);
    DBG("Constructing waveform display");
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);   // clear the background
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (juce::Colours::darkorange);

    if (fileLoaded)
    {
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f);
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth(),
            0,
            getWidth() / 40,
            getHeight());
    }
    else
    {
        g.setFont(22.0f);
        g.setColour(juce::Colours::ghostwhite);
        g.drawText("File not loaded...", getLocalBounds(),
            juce::Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        totalLength = audioThumb.getTotalLength();
    }
    else std::cout << "wfd: notLoaded" << std::endl;
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    std::cout << "change recieved" << std::endl;
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}

double WaveformDisplay::getTotalLength()
{
    return totalLength;
}
