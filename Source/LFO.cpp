/*
  ==============================================================================

    LFO.cpp
    Created: 24 Mar 2016 4:38:16pm
    Author:  Alistair Barker
 
    Basic sine function generator

  ==============================================================================
*/

#include "LFO.h"

void LFO::setRate(float rateHz, float sampleRate)
{
    // set the phase increment per sample
    phaseInc = 2 * M_PI * rateHz / sampleRate;
}

float LFO::getNextSample()
{
    // generate output
    float output =  sinf(phase);
    
    // increment phase
    phase += phaseInc;
    
    //  wrap phase if needed
    if (phase > 2 * M_PI)
        phase -= 2 * M_PI;
    
    return output;
}