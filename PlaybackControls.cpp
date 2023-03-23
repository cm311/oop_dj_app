/*
  ==============================================================================

    PlaybackControls.cpp
    Created: 4 Mar 2021 4:24:01am
    Author:  Colin

  ==============================================================================
*/

#include "PlaybackControls.h"


PlaybackControls::PlaybackControls(DJAudioPlayer* player) :
    player(player)
{
    addMouseListener(this, true);
}

PlaybackControls::~PlaybackControls()
{

}

void PlaybackControls::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::darkorange);

    float buttonW = getWidth() / 6;
    float buttonH = getHeight() / 3;

    //Back Button
    g.drawLine(buttonW + buttonW * .1, getHeight() / 2,
        buttonW + buttonW * .35, buttonH, 2);
    g.drawLine(buttonW + buttonW * .1, getHeight() / 2,
        buttonW + buttonW * .35, buttonH * 2, 2);
    g.drawLine(buttonW + buttonW * .35, buttonH,
        buttonW + buttonW * .35, buttonH * 2, 2);

    g.setColour(juce::Colours::darkorange);
    if (player->isPlaying())
    {
        g.drawRect(buttonW * 2, buttonH, buttonW * .7, buttonH);
    }
    else
    {
        //Play Button
        g.drawLine(buttonW * 2, buttonH, buttonW * 2, buttonH * 2, 2);
        g.drawLine(buttonW * 2, buttonH,
            buttonW * 2 + buttonW * .75, getHeight() / 2, 2);
        g.drawLine(buttonW * 2, buttonH * 2,
            buttonW * 2 + buttonW * .75, getHeight() / 2, 2);
    }

    //Pause Button
    g.drawRect(buttonW * 3, buttonH,
        buttonW * .2, buttonH);
    g.drawRect(buttonW * 3 + buttonW * .3, buttonH,
        buttonW * .2, buttonH);

    //Next Button
    g.drawLine(buttonW * 4, buttonH, buttonW * 4, buttonH * 2, 2);
    g.drawLine(buttonW * 4, buttonH,
        buttonW * 4 + buttonW * .25, getHeight() / 2, 2);
    g.drawLine(buttonW * 4, buttonH * 2,
        buttonW * 4 + buttonW * .25, getHeight() / 2, 2);
    repaint();
}

void PlaybackControls::mouseDown(const juce::MouseEvent& event)
{
    double x = event.getPosition().x;
    double y = event.getPosition().y;
    double buttonW = getWidth() / 6;

    if (x > buttonW && x < buttonW * 2)
    {
        DBG("Back button clicked");

        double currentPos = player->getPositionRelative();
        player->setPositionRelative(currentPos - .01);
    }
    if (x > buttonW * 2 && x < buttonW * 3)
    {
        if (!playing)
        {
            player->start();
            mouseCount++;

            if (mouseCount == 2)
            {
                playing = !playing;
                mouseCount = 0;
            }
        }
        else
        {
            player->stop();
            mouseCount++;

            if (mouseCount == 2)
            {
                playing = !playing;
                mouseCount = 0;
            }
        }
    }
    if (x > buttonW * 3 && x < buttonW * 4)
    {
        if (playing == true)
        {
            player->pause();
            playing = false;
        }
    }
    if (x > buttonW * 4 && x < buttonW * 5)
    {
        DBG("next button clicked");
        double currentPos = player->getPositionRelative();
        player->setPositionRelative(currentPos + .01);
    }
}

void PlaybackControls::mouseMove(const juce::MouseEvent& event)
{
    double x = event.getPosition().x;
    double y = event.getPosition().y;
    double buttonW = getWidth() / 6;

    if (x > buttonW && x < buttonW * 2)
    {
        DBG("Back button hover");
    }
    if (x > buttonW * 2 && x < buttonW * 3)
        DBG("play button hover");
    if (x > buttonW * 3 && x < buttonW * 4)
        DBG("pauuse button hover");
    if (x > buttonW * 4 && x < buttonW * 5)
        DBG("next button hover");
}
