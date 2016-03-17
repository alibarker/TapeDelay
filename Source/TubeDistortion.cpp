/*
 ==============================================================================
 
 TubeDistortion.cpp
 Created: 16 Mar 2016 8:45:44pm
 Author:  Alistair Barker
 
 ==============================================================================
 */

#include "TubeDistortion.h"

float TubeDistortion::processSample(float input)
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
