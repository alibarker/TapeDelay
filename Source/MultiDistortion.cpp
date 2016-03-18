/*
 ==============================================================================
 
 MultiDistortion.cpp
 Created: 16 Mar 2016 8:45:44pm
 Author:  Alistair Barker
 
 ==============================================================================
 */

#include "MultiDistortion.h"

float MultiDistortion::processSample(float input, int type)
{
    switch (type) {
        case distTypeTube:
            return tubeClip(input);
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
    
    if (Q == 0)
    {
        if(input == Q)
            output = 1/distortion;
        else
            output = input/(1 - exp(-distortion*input));
        
    }
    else
    {
        
        if(input == Q)
            output = 1/distortion + Q/(1-exp(distortion*Q));
        else
            output = (input-Q)/(1 - exp(-distortion*(input - Q))) + Q/(1-exp(distortion*Q));
    }
    
    
    
    return output;
}
