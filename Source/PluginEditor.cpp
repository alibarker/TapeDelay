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

class TapeDelayAudioProcessorEditor::ParameterToggleButton   : public ToggleButton,
private Timer
{
public:
    ParameterToggleButton (AudioProcessorParameter& p)
    : ToggleButton (p.getName (256)), param (p)
    {
        setToggleState(true, dontSendNotification);
        startTimerHz (30);
        updateTogglePos();
        setClickingTogglesState(true);
    }

    void buttonStateChanged() override
    {
        param.setValueNotifyingHost ((float) Button::getToggleState());
    }

    void timerCallback() override       { updateTogglePos(); }

//    void startedDragging() override     { param.beginChangeGesture(); }
//    void stoppedDragging() override     { param.endChangeGesture();   }

//    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
//    String getTextFromValue (bool value) override         { return param.getText ((bool) value, 1024); }

    void updateTogglePos()
    {
        const bool newValue = param.getValue();

        if (newValue != ToggleButton::getToggleState() && ! isMouseButtonDown())
            ToggleButton::setToggleState(newValue, sendNotification);
    }

    AudioProcessorParameter& param;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterToggleButton)
};




//[/MiscUserDefs]

//==============================================================================
TapeDelayAudioProcessorEditor::TapeDelayAudioProcessorEditor (TapeDelayAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Input Gain")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Speed")));
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
                                           TRANS("Low Cut")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderHighCutoff = new ParameterSlider (*processor.getParameters()[kHighCutoff]));
    sliderHighCutoff->setName ("High TCutoff");

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("High Cut\n")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    sliderInputGain->setSliderStyle(juce::Slider::LinearVertical);
    sliderInputGain->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 24);
    sliderInputGain->setSkewFactor(4);

    sliderOutputGain->setSliderStyle(juce::Slider::LinearVertical);
    sliderOutputGain->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 24);
    sliderOutputGain->setSkewFactor(4);

    sliderFeedback->setSliderStyle(juce::Slider::Rotary );
    sliderFeedback->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 24);
    sliderFeedback->setSkewFactor(4);

    sliderDistortion->setSliderStyle(juce::Slider::Rotary);
    sliderDistortion->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 24);

    sliderReadGain1->setSkewFactor(4);
    sliderReadGain2->setSkewFactor(4);
    sliderReadGain3->setSkewFactor(4);

    sliderReadPosition1->setSkewFactor(0.25);
    sliderReadPosition2->setSkewFactor(0.25);
    sliderReadPosition3->setSkewFactor(0.25);

    sliderWow->setSkewFactor(0.5);
    sliderFlutter->setSkewFactor(0.5);

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

    label = nullptr;
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


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TapeDelayAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TapeDelayAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (15, 104, 72, 24);
    label2->setBounds (328, 136, 150, 24);
    sliderSpeed->setBounds (112, 136, 200, 24);
    sliderReadPosition1->setBounds (112, 179, 200, 24);
    sliderReadPosition2->setBounds (112, 202, 200, 24);
    sliderReadPosition3->setBounds (112, 225, 200, 24);
    sliderReadGain1->setBounds (328, 179, 180, 24);
    sliderReadGain2->setBounds (328, 202, 180, 24);
    sliderReadGain3->setBounds (328, 224, 180, 25);
    sliderInputGain->setBounds (32, 136, 40, 136);
    label3->setBounds (496, 104, 72, 24);
    sliderOutputGain->setBounds (512, 136, 40, 136);
    label4->setBounds (15, 104, 72, 24);
    sliderFeedback->setBounds (4, 312, 136, 56);
    label5->setBounds (32, 280, 72, 24);
    sliderDistortion->setBounds (432, 312, 136, 56);
    label7->setBounds (456, 280, 72, 24);
    sliderFlutter->setBounds (352, 48, 136, 56);
    label9->setBounds (376, 16, 72, 24);
    sliderWow->setBounds (216, 48, 136, 56);
    label10->setBounds (240, 16, 72, 24);
    sliderLowCutoff->setBounds (200, 312, 232, 32);
    label6->setBounds (144, 312, 72, 24);
    sliderHighCutoff->setBounds (200, 344, 232, 32);
    label8->setBounds (136, 345, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TapeDelayAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor"
                 constructorParams="TapeDelayAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="491a6e670b4b1660" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="15 104 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d0f6c70f30ab4f86" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="328 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Speed" id="b8a6cd9e43bd32aa" memberName="sliderSpeed" virtualName="ParameterSlider"
                    explicitFocusOrder="0" pos="112 136 200 24" class="Component"
                    params="*processor.getParameters()[kSpeed]"/>
  <GENERICCOMPONENT name="Read Head Position 1" id="588299d546d8baa7" memberName="sliderReadPosition1"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="112 179 200 24"
                    class="Component" params="*processor.getParameters()[kReadPosition1]"/>
  <GENERICCOMPONENT name="Read Head Position 2" id="d2d34473059c0cbd" memberName="sliderReadPosition2"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="112 202 200 24"
                    class="Component" params="*processor.getParameters()[kReadPosition2]"/>
  <GENERICCOMPONENT name="Read Head Position 3" id="36701f5399abe6c1" memberName="sliderReadPosition3"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="112 225 200 24"
                    class="Component" params="*processor.getParameters()[kReadPosition3]"/>
  <GENERICCOMPONENT name="Read Head Gain 1" id="f2bee4e05f5ba772" memberName="sliderReadGain1"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="328 179 180 24"
                    class="Component" params="*processor.getParameters()[kReadGain1]"/>
  <GENERICCOMPONENT name="Read Head Gain 2" id="1e3f8c27aaeee0" memberName="sliderReadGain2"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="328 202 180 24"
                    class="Component" params="*processor.getParameters()[kReadGain2]"/>
  <GENERICCOMPONENT name="Read Head Gain 3" id="563eb90a78e2393a" memberName="sliderReadGain3"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="328 224 180 25"
                    class="Component" params="*processor.getParameters()[kReadGain3]"/>
  <GENERICCOMPONENT name="Input Gain" id="391a936d0b3d9b7f" memberName="sliderInputGain"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="32 136 40 136"
                    class="Component" params="*processor.getParameters()[kInputGain]"/>
  <LABEL name="new label" id="a075a7b25fb52d37" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="496 104 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Output Gain" id="6c0f79ba621cee65" memberName="sliderOutputGain"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="512 136 40 136"
                    class="Component" params="*processor.getParameters()[kOutputGain]"/>
  <LABEL name="new label" id="63127774c1471aa7" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="15 104 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="4ade28566dfd337b" memberName="sliderFeedback"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="4 312 136 56"
                    class="Component" params="*processor.getParameters()[kFeedback]"/>
  <LABEL name="new label" id="7fd8294b15a91b94" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="32 280 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="e780d7eca0ed303e" memberName="sliderDistortion"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="432 312 136 56"
                    class="Component" params="*processor.getParameters()[kDistortion]"/>
  <LABEL name="new label" id="5d964e24bc68ede2" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="456 280 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Distortion" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="451bd2dca0632d03" memberName="sliderFlutter"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="352 48 136 56"
                    class="Component" params="*processor.getParameters()[kFlutter]"/>
  <LABEL name="new label" id="688963f2b3ecfe21" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="376 16 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Flutter" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Feedback" id="adfb10e87705823c" memberName="sliderWow"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="216 48 136 56"
                    class="Component" params="*processor.getParameters()[kWow]"/>
  <LABEL name="new label" id="1694e828ea29ab44" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="240 16 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Wow" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Low Cutoff" id="aeb356e4b9375930" memberName="sliderLowCutoff"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="200 312 232 32"
                    class="Component" params="*processor.getParameters()[kLowCutoff]"/>
  <LABEL name="new label" id="b1733136ed04b0b9" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="144 312 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Low Cut" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="High TCutoff" id="ea63aed4b1aba84a" memberName="sliderHighCutoff"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="200 344 232 32"
                    class="Component" params="*processor.getParameters()[kHighCutoff]"/>
  <LABEL name="new label" id="c5e5e3a4190177b" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="136 345 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="High Cut&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
