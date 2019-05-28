
#include "PluginProcessor.h"
#include "PluginEditor.h"


JuceSynthFrameworkAudioProcessor::JuceSynthFrameworkAudioProcessor():
#ifndef JucePlugin_PreferredChannelConfigurations
    AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    attackTime (0.1f),
    tree (*this, nullptr)

#endif
{
    // Need these normalisable range objects for the tree state.
    NormalisableRange<float> attackParam (0.1f, 5000.0f);
    NormalisableRange<float> sustainParam (0.1f, 2000.0f);
    NormalisableRange<float> decayParam (0.1f, 1);
    NormalisableRange<float> releaseParam (0.1f, 5000.0f);

    // These parameters make it possible to set/get states and automate parameters in your DAW.
    // Also connects values between the slider and the values here.
    tree.createAndAddParameter ("attack", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter ("sustain", "Sustain", "Sustain", sustainParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter ("decay", "Decay", "Decay", decayParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter ("release", "Release", "Release", releaseParam, 0.1f, nullptr, nullptr);
    
    NormalisableRange<float> wavetypeParam (0, 2);
    tree.createAndAddParameter ("wavetype", "Wavetype", "wavetype", wavetypeParam, 0, nullptr, nullptr);
    
    NormalisableRange<float> filterTypeVal (0, 2);
    NormalisableRange<float> filterParam (20.0f, 10000.0f);
    NormalisableRange<float> resParam (1, 5);

    tree.createAndAddParameter ("filterType", "FilterType", "filterType", filterTypeVal, 0, nullptr, nullptr);
    tree.createAndAddParameter ("filterCutoff", "FilterCutoff", "filterCutoff", filterParam, 400.0f, nullptr, nullptr);
    tree.createAndAddParameter ("filterRes", "FilterRes", "filterRes", resParam, 1, nullptr, nullptr);

    // Parameters need to be added before tree is initialised.
    tree.state = ValueTree("beef");
    
    // housekeeping
    mySynth.clearVoices();
    
    // Number of synth voices.
    int numVoices = 5;

    for (int i = 0; i < numVoices; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

JuceSynthFrameworkAudioProcessor::~JuceSynthFrameworkAudioProcessor() {}


const String JuceSynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceSynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceSynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceSynthFrameworkAudioProcessor::getNumPrograms()
{
    // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
    return 1;
}

int JuceSynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceSynthFrameworkAudioProcessor::setCurrentProgram (int index) {}

const String JuceSynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceSynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName) {}


void JuceSynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Clears unused samples from last key pressed.
    ignoreUnused(samplesPerBlock);
    
    // Storing sample rate in case it changes during playback.
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
//    dsp::ProcessSpec spec;
//    spec.sampleRate = lastSampleRate;
//    spec.maximumBlockSize = samplesPerBlock;
//    spec.numChannels = getTotalNumOutputChannels();
//    
//    stateVariableFilter.reset();
//    stateVariableFilter.prepare(spec);
//    updateFilter();
}

void JuceSynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceSynthFrameworkAudioProcessor::updateFilter()
{
//    int menuChoice = *tree.getRawParameterValue("filterType");
//    int freq = *tree.getRawParameterValue("filterCutoff");
//    int res = *tree.getRawParameterValue("filterRes");
//
//    if (menuChoice == 0)
//    {
//        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
//        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
//    }
//
//    if (menuChoice == 1)
//    {
//        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
//        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
//    }
//
//    if (menuChoice == 2)
//    {
//        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
//        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
//    }
}

void JuceSynthFrameworkAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    //const int totalNumInputChannels  = getTotalNumInputChannels();
    //const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        // If voice dynamically casts successfully as SynthVoice, then relay voice information.
        if ((myVoice = dynamic_cast<SynthVoice*> (mySynth.getVoice(i)) ))
        {
            myVoice->getEnvelopeParams (tree.getRawParameterValue("attack"),
                                        tree.getRawParameterValue("decay"),
                                        tree.getRawParameterValue("sustain"),
                                        tree.getRawParameterValue("release"));
            
            myVoice->getOscType (tree.getRawParameterValue("wavetype"));
            
            myVoice->getFilterParams (tree.getRawParameterValue("filterType"),
                                      tree.getRawParameterValue("filterCutoff"),
                                      tree.getRawParameterValue("filterRes"));
        }

    }
    
    // housekeeeping...
    buffer.clear();
    mySynth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
    
//    updateFilter();
//    dsp::AudioBlock<float> block (buffer);
//    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (block));
}

bool JuceSynthFrameworkAudioProcessor::hasEditor() const
{
    // (change this to false if you choose to not supply an editor)
    return true;
}

AudioProcessorEditor* JuceSynthFrameworkAudioProcessor::createEditor()
{
    return new JuceSynthFrameworkAudioProcessorEditor (*this);
}

void JuceSynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthFrameworkAudioProcessor();
}
