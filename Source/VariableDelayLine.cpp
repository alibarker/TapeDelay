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
             float lin_inc = 1.0f / (floor(phase) - lastPhase + 1);
        lin_inc = lin_inc > 1.0f ? 1.0f : lin_inc;
         float lin_int = 0.0f;
        for (int track = lastPhase; track < phase; track++) {
            lin_int += lin_inc;
            float in = interpolate(lin_int, lastIn, input);
            delayLine.setSample(0, track % DELAY_LINE_SIZE, in);
        }
        lastIn = input;
        
        ;
        if (phase >= DELAY_LINE_SIZE) {
            phase -= DELAY_LINE_SIZE;
        }
        
//        int fph = (int)floor(phase) % DELAY_LINE_SIZE;
//        int ph = (lastPhase + 1) % DELAY_LINE_SIZE;
//        
//        float lin_inc = 1.0f / (floor(phase) - lastPhase + 1);
//        lin_inc = lin_inc > 1.0f ? 1.0f : lin_inc;
//        float lin_int = 0.0f;
//        
//        while (ph <= fph) {
//            lin_int += lin_inc;
//            float in = interpolate(lin_int, delayLine.getSample(0, lastPhase), input);
//            delayLine.setSample(0, ph, in);
//            ph = (ph + 1);
//        }
//        
//        lastIn = input;
//        lastPhase = fph;
//        phase += speed;
//
//        if (phase >= DELAY_LINE_SIZE) {
//            phase -= DELAY_LINE_SIZE;
//        }
//        
    
    }

}

float VariableDelayLine::readSample()
{
    if (isActive) {

        int fph = round(floor(phase));
        lastPhase = fph;
        float lin_int = phase - (float)fph;
        float out = interpolate(lin_int, delayLine.getSample(0, (fph+1) % DELAY_LINE_SIZE),
                                delayLine.getSample(0, (fph+2) % DELAY_LINE_SIZE));
        
        phase += speed;
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