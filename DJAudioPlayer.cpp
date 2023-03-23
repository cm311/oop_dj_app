#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
    : formatManager(_formatManager)
{
    DBG("Constructing DJAudioPlayer");
}


DJAudioPlayer::~DJAudioPlayer()
{

}

//========Pure virtuals from AudioSource===========
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
   resampleSource.getNextAudioBlock(bufferToFill);
   juce::Range<float> ranges = bufferToFill.buffer->findMinMax(0, 0, 441);
   visuals->addRangeToSongVisual(ranges);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(Track trackToLoad)
{
    currentTrack = trackToLoad;
    DBG("Current track assigned in loadURL");
    actualBPM = currentTrack.beatsPerMin;
    DBG("Current track BPM read");
    actualKey = currentTrack.nativeKey;
    DBG("Current track nativeKey read");
    juce::URL u(currentTrack.file);
    DBG("Trying to load the file: " + currentTrack.file.getFullPathName());
    auto* reader = formatManager.createReaderFor(u.createInputStream(false));
    if (reader != nullptr) //did formatManager successfully create the reader?
    {
        DBG("File successfully created");
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        DBG("transport Source set");
    }
}

void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0) DBG("DJAudioPlayer::setGain gain should be btw 0 and 1");
    else transportSource.setGain(gain);
}

float DJAudioPlayer::getSpeed()
{
    return actualBPM/currentTrack.beatsPerMin;
}

void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 3.0) DBG("DJAudioPlayer::setSpeed speed should be btw .3 and 3");
    else
    {
        resampleSource.setResamplingRatio(ratio);
        actualBPM = currentTrack.beatsPerMin * ratio;
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)  DBG("pos should be btw 0 and 1");
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::setKey(int newKey)
{
    int n = newKey;
    actualKey = currentTrack.nativeKey + newKey;
    DBG("n = " + std::to_string(n));
    float newBPM;
    
    newBPM = 1.0f * currentTrack.beatsPerMin * pow(2, (1.0f * n / 12));
    float newSpeed = 1.0f * newBPM / currentTrack.beatsPerMin;

    DBG("Setting speed to " + std::to_string(newSpeed));

    actualKey = (currentTrack.nativeKey + (7*newKey) % 12);

    setSpeed(newSpeed);
}

int DJAudioPlayer::getKey()
{
    if (currentTrack.name.length() > 0)
    {
        if (actualKey < 1)
            return actualKey + 12;
        if (actualKey < 13)
            return actualKey;
        else
            return actualKey % 12;
    }
    else return 0;
}

float DJAudioPlayer::getBPM()
{
    return actualBPM;
}

void DJAudioPlayer::start()
{
    transportSource.start();
}

void DJAudioPlayer::pause()
{
    transportSource.stop();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
    transportSource.setPosition(0);
}

bool DJAudioPlayer::isPlaying()
{
    return transportSource.isPlaying();
}

juce::String DJAudioPlayer::getFileName()
{
    return currentTrack.name;
}

double DJAudioPlayer::getPositionRelative()
{
    double pos = transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    if (isnan(pos)) {
        return 0;
    }
    return pos;
}

bool DJAudioPlayer::getCurrentPosition(CurrentPositionInfo& result)
{
    return true;
}

void DJAudioPlayer::setVisualsArea(VisualsDeck* vis)
{
    visuals = vis;
}

void DJAudioPlayer::analyzeSong()
{
    
}





