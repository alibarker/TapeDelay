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
//[/MiscUserDefs]

//==============================================================================
TapeDelayAudioProcessorEditor::TapeDelayAudioProcessorEditor (TapeDelayAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (gain = new Slider ("new slider"));
    gain->setRange (0, 1, 0);
    gain->setSliderStyle (Slider::LinearHorizontal);
    gain->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gain->addListener (this);
    gain->setSkewFactor (0.1);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Gain")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (toggleButton = new ToggleButton ("new toggle button"));
    toggleButton->setButtonText (TRANS("Emphasis on/off"));
    toggleButton->addListener (this);

    addAndMakeVisible (sliderSpeed = new Slider ("new slider"));
    sliderSpeed->setRange (0.1, 10, 0);
    sliderSpeed->setSliderStyle (Slider::LinearHorizontal);
    sliderSpeed->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderSpeed->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Speed")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TapeDelayAudioProcessorEditor::~TapeDelayAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gain = nullptr;
    label = nullptr;
    toggleButton = nullptr;
    sliderSpeed = nullptr;
    label2 = nullptr;


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

    gain->setBounds (32, 24, 150, 24);
    label->setBounds (192, 24, 150, 24);
    toggleButton->setBounds (32, 64, 150, 24);
    sliderSpeed->setBounds (56, 144, 198, 24);
    label2->setBounds (256, 144, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TapeDelayAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gain)
    {
        //[UserSliderCode_gain] -- add your slider handling code here..
        processor.setParameter(0, gain->getValue());
        //[/UserSliderCode_gain]
    }
    else if (sliderThatWasMoved == sliderSpeed)
    {
        //[UserSliderCode_sliderSpeed] -- add your slider handling code here..
        processor.setParameter(kSpeed, sliderSpeed->getValue());
        //[/UserSliderCode_sliderSpeed]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
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
  <SLIDER name="new slider" id="b7cd89715f76ddef" memberName="gain" virtualName=""
          explicitFocusOrder="0" pos="32 24 150 24" min="0" max="1" int="0"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.10000000000000000555"/>
  <LABEL name="new label" id="491a6e670b4b1660" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="192 24 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="978d986d74cd651a" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="32 64 150 24" buttonText="Emphasis on/off"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="new slider" id="efd08dd65e36581b" memberName="sliderSpeed"
          virtualName="" explicitFocusOrder="0" pos="56 144 198 24" min="0.10000000000000000555"
          max="10" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="d0f6c70f30ab4f86" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="256 144 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
