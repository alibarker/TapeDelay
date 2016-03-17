/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

enum Parameters {
    kGain = 0,
    kEmphasisOn,
    kFeedback,
    kSpeed,
    kNumParameters
};


//==============================================================================
TapeDelayAudioProcessor::TapeDelayAudioProcessor()
{
    // Add parameters in order of enum
    addParameter(new AudioParameterFloat("1", "Gain", 0, 1, 1));
    addParameter(new AudioParameterBool("1", "Emphasis On", 1));
    addParameter(new AudioParameterFloat("1", "Feedback", 0, 1, 0.25));
    addParameter(new AudioParameterFloat("1", "Speed", 0.1, 10, 1));

    
    // Setup Delayline
    tape = new VariableDelayLine(1);
    
}

TapeDelayAudioProcessor::~TapeDelayAudioProcessor()
{
}

//==============================================================================
const String TapeDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TapeDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TapeDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TapeDelayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double TapeDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TapeDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TapeDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TapeDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String TapeDelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void TapeDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TapeDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    int numChannels = getTotalNumInputChannels();
    
    for (int i = 0; i < numChannels; i++)
    {
        highpass.add(new IIRFilter);
        highpass[i]->setCoefficients(IIRCoefficients::makeHighPass(getSampleRate(), 100));
    }
    
}

void TapeDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void TapeDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    
    AudioSampleBuffer tapeOutput;
    AudioSampleBuffer tapeInput;
    
    tapeOutput.setSize(1, numSamples);
    tapeInput.setSize(1, numSamples);
    
    tapeInput.clear();
    tapeOutput.clear();
    
    float feedback = getParameters()[kFeedback]->getValue();
    float inputGain = getParameters()[kGain]->getValue();
    
    // Mono sum
    for (int channel = 0; channel < numChannels; ++channel)
    {
        tapeInput.addFrom(0, 0, buffer, channel, 0, numSamples);
    }
        
        tape->readSamples(0, tapeOutput);
    

        tapeInput.addFrom(0, 0, tapeOutput, 0, 0, numSamples, feedback);
    
//    for (int n = 0; n < numSamples; n++)
//    {
    
//        dist.setGain(1);
    
//        float input = tapeInput.getSample(0, n);
//        float output = highpass[0]->processSingleSampleRaw(dist.processSample(input));
        
//        tapeInput.setSample(0, n, output);
//    }
    
    tape->writeSamples(tapeInput);
    
    buffer.clear();
    
    
    for (int i = 0; i < numChannels; i++)
    {
        buffer.addFrom(i, 0, tapeOutput, 0, 0, numSamples);
    }
}

//==============================================================================
bool TapeDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TapeDelayAudioProcessor::createEditor()
{
    return new TapeDelayAudioProcessorEditor (this);
}

//==============================================================================
void TapeDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TapeDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TapeDelayAudioProcessor();
}