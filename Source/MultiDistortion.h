/*
  ==============================================================================

    MultiDistortion.h
    Created: 16 Mar 2016 8:45:44pm
    Author:  Alistair Barker

  ==============================================================================
*/

#ifndef MULTIDISTORTION_H_INCLUDED
#define MULTIDISTORTION_H_INCLUDED

enum {
    distTypeTube = 0,
    distTypeSoftClip,
    distTypeBitCrush
};

#include "JuceHeader.h"

class MultiDistortion {
public:
    
    MultiDistortion(){}
    ~MultiDistortion(){}
    
    float processSample(float input, int distType);
    
    float tubeClip(float input);
    float softClip(float input);
    float bitCrush(float input);
    
    void setGain(float g) {gain = g;}
    
    
private:
    float Q = -0.2;
    float distortion = 8;
    float gain = 0.75;
    
    int distortionType;
    
};



#endif  // MULTIDISTORTION_H_INCLUDED
