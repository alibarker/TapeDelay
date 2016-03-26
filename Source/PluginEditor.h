/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_4C156990EE00E92C__
#define __JUCE_HEADER_4C156990EE00E92C__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TapeDelayAudioProcessorEditor  : public AudioProcessorEditor,
                                       public Timer
{
public:
    //==============================================================================
    TapeDelayAudioProcessorEditor (TapeDelayAudioProcessor* ownerFilter);
    ~TapeDelayAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void timerCallback();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    class ParameterSlider;
    class ParameterToggleButton;

    TapeDelayAudioProcessor *parentProcessor;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<ParameterSlider> sliderSpeed;
    ScopedPointer<ParameterSlider> sliderReadPosition1;
    ScopedPointer<ParameterSlider> sliderReadPosition2;
    ScopedPointer<ParameterSlider> sliderReadPosition3;
    ScopedPointer<ParameterSlider> sliderReadGain1;
    ScopedPointer<ParameterSlider> sliderReadGain2;
    ScopedPointer<ParameterSlider> sliderReadGain3;
    ScopedPointer<ParameterSlider> sliderInputGain;
    ScopedPointer<Label> label3;
    ScopedPointer<ParameterSlider> sliderOutputGain;
    ScopedPointer<Label> label4;
    ScopedPointer<ParameterSlider> sliderFeedback;
    ScopedPointer<Label> label5;
    ScopedPointer<ParameterSlider> sliderDistortion;
    ScopedPointer<Label> label7;
    ScopedPointer<ParameterSlider> sliderFlutter;
    ScopedPointer<Label> label9;
    ScopedPointer<ParameterSlider> sliderWow;
    ScopedPointer<Label> label10;
    ScopedPointer<ParameterSlider> sliderLowCutoff;
    ScopedPointer<Label> label6;
    ScopedPointer<ParameterSlider> sliderHighCutoff;
    ScopedPointer<Label> label8;
    ScopedPointer<Label> labelReadHead1;
    ScopedPointer<Label> labelReadHead2;
    ScopedPointer<Label> labelReadHead3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TapeDelayAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_4C156990EE00E92C__
