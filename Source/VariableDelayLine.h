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

#define DELAY_LINE_SIZE 441000
#define BUFFER_SIZE 100

class VariableDelayLine
{
public:
    VariableDelayLine();
    ~VariableDelayLine() {}
    
    void writeSample(float input);
    float readSample(int readHeadIndex);
    
    void prepareToPlay(int numReadHeads, int* readHeadPositions);
    void reset();
        
    void setSpeed(float value) {speed = value; }
    void setReadPosition(int readHeadIndex, int position);
    
private:
    // the delay line buffer
    AudioSampleBuffer delayLine;
    
    // buffers and pointers used on input and output
    AudioSampleBuffer inputBufferA;
    AudioSampleBuffer inputBufferB;
    int inputBufferPtr = 0;
    AudioSampleBuffer outputBuffer;
    int outputBufferPtr;
    AudioSampleBuffer unusedSamples;
    int numUnusedSamples;


    // tape heads
    ScopedPointer<LagrangeInterpolator> writeHead;
    OwnedArray<LagrangeInterpolator> readHeads;
    
    // delay line pointrs
    int writePointer;
    int* readPointers;
    
    // actual speed
    float currentSpeed;
    
    // what the speed parameter is set to
    float speed;
    
    bool isActive;    
    
};


#endif  // VARIABLEDELAYLINE_H_INCLUDED
