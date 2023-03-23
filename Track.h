/*
  ==============================================================================

    Track.h
    Created: 6 Mar 2021 1:12:09pm
    Author:  Colin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct Track {
    juce::File file;
    juce::String name;
    float trackLength;
    float beatsPerMin;
    int nativeKey;
    int isMajor;
    int buttonID1;
    int buttonID2;
    bool displayed;
};

/**Not used, might implement later*/
enum majorKeys {BMAJ=1, FshMAJ =2, CshMAJ =3, GshMAJ =4, DshMAJ =5, AshMAJ =6, FMAJ =7, CMAJ =8, GMAJ =9, DMAJ =10, AMAJ =11, EMAJ =12};
enum minorKeys {GshMIN=1, DshMIN =2, AshMIN =3, FMIN =4, CMIN =5, GMIN =6, DMIN =7, AMIN =8, EMIN =9, BMIN =10, FshMIN =11, CshMIN =12};
