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
    currentSpeed = 1;
    
}

void VariableDelayLine::prepareToPlay(int numReadHeads, int *positions)
{
    
    delayLine.setSize(1, DELAY_LINE_SIZE);
    delayLine.clear();

    unusedSamples.setSize(1, 512);
    numUnusedSamples = 0;
    
    writePointer = 0;
    
    writeHead = new LagrangeInterpolator();
    writeInputBuffer.setSize( 1, DELAY_LINE_SIZE);
    writeInputBuffer.clear();
    
    readHeads.clear();
    readPointers = new int[numReadHeads]();
    
    for (int i = 0; i < numReadHeads; i++) {
        readHeads.add(new LagrangeInterpolator);
        readPointers[i] = (writePointer - positions[i] + DELAY_LINE_SIZE) % DELAY_LINE_SIZE;
    }
    
    isActive = true;
}

void VariableDelayLine::writeSamples(AudioSampleBuffer &buffer)
{
    
    if (isActive)
    {
        float speed = currentSpeed;
        
        int numInputSamples = buffer.getNumSamples() + numUnusedSamples; // Number of sample in input buffer
        int numOutputSamples = floor((numInputSamples-1)/speed); // Number of samples to be produced
                                                                 // -1 ensures input used < input
        
        // Buffer to to use as input to delay line
        AudioSampleBuffer bufferToCopyFrom;
        bufferToCopyFrom.setSize(1, numInputSamples);

        // Check if there were any unused samples and populate input buffer accordingly
        if (numUnusedSamples > 0) {
            bufferToCopyFrom.copyFrom(0, 0,
                                      unusedSamples, 0, 0, numUnusedSamples);
            bufferToCopyFrom.copyFrom(0, numUnusedSamples, buffer, 0, 0, buffer.getNumSamples());
            numUnusedSamples = 0;
        } else
        {
            bufferToCopyFrom.copyFrom(0, 0, buffer, 0, 0, buffer.getNumSamples());
        }
        
        // Buffer to write output of sample
        AudioSampleBuffer bufferToWriteTo;
        bufferToWriteTo.setSize(1, numOutputSamples);
        
        // Process buffer and store number of samples unused.
        int samplesUsed = writeHead->process(speed, bufferToCopyFrom.getReadPointer(0), bufferToWriteTo.getWritePointer(0, 0), numOutputSamples);

        numUnusedSamples = numInputSamples - samplesUsed;
        
        // If unused input samples copy them to buffer to reuse on next block
        if (numUnusedSamples > 0)
        {
            unusedSamples.copyFrom(0, 0, bufferToCopyFrom, 0, samplesUsed, numUnusedSamples);
        }
        
        DBG("Unused Samples: \t" << numUnusedSamples);
        
        // Copy resampled output to delay line
        for (int i = 0; i < numOutputSamples; i++)
        {
            delayLine.setSample(0, writePointer, bufferToWriteTo.getSample(0, i));
            writePointer++;
            
            if (writePointer >= DELAY_LINE_SIZE) {
                writePointer -= DELAY_LINE_SIZE;
            }
        }
    }
    
}


void VariableDelayLine::readSamples(int readHeadIndex, AudioSampleBuffer &buffer)
{
    if (isActive)
    {
        float speed = currentSpeed;
        
        int numOutputSamples = buffer.getNumSamples();
        int maxNumInputSamples = ceil(numOutputSamples/speed);
        
        AudioSampleBuffer inputBuffer;
        inputBuffer.setSize(1, maxNumInputSamples);
        
        
        for (int i = 0; i < maxNumInputSamples; i++)
        {
            int pos = (readPointers[readHeadIndex] + i + DELAY_LINE_SIZE) % DELAY_LINE_SIZE;
            inputBuffer.setSample(0, i, delayLine.getSample(0, pos));
        }
        
        int samplesUsed =readHeads[readHeadIndex]->process(1/speed, inputBuffer.getReadPointer(0), buffer.getWritePointer(0), numOutputSamples);
        
        readPointers[readHeadIndex] += samplesUsed;
        if (readPointers[readHeadIndex] >= DELAY_LINE_SIZE) {
            readPointers[readHeadIndex] -= DELAY_LINE_SIZE;
        }
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

void setReadPosition(int readHeadIndex, float position)
{
    
    
}

float getDelayTimeMs(int readHeadIndex);