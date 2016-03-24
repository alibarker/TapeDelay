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
    
    float output;
    
    input*=gain;
    
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
    input*=gain;
    
    float output;
    
    float clipPoint = fabs(threshold);
    
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

