/*
  ==============================================================================

    VariableDelayLine.h
    Created: 17 Mar 2016 1:17:12pm
    Author:  Alistair Barker

  ==============================================================================
*/

#ifndef VARIABLEDELAYLINE_H_INCLUDED
#define VARIABLEDELAYLINE_H_INCLUDED

#include "JuceHeader.h"

#define DELAY_LINE_SIZE 22050

class VariableDelayLine
{
public:
    VariableDelayLine();
    ~VariableDelayLine() {}
    
    void writeSample(float input);
    float readSample();

    void prepareToPlay();
    void reset();
        
    void setSpeed(float value) {speed = value; }
    void setTimeMs(float value, float sampleRate);
private:
    
    float interpolate(float fract, float in1, float in2);

    // the delay line buffer
    AudioSampleBuffer delayLine;

    // delay line pointrs
    float phase;
    int lastPhase;
    float lastIn;
    
    // state variables
    float speed;
    bool isActive;
    
};


#endif  // VARIABLEDELAYLINE_H_INCLUDED
