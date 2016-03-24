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

    addAndMakeVisible (toggleButton = new ToggleButton ("new toggle button"));
    toggleButton->setButtonText (TRANS("Emphasis on/off"));
    toggleButton->addListener (this);

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


    //[UserPreSize]
    
    sliderInputGain->setSliderStyle(juce::Slider::LinearVertical);
    sliderInputGain->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 24);
    
    sliderOutputGain->setSliderStyle(juce::Slider::LinearVertical);
    sliderOutputGain->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 24);
    
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
    toggleButton = nullptr;
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
    toggleButton->setBounds (24, 320, 150, 24);
    label2->setBounds (328, 136, 150, 24);
    sliderSpeed->setBounds (112, 136, 200, 24);
    sliderReadPosition1->setBounds (112, 179, 200, 24);
    sliderReadPosition2->setBounds (112, 202, 200, 24);
    sliderReadPosition3->setBounds (112, 225, 200, 24);
    sliderReadGain1->setBounds (328, 179, 120, 24);
    sliderReadGain2->setBounds (328, 202, 120, 24);
    sliderReadGain3->setBounds (328, 225, 120, 24);
    sliderInputGain->setBounds (32, 136, 32, 136);
    label3->setBounds (479, 104, 72, 24);
    sliderOutputGain->setBounds (496, 136, 32, 136);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TapeDelayAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleButton)
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
  <TOGGLEBUTTON name="new toggle button" id="978d986d74cd651a" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="24 320 150 24" buttonText="Emphasis on/off"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
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
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="328 179 120 24"
                    class="Component" params="*processor.getParameters()[kReadGain1]"/>
  <GENERICCOMPONENT name="Read Head Gain 2" id="1e3f8c27aaeee0" memberName="sliderReadGain2"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="328 202 120 24"
                    class="Component" params="*processor.getParameters()[kReadGain2]"/>
  <GENERICCOMPONENT name="Read Head Gain 3" id="563eb90a78e2393a" memberName="sliderReadGain3"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="328 225 120 24"
                    class="Component" params="*processor.getParameters()[kReadGain3]"/>
  <GENERICCOMPONENT name="Input Gain" id="391a936d0b3d9b7f" memberName="sliderInputGain"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="32 136 32 136"
                    class="Component" params="*processor.getParameters()[kInputGain]"/>
  <LABEL name="new label" id="a075a7b25fb52d37" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="479 104 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="Output Gain" id="6c0f79ba621cee65" memberName="sliderOutputGain"
                    virtualName="ParameterSlider" explicitFocusOrder="0" pos="496 136 32 136"
                    class="Component" params="*processor.getParameters()[kOutputGain]"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
