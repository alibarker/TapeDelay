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
    
    void setDist(float value) {distortion = value;}
    void setGain(float value) {gain = value;}
    void setTreshold(float value) {threshold = value;}

    
private:
    float distortion = 8;
    float gain = 1;
    float threshold = 0.3;
    
    int distortionType;
    
};



#endif  // MULTIDISTORTION_H_INCLUDED
