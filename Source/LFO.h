/*
  ==============================================================================

    LFO.h
    Created: 24 Mar 2016 4:38:16pm
    Author:  Alistair Barker

  ==============================================================================
*/

#ifndef LFO_H_INCLUDED
#define LFO_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"

#define WAVETABLE_LENGTH 2048

class LFO {
public:
    LFO();
    void setRate(float rateHz, float sampleRate);
    float getNextSample();
    
private:
    
    float waveTable[WAVETABLE_LENGTH];
    float phase;
    float phaseInc;

};


#endif  // LFO_H_INCLUDED
