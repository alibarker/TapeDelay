/*
  ==============================================================================

    TubeDistortion.h
    Created: 16 Mar 2016 8:45:44pm
    Author:  Alistair Barker

  ==============================================================================
*/

#ifndef TUBEDISTORTION_H_INCLUDED
#define TUBEDISTORTION_H_INCLUDED

#include "JuceHeader.h"

class TubeDistortion {
public:
    
    TubeDistortion(){}
    ~TubeDistortion(){}
    
    float processSample(float input);
    void setGain(float g) {gain = g;}
    
    
private:
    float Q = -0.2;
    float distortion = 8;
    float gain = 0.75;
};



#endif  // TUBEDISTORTION_H_INCLUDED
