/*
  ==============================================================================

    VariableDelayLine.cpp
    Created: 17 Mar 2016 1:17:12pm
    Author:  Alistair Barker

  ==============================================================================
*/

#include "VariableDelayLine.h"

VariableDelayLine::VariableDelayLine(int numReadHeads)
{
    
    numReadHeads = 1;
    
    currentSpeed = 1.1;
    
    writePointer = 0;
    
    delayLine.setSize(1, DELAY_LINE_SIZE);
    delayLine.clear();
    
    writeHead = new LagrangeInterpolator();
    writeInputBuffer.setSize( 1, DELAY_LINE_SIZE);
    writeInputBuffer.clear();
    
    for (int i = 0; i < numReadHeads; i++) {
        readHeads.add(new LagrangeInterpolator());
        readPointers[i] = DELAY_LINE_SIZE/2;
    }
}

void VariableDelayLine::writeSamples(AudioSampleBuffer &buffer)
{
    
    int numInputSamples = buffer.getNumSamples();
    int numOutputSamples = floor(numInputSamples/currentSpeed);
    
    AudioSampleBuffer bufferToWriteTo;
    bufferToWriteTo.setSize(1, numOutputSamples);
    
    int samplesUsed = writeHead->process(currentSpeed, buffer.getReadPointer(0), bufferToWriteTo.getWritePointer(0, 0), numOutputSamples);

    for (int i = 0; i < numOutputSamples; i++)
    {
        delayLine.setSample(0, writePointer, bufferToWriteTo.getSample(0, i));
        writePointer++;
        
        if (writePointer >= DELAY_LINE_SIZE) {
            writePointer -= DELAY_LINE_SIZE;
        }
    }
    
    
}


void VariableDelayLine::readSamples(int readHeadIndex, AudioSampleBuffer &buffer)
{
    int numOutputSamples = buffer.getNumSamples();
    int maxNumInputSamples = ceil(numOutputSamples/currentSpeed);
    
    AudioSampleBuffer inputBuffer;
    inputBuffer.setSize(1, maxNumInputSamples);
    
    
    for (int i = 0; i < maxNumInputSamples; i++)
    {
        int pos = (readPointers[readHeadIndex] + i + DELAY_LINE_SIZE) % DELAY_LINE_SIZE;
        inputBuffer.setSample(0, i, delayLine.getSample(0, pos));
    }
    
    int samplesUsed =readHeads[readHeadIndex]->process(1/currentSpeed, inputBuffer.getReadPointer(0), buffer.getWritePointer(0), numOutputSamples);
    
    readPointers[readHeadIndex] += samplesUsed;
    if (readPointers[readHeadIndex] >= DELAY_LINE_SIZE) {
        readPointers[readHeadIndex] -= DELAY_LINE_SIZE;
    }
    
    
}

void VariableDelayLine::reset()
{
    delayLine.clear();
    
    writeHead->reset();
    
    
    int numReadHeads = readHeads.size();
    
    for (int i = 0; i < numReadHeads; i++) {
        readHeads[i]->reset();
    }
}

void setSpeed(float speed);
void setReadPosition(int readHeadIndex, float position);

float getDelayTimeMs(int readHeadIndex);