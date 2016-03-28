/*
 ==============================================================================
 
 MultiDistortion.cpp
 Created: 16 Mar 2016 8:45:44pm
 Author:  Alistair Barker
  
 ==============================================================================
 */

#include "MultiDistortion.h"
#include <math.h>

float MultiDistortion::processSample(float input, int type)
{
 
    // process input sample based on type
    switch (type) {
        case distTypeTube:
            return tubeClip(input);
            break;
        case distTypeSoftClip:
            return softClip(input);
            break;
            
        default:
            return input;
            break;
    }
    
}

float MultiDistortion::tubeClip(float input)
{
    // based on the tube emulation in DAFx book

    float output;
    
    // apply gain
    input*=gain;
    
    // apply input/output curve
    // if statements stop division by zero
    if (threshold == 0)
    {
        if(input == threshold)
            output = 1/distortion;
        else
            output = input/(1 - exp(-distortion*input));
        
    }
    else
    {
        
        if(input == threshold)
            output = 1/distortion + threshold/(1-exp(distortion*threshold));
        else
            output = (input-threshold)/(1 - exp(-distortion*(input - threshold))) + threshold/(1-exp(distortion*threshold));
    }

    return output;
}

float MultiDistortion::softClip(float input)
{
    // based on the soft clip function in DAFx book
    
    // apply gain
    input*=gain;
    
    float output;
    float clipPoint = fabs(threshold);
    
    
    // apply non-linearity depending on the input level
    if (fabs(input) < clipPoint) {
        output = 2 * input;
    } else if (fabs(input) >= clipPoint && std::fabs(input) <= 2 * clipPoint) {
        
        if(input > 0) output = pow((3 - (2 - input * 3)), 2)/3;
        if (input < 0) output = -pow((3 - (2 - fabs(input) * 3)), 2)/3;
        
    } else if (fabs(input) > 2 * clipPoint)
    {
        if(input > 0) output = 1;
        if (input < 0) output = -1;

    }
    
    return output;
}

