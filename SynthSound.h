
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class SynthSound:
    public SynthesiserSound
{
    public:
        // Returns true if this sound should be played when a given MIDI note is pressed.
        bool appliesToNote (int /*midiNoteNumber*/) override
        {
            return true;
        }

        // Returns true is the sound should be triggered by MIDI ecents on a given channel.
        bool appliesToChannel (int /*midiNoteNumber*/) override
        {
            return true;
        }
};
