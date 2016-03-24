/*
  ==============================================================================

    Compressor.cpp
    Created: 8 Mar 2016 11:55:52am
    Author:  Alistair Barker
 
    Based on the compressor example plug-in by Reiss and McPherson

  ==============================================================================
*/

#include "Compressor.h"

float Compressor::processSample(float input)
    { //
        float output;
        
        if (compressorONOFF) // check if compressor is active
        {
            if ( (threshold< 0) ) // check if compressor threshold is non-zero
            {
                // compression : calculates the control voltage
                float alphaAttack = exp(-1/(0.001 * samplerate * tauAttack));
                float alphaRelease= exp(-1/(0.001 * samplerate * tauRelease));

                    //Level detection- estimate level using peak detector
                if (fabs(input) < 0.000001)
                {
                    x_g =-120;
                }
                else
                {
                    x_g =20*log10(fabs(input));
                }
                
                //Gain computer - apply input/output curve with kneewidth
                if (2 * (x_g-threshold) >= kneeWidth)
                {
                    // above knee
                    y_g = threshold;
                }
                else if (2 * fabs(x_g - threshold) <= kneeWidth)
                {
                    // in knee
                    y_g = x_g + (1/ratio - 1) * pow(x_g - threshold + kneeWidth/2, 2)/(2 * kneeWidth);
                }
                else {
                    // below knee
                    y_g = x_g;
                }
                
                x_l = x_g - y_g;
                
                //Ballistics- smoothing of the gain
                if (x_l>yL_prev)  y_l=alphaAttack * yL_prev+(1 - alphaAttack ) * x_l ;
                else			  y_l=alphaRelease* yL_prev+(1 - alphaRelease) * x_l ;
                
                
                //find control voltage
                c = pow(10,(makeUpGain - y_l)/20);
                yL_prev=y_l;
               
                // apply control voltage to both channels
                output = input * c;
            }
            else
            {
                // if threshold = 0, still apply make up gain.
                output = input  * pow(10,(makeUpGain)/20);
            }
        }
        
        return output;
    }
    
void Compressor::setParameters(float ra, float t, float a, float re, float m, float kw)
{
    ratio = ra;
    threshold = t;
    tauAttack = a;
    tauRelease = re;
    makeUpGain = Decibels::gainToDecibels(m);
    kneeWidth = kw;
        
}
    
void Compressor::prepareToPlay (double sr, int samplesPerBlock, int numInputChannels)
{
    
    samplerate = sr;
    // Allocate a lot of dynamic memory here
    yL_prev=0;
}