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

#define DELAY_LINE_SIZE 44100

class VariableDelayLine
{
public:
    VariableDelayLine(int numReadHeads);
    ~VariableDelayLine() {}
    
    void writeSamples(AudioSampleBuffer &buffer);
    void readSamples(int readHeadIndex, AudioSampleBuffer &buffer);
    
    void reset();
    
    void setSpeed(float speed) {currentSpeed = speed;}
    void setReadPosition(int readHeadIndex, float position);
    
    float getDelayTimeMs(int readHeadIndex);
    
private:
    
    AudioSampleBuffer delayLine;
    
    ScopedPointer<LagrangeInterpolator> writeHead;
    OwnedArray<LagrangeInterpolator> readHeads;
    
    int writePointer;
    AudioSampleBuffer writeInputBuffer;
    int writeInputBufferWritePointer = 0;
    int writeInputBufferReadPointer = 0;

    int readPointers[1];
    
    float currentSpeed;
    bool isActive;
    
    
};


#endif  // VARIABLEDELAYLINE_H_INCLUDED
