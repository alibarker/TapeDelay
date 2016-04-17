/*
 ==============================================================================
 
 VariableDelayLine.cpp
 Created: 17 Mar 2016 1:17:12pm
 Author:  Alistair Barker
 
 ==============================================================================
 */

#include "VariableDelayLine.h"

VariableDelayLine::VariableDelayLine()
{
    isActive = false;
}

void VariableDelayLine::prepareToPlay()
{
    // Initialise buffer
    delayLine.setSize(1, DELAY_LINE_SIZE);
    delayLine.clear();
    
    phase = 0.0;
    isActive = true;
}

float VariableDelayLine::interpolate(float fract, float in1, float in2)
{
    return in1 * (1 - fract) + in2 * fract;
}


void VariableDelayLine::writeSample(float input)
{
    
    if (isActive)
    {
        
        int fph = (int)floor(phase) % DELAY_LINE_SIZE;
        int ph = (last_phase + 1) % DELAY_LINE_SIZE;
        
        float lin_inc = 1.0f / (floor(phase) - (last_phase + 1)% DELAY_LINE_SIZE);
        lin_inc = lin_inc > 1.0f ? 1.0f : lin_inc;
        float lin_int = 0.0f;
        
        while (ph <= fph) {
            lin_int += lin_inc;
            float in = interpolate(lin_int, delayLine.getSample(0, last_phase), input);
            delayLine.setSample(0, ph, in);
            ph = ph + 1;
        }
        last_phase = fph;
        phase += speed;

        if (phase >= DELAY_LINE_SIZE) {
            phase -= DELAY_LINE_SIZE;
        }
        
    
    }

}

float VariableDelayLine::readSample()
{
    if (isActive) {

        int fph = (int)floor(phase) % DELAY_LINE_SIZE;
        float fract = phase - (float)fph;
        float out = interpolate(fract, delayLine.getSample(0, fph % DELAY_LINE_SIZE),
                                     delayLine.getSample(0, (fph+1) % DELAY_LINE_SIZE));
        return out;
    }
    return 0.0;
}

void VariableDelayLine::reset()
{
    // clear deley line
    delayLine.clear();
    
}

void VariableDelayLine::setTimeMs(float value, float sampleRate)
{
    speed = DELAY_LINE_SIZE / (0.001 * value * sampleRate);
    
}