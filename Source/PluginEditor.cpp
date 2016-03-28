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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"

//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

class TapeDelayAudioProcessorEditor::ParameterSlider   : public Slider,
                                                                private Timer
{
    
    // A class which can link a parameter to a slider
    
public:
    ParameterSlider (AudioProcessorParameter& p)
    : Slider (p.getName (256)), param (p)
    {
        setRange (0.0, 1.0, 0.0);
        startTimerHz (30);
        updateSliderPos();
    }

    void valueChanged() override
    {
        param.setValueNotifyingHost ((float) Slider::getValue());
    }

    void timerCallback() override       { updateSliderPos(); }

    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }

    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }

    void updateSliderPos()
    {
        const float newValue = param.getValue();

        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue);
    }

    AudioProcessorParameter& param;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
};


//[/MiscUserDefs]

//==============================================================================
TapeDelayAudioProcessorEditor::TapeDelayAudioProcessorEditor (TapeDelayAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter), parentProcessor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..

    startTimerHz(30);
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             String()));

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Read Head Gains")));

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Read Head Positions")));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Tape Speed")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderSpeed = new ParameterSlider (*processor.getParameters()[kSpeed]));
    sliderSpeed->setName ("Speed");

    addAndMakeVisible (sliderReadPosition1 = new ParameterSlider (*processor.getParameters()[kReadPosition1]));
    sliderReadPosition1->setName ("Read Head Position 1");

    addAndMakeVisible (sliderReadPosition2 = new ParameterSlider (*processor.getParameters()[kReadPosition2]));
    sliderReadPosition2->setName ("Read Head Position 2");

    addAndMakeVisible (sliderReadPosition3 = new ParameterSlider (*processor.getParameters()[kReadPosition3]));
    sliderReadPosition3->setName ("Read Head Position 3");

    addAndMakeVisible (sliderReadGain1 = new ParameterSlider (*processor.getParameters()[kReadGain1]));
    sliderReadGain1->setName ("Read Head Gain 1");

    addAndMakeVisible (sliderReadGain2 = new ParameterSlider (*processor.getParameters()[kReadGain2]));
    sliderReadGain2->setName ("Read Head Gain 2");

    addAndMakeVisible (sliderReadGain3 = new ParameterSlider (*processor.getParameters()[kReadGain3]));
    sliderReadGain3->setName ("Read Head Gain 3");

    addAndMakeVisible (sliderInputGain = new ParameterSlider (*processor.getParameters()[kInputGain]));
    sliderInputGain->setName ("Input Gain");

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Output Gain")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderOutputGain = new ParameterSlider (*processor.getParameters()[kOutputGain]));
    sliderOutputGain->setName ("Output Gain");

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Input Gain")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderFeedback = new ParameterSlider (*processor.getParameters()[kFeedback]));
    sliderFeedback->setName ("Feedback");

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Feedback")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderDistortion = new ParameterSlider (*processor.getParameters()[kDistortion]));
    sliderDistortion->setName ("Feedback");

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Distortion")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderFlutter = new ParameterSlider (*processor.getParameters()[kFlutter]));
    sliderFlutter->setName ("Feedback");

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Flutter")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderWow = new ParameterSlider (*processor.getParameters()[kWow]));
    sliderWow->setName ("Feedback");

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Wow")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderLowCutoff = new ParameterSlider (*processor.getParameters()[kLowCutoff]));
    sliderLowCutoff->setName ("Low Cutoff");

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Low Cut:")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderHighCutoff = new ParameterSlider (*processor.getParameters()[kHighCutoff]));
    sliderHighCutoff->setName ("High TCutoff");

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("High Cut:")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelReadHead1 = new Label ("new label",
                                                   TRANS("label text")));
    labelReadHead1->setFont (Font (15.00f, Font::plain));
    labelReadHead1->setJustificationType (Justification::centredLeft);
    labelReadHead1->setEditable (false, false, false);
    labelReadHead1->setColour (TextEditor::textColourId, Colours::black);
    labelReadHead1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelReadHead2 = new Label ("new label",
                                                   TRANS("label text")));
    labelReadHead2->setFont (Font (15.00f, Font::plain));
    labelReadHead2->setJustificationType (Justification::centredLeft);
    labelReadHead2->setEditable (false, false, false);
    labelReadHead2->setColour (TextEditor::textColourId, Colours::black);
    labelReadHead2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelReadHead3 = new Label ("new label",
                                                   TRANS("label text")));
    labelReadHead3->setFont (Font (15.00f, Font::plain));
    labelReadHead3->setJustificationType (Justification::centredLeft);
    labelReadHead3->setEditable (false, false, false);
    labelReadHead3->setColour (TextEditor::textColourId, Colours::black);
    labelReadHead3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    sliderInputGain->setSliderStyle(juce::Slider::LinearVertical);
    sliderInputGain->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 24);
    sliderInputGain->setSkewFactor(4);

    sliderOutputGain->setSliderStyle(juce::Slider::LinearVertical);
    sliderOutputGain->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 24);
    sliderOutputGain->setSkewFactor(4);

    sliderFeedback->setSliderStyle(juce::Slider::Rotary );
    sliderFeedback->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 24);
    sliderFeedback->setSkewFactor(4);

    sliderDistortion->setSliderStyle(juce::Slider::Rotary);
    sliderDistortion->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 24);

    sliderReadGain1->setSkewFactor(4);
    sliderReadGain1->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 24);
    sliderReadGain1->setSliderStyle(juce::Slider::Rotary);

    sliderReadGain2->setSkewFactor(4);
    sliderReadGain2->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 24);
    sliderReadGain2->setSliderStyle(juce::Slider::Rotary);

    sliderReadGain3->setSkewFactor(4);
    sliderReadGain3->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 24);
    sliderReadGain3->setSliderStyle(juce::Slider::Rotary);

    sliderSpeed->setSliderStyle(juce::Slider::Rotary);
    sliderSpeed->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 24);
    sliderSpeed->setSkewFactorFromMidPoint(1/3.75);

    sliderReadPosition1->setSkewFactor(0.5);
    sliderReadPosition1->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    sliderReadPosition2->setSkewFactor(0.5);
    sliderReadPosition2->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    sliderReadPosition3->setSkewFactor(0.5);
    sliderReadPosition3->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);


    sliderWow->setSkewFactor(0.5);
    sliderWow->setSliderStyle(juce::Slider::Rotary );
    sliderWow->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 24);

    sliderFlutter->setSkewFactor(0.5);
    sliderFlutter->setSliderStyle(juce::Slider::Rotary );
    sliderFlutter->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 24);


    sliderLowCutoff->setSkewFactor(0.5);
    sliderHighCutoff->setSkewFactor(0.5);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TapeDelayAudioProcessorEditor::~TapeDelayAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent3 = nullptr;
    groupComponent2 = nullptr;
    groupComponent = nullptr;
    label2 = nullptr;
    sliderSpeed = nullptr;
    sliderReadPosition1 = nullptr;
    sliderReadPosition2 = nullptr;
    sliderReadPosition3 = nullptr;
    sliderReadGain1 = nullptr;
    sliderReadGain2 = nullptr;
    sliderReadGain3 = nullptr;
    sliderInputGain = nullptr;
    label3 = nullptr;
    sliderOutputGain = nullptr;
    label4 = nullptr;
    sliderFeedback = nullptr;
    label5 = nullptr;
    sliderDistortion = nullptr;
    label7 = nullptr;
    sliderFlutter = nullptr;
    label9 = nullptr;
    sliderWow = nullptr;
    label10 = nullptr;
    sliderLowCutoff = nullptr;
    label6 = nullptr;
    sliderHighCutoff = nullptr;
    label8 = nullptr;
    labelReadHead1 = nullptr;
    labelReadHead2 = nullptr;
    labelReadHead3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TapeDelayAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::chocolate);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TapeDelayAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent3->setBounds (98, 8, 288, 160);
    groupComponent2->setBounds (280, 168, 192, 128);
    groupComponent->setBounds (25, 168, 248, 128);
    label2->setBounds (114, 24, 150, 24);
    sliderSpeed->setBounds (114, 48, 88, 112);
    sliderReadPosition1->setBounds (36, 195, 160, 24);
    sliderReadPosition2->setBounds (36, 226, 160, 24);
    sliderReadPosition3->setBounds (36, 257, 160, 24);
    sliderReadGain1->setBounds (290, 184, 55, 104);
    sliderReadGain2->setBounds (350, 184, 55, 104);
    sliderReadGain3->setBounds (410, 184, 55, 104);
    sliderInputGain->setBounds (34, 32, 40, 128);
    label3->setBounds (393, 8, 72, 24);
    sliderOutputGain->setBounds (410, 32, 40, 128);
    label4->setBounds (18, 7, 72, 24);
    sliderFeedback->setBounds (29, 309, 56, 88);
    label5->setBounds (24, 290, 72, 24);
    sliderDistortion->setBounds (402, 310, 56, 88);
    label7->setBounds (394, 290, 72, 24);
    sliderFlutter->setBounds (250, 104, 112, 56);
    label9->setBounds (202, 120, 72, 24);
    sliderWow->setBounds (250, 32, 112, 56);
    label10->setBounds (210, 48, 72, 24);
    sliderLowCutoff->setBounds (168, 312, 208, 32);
    label6->setBounds (108, 314, 72, 24);
    sliderHighCutoff->setBounds (168, 344, 208, 32);
    label8->setBounds (103, 347, 72, 24);
    labelReadHead1->setBounds (201, 194, 70, 24);
    labelReadHead2->setBounds (201, 225, 70, 24);
    labelReadHead3->setBounds (201, 256, 70, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TapeDelayAudioProcessorEditor::timerCallback()
{
    float speed = *parentProcessor->pSpeed;
    juce::String  time1 = String(*parentProcessor->pReadPositions[0] * speed, 1);
    juce::String  time2 = String(*parentProcessor->pReadPositions[1] * speed, 1);
    juce::String  time3 = String(*parentProcessor->pReadPositions[2] * speed, 1);

    time1+= " ms";
    time2+= " ms";
    time3+= " ms";

    labelReadHead1->setText( time1, dontSendNotification);
    labelReadHead2->setText( time2, dontSendNotification);
    labelReadHead3->setText( time3, dontSendNotification);

}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TapeDelayAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="TapeDelayAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter), parentProcessor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffd2691e"/>
  <GROUPCOMPONENT name="new group" id="788fb0905a804243" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="98 8 288 160" title=""/>
  <GROUPCOMPONENT name="new group" id="81edee2e075ea980" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="280 168 192 128" title="Read Head Gains"/>
  <GROUPCOMPONENT name="new group" id="46429bb550406a98" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="25 168 248 128" title="Read Head Positions"/>
  <LABEL name="new label" id="d0f6c70f30ab4f86" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="114 24 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tape Speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Speed" id="b8a6cd9e43bd32aa" memberName="sliderSpeed" virtualName="ParameterSlider"
                    explicitFocusOrder="0" pos="114 48 88 112" class="Component"
                    params="*processor.getParameters()[kSpeed]"/>
  <GENERICCOMPONENT name="Read Head Position 1" id="588299d546d8baa7" memberName="sliderReadPosition1"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="36 195 160 24"
                    class="Component" params="*processor.getParameters()[kReadPosition1]"/>
  <GENERICCOMPONENT name="Read Head Position 2" id="d2d34473059c0cbd" memberName="sliderReadPosition2"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="36 226 160 24"
                    class="Component" params="*processor.getParameters()[kReadPosition2]"/>
  <GENERICCOMPONENT name="Read Head Position 3" id="36701f5399abe6c1" memberName="sliderReadPosition3"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="36 257 160 24"
                    class="Component" params="*processor.getParameters()[kReadPosition3]"/>
  <GENERICCOMPONENT name="Read Head Gain 1" id="f2bee4e05f5ba772" memberName="sliderReadGain1"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="290 184 55 104"
                    class="Component" params="*processor.getParameters()[kReadGain1]"/>
  <GENERICCOMPONENT name="Read Head Gain 2" id="1e3f8c27aaeee0" memberName="sliderReadGain2"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="350 184 55 104"
                    class="Component" params="*processor.getParameters()[kReadGain2]"/>
  <GENERICCOMPONENT name="Read Head Gain 3" id="563eb90a78e2393a" memberName="sliderReadGain3"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="410 184 55 104"
                    class="Component" params="*processor.getParameters()[kReadGain3]"/>
  <GENERICCOMPONENT name="Input Gain" id="391a936d0b3d9b7f" memberName="sliderInputGain"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="34 32 40 128"
                    class="Component" params="*processor.getParameters()[kInputGain]"/>
  <LABEL name="new label" id="a075a7b25fb52d37" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="393 8 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Output Gain" id="6c0f79ba621cee65" memberName="sliderOutputGain"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="410 32 40 128"
                    class="Component" params="*processor.getParameters()[kOutputGain]"/>
  <LABEL name="new label" id="63127774c1471aa7" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="18 7 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="4ade28566dfd337b" memberName="sliderFeedback"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="29 309 56 88"
                    class="Component" params="*processor.getParameters()[kFeedback]"/>
  <LABEL name="new label" id="7fd8294b15a91b94" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="24 290 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="e780d7eca0ed303e" memberName="sliderDistortion"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="402 310 56 88"
                    class="Component" params="*processor.getParameters()[kDistortion]"/>
  <LABEL name="new label" id="5d964e24bc68ede2" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="394 290 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Distortion" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="451bd2dca0632d03" memberName="sliderFlutter"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="250 104 112 56"
                    class="Component" params="*processor.getParameters()[kFlutter]"/>
  <LABEL name="new label" id="688963f2b3ecfe21" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="202 120 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Flutter" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="adfb10e87705823c" memberName="sliderWow"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="250 32 112 56"
                    class="Component" params="*processor.getParameters()[kWow]"/>
  <LABEL name="new label" id="1694e828ea29ab44" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="210 48 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Wow" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Low Cutoff" id="aeb356e4b9375930" memberName="sliderLowCutoff"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="168 312 208 32"
                    class="Component" params="*processor.getParameters()[kLowCutoff]"/>
  <LABEL name="new label" id="b1733136ed04b0b9" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="108 314 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Low Cut:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="High TCutoff" id="ea63aed4b1aba84a" memberName="sliderHighCutoff"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="168 344 208 32"
                    class="Component" params="*processor.getParameters()[kHighCutoff]"/>
  <LABEL name="new label" id="c5e5e3a4190177b" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="103 347 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="High Cut:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3af6bf37dbe38465" memberName="labelReadHead1"
         virtualName="" explicitFocusOrder="0" pos="201 194 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8d3211ad35ec6462" memberName="labelReadHead2"
         virtualName="" explicitFocusOrder="0" pos="201 225 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a45d4bfb7249f127" memberName="labelReadHead3"
         virtualName="" explicitFocusOrder="0" pos="201 256 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
