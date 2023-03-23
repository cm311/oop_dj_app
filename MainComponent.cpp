#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1600, 900);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
    DBG("Constructing main component");
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);

    addAndMakeVisible(menu);
    addAndMakeVisible(playlistComponent);

    formatManager.registerBasicFormats();
    DBG("Formats added");

    updateLookAndFeel();
    DBG("Look and Feel updated");
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    DBG("Main Component prepare to play");
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
}

void MainComponent::resized()
{
    double row = getHeight() / 20;

    menu.setBounds(0, 0, getWidth(), row);
    playlistComponent.setBounds(0, row, getWidth() / 2, getHeight() - row);
    deckGUI1.setBounds(getWidth() / 2, row, getWidth() / 4, row * 19);
    deckGUI2.setBounds(getWidth() / 2 + getWidth() / 4, row, getWidth() / 4, row * 19);
}

void MainComponent::updateLookAndFeel()
{
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::darkorange);
    getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colours::ghostwhite);
    getLookAndFeel().setColour(juce::Slider::backgroundColourId, veryDarkOrange);
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    getLookAndFeel().setColour(juce::TableListBox::backgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(juce::TextEditor::backgroundColourId, veryDarkOrange);
    getLookAndFeel().setDefaultSansSerifTypeface(fontPointer);
}
