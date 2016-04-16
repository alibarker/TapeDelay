/*
  ==============================================================================

    Compressor.h
    Created: 8 Mar 2016 11:55:52am
    Author:  Alistair Barker
 
    Based on the compressor example plug-in by Reiss and McPherson


  ==============================================================================
*/

#ifndef COMPRESSOR_H_INCLUDED
#define COMPRESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"



class Compressor
{
public:
    Compressor(){}
    ~Compressor(){}
    
    void prepareToPlay (double sr, int samplesPerBlock, int numInputChannels);
    float processSample(float input);
    void setParameters(float ra, float t, float a, float re, float m, float kw);
    
private:
    
    // parameters
    float ratio;
    float threshold;
    float tauAttack;
    float tauRelease;
    float makeUpGain;
    float kneeWidth;
    int compressorONOFF = 1;
        
    float samplerate;
        
    // input/output gains & input/output level (dB)
    float x_g, y_g, x_l, y_l;
    // previous output level (used for ballistics)
    float yL_prev;

    // control voltage
    float c;
};



#endif  // COMPRESSOR_H_INCLUDED
