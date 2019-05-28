
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Oscillator:
    public Component,
    private ComboBox::Listener
{
    public:
        Oscillator(JuceSynthFrameworkAudioProcessor&);
        ~Oscillator();

        void paint (Graphics&) override;
        void resized() override;
    
        void comboBoxChanged (ComboBox*) override;

    private:
        // This reference is provided as a quick way for your editor to
        // access the processor object that created it.
        JuceSynthFrameworkAudioProcessor& processor;
    
        ComboBox oscMenu;
    
        ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
