
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "Maximilian.h"


class SynthVoice:
    public SynthesiserVoice
{
public:
    // Must return true if this voice object is capable of playing the given sound.
    bool canPlaySound (SynthesiserSound* sound) override
    {
        // If the cast is successful, return true; otherwise false and no sound is played.
        return dynamic_cast <SynthSound*> (sound) != nullptr;
    }
    
    void getOscType (float* selection)
    {
        wave = *selection;
    }
    
    double setOscType ()
    {
        if (wave == 0)
            return osc1.sinewave (frequency);
        
        else if (wave == 1)
            return osc1.saw (frequency);
        
        else if (wave == 2)
            return osc1.square (frequency);
        
        else
            return osc1.sinewave (frequency);
    }
    
    //  Relays envelope parameters from value tree to synth voice.
    void getEnvelopeParams (float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack  (double (*attack));
        env1.setDecay   (double (*decay));
        env1.setSustain (double (*sustain));
        env1.setRelease (double (*release));
    }
    
    double setEnvelope()
    {
        return env1.adsr (setOscType(), env1.trigger);
    }
    
    //  Relays filter parameters from value tree to synth voice.
    void getFilterParams (float* filterType, float* filterCutoff, float* filterRes)
    {
        filterChoice = *filterType;
        cutoff       = *filterCutoff;
        resonance    = *filterRes;
    }
    
    double setFilter ()
    {
        if (filterChoice == 0)
            return filter1.lores (setEnvelope(), cutoff, resonance);
        
        else if (filterChoice == 1)
            return filter1.hires (setEnvelope(), cutoff, resonance);
        
        else if (filterChoice == 2)
            return filter1.bandpass(setEnvelope(), cutoff, resonance);
        
        else
            return filter1.lores (setEnvelope(), cutoff, resonance);
    }
    
    
    // Called to start a new note.
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        // Value to trigger envelope.
        env1.trigger = 1;
        frequency    = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level        = velocity;
    }
    
    // Called to stop a note. 
    void stopNote (float velocity, bool allowTailOff) override
    {
        // Value to release note.
        env1.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    // Called to let the voice know that the pitch wheel has been moved.
    void pitchWheelMoved (int newPitchWheelValue) override {}
    
    // Called to let the voice know that a MIDI controller has been moved.
    void controllerMoved (int controllerNumber, int newControllerValue) override {}
    
    // Renders the next block of data for the voice. 
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample (channel, startSample, setFilter() * 0.3f);
            }
            
            ++startSample;
        }
    }
    
    
private:
    double level;
    double frequency;
    int    wave;
    
    int   filterChoice;
    float cutoff;
    float resonance;
    
    // Maximilian classes.
    maxiOsc    osc1;
    maxiEnv    env1;
    maxiFilter filter1;
};
