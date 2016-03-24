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
    
    float getDelayTimeMs(int readHeadIndex);
    
private:
    
    AudioSampleBuffer delayLine;
    
    AudioSampleBuffer inputBufferA;
    AudioSampleBuffer inputBufferB;

    int inputBufferPtr = 0;
    AudioSampleBuffer outputBuffer;

    int outputBufferPtr;

    ScopedPointer<LagrangeInterpolator> writeHead;
    OwnedArray<LagrangeInterpolator> readHeads;
    
    int writePointer;
    AudioSampleBuffer writeInputBuffer;
    int writeInputBufferWritePointer = 0;
    int writeInputBufferReadPointer = 0;
    
    AudioSampleBuffer unusedSamples;
    int numUnusedSamples;
    int* readPointers;
    
    float currentSpeed;
    float speed;
    
    
    bool isActive;
    
    AudioProcessor* processor;
    
    
};


#endif  // VARIABLEDELAYLINE_H_INCLUDED
