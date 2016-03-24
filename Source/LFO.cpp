/*
  ==============================================================================

    LFO.cpp
    Created: 24 Mar 2016 4:38:16pm
    Author:  Alistair Barker

  ==============================================================================
*/

#include "LFO.h"

LFO::LFO()
{
    for (int i = 0; i < WAVETABLE_LENGTH; i++)
    {
        waveTable[i] = sin(2 * M_PI * i / WAVETABLE_LENGTH);
        
    }
    
    
}

void LFO::setRate(float rateHz, float sampleRate)
{
    phaseInc = 2 * M_PI * rateHz / sampleRate;
    
}

float LFO::getNextSample()
{
    
    float output =  sinf(phase);
    phase += phaseInc;
    if (phase > 2 * M_PI)
    {
        phase -= 2 * M_PI;
    }
    
    return output;
}