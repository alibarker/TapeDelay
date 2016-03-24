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
    
    inputBufferA.setSize(1, BUFFER_SIZE);
    inputBufferB.setSize(1, BUFFER_SIZE);
    outputBuffer.setSize(1, BUFFER_SIZE);
    

}

void VariableDelayLine::writeSample(float input)
{
    
    if (isActive)
    {
        
        // copy sample to input buffer
        inputBufferA.setSample(0, inputBufferPtr, input);
//        inputBuffera[inputBufferPtr] = input;
        inputBufferPtr++;
       
        int samplesUsed = 0;
        
        int numInputSamplesNeeded = ceil(currentSpeed);
        
        if (currentSpeed < 1) {
            numInputSamplesNeeded++;
        }
        
        // if we have enough input samples
        if (inputBufferPtr >= numInputSamplesNeeded){
            
            // process samples
            
            samplesUsed = writeHead->process(currentSpeed, inputBufferA.getReadPointer(0), inputBufferB.getWritePointer(0), ceil(1/currentSpeed));
//            samplesUsed = writeHead->process(currentSpeed, inputBuffera, inputBufferb, ceil(1/currentSpeed));

            // copy unused samples to beginning of buffer
            for (int i = 0; i < inputBufferPtr - samplesUsed; i++) {
                inputBufferA.setSample(0, i, inputBufferA.getSample(0, inputBufferPtr - 1 + i));
            }
            
            // reset pointer
            inputBufferPtr -= samplesUsed;
            

            for (int i = 0; i < ceil(1/currentSpeed); i++)
            {
                delayLine.setSample(0, writePointer, inputBufferB.getSample(0, i));
                writePointer++;
                
                if (writePointer >= DELAY_LINE_SIZE) {
                    writePointer -= DELAY_LINE_SIZE;
                }
            }
            
            currentSpeed = speed;

            
        }
        
//        DBG("Write: Num used\t" << samplesUsed);

        // copy resampled samples to buffer
        

    }
    
}


float VariableDelayLine::readSample(int readHeadIndex)
{
    if (isActive)
    {
        // copy max number of samples needed from delayline to buffer
        
        int numInputSamples = ceil(1/currentSpeed);
        
        for (int i = 0; i < numInputSamples; i++) {
            
            int ptr = (readPointers[readHeadIndex] + i + DELAY_LINE_SIZE ) % DELAY_LINE_SIZE;
            
            outputBuffer.setSample(0, i, delayLine.getSample(0, ptr));
        }
        
        
        // process samples
        
        float output;
        
        int numSamplesUsed = readHeads[readHeadIndex]->process(1/currentSpeed, outputBuffer.getReadPointer(0), &output, 1);
        
//        DBG("Read: Num In\t" << numInputSamples << " used\t" << numSamplesUsed);

        
        // increment pointer by samples used
        
        readPointers[readHeadIndex] += numSamplesUsed;
        
        if (readPointers[readHeadIndex] >= DELAY_LINE_SIZE) {
            readPointers[readHeadIndex] -= DELAY_LINE_SIZE;
        }
        
        // output latest sample of delayLine
        return output;
        
    }
    
    return 0.0;
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

void VariableDelayLine::setReadPosition(int readHeadIndex, int position)
{
    
    readPointers[readHeadIndex] = (writePointer - position + DELAY_LINE_SIZE) % DELAY_LINE_SIZE;

}

float getDelayTimeMs(int readHeadIndex);