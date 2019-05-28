
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Envelope:
    public Component
{
    public:
        Envelope(JuceSynthFrameworkAudioProcessor&);
        ~Envelope();

        void paint (Graphics&) override;
        void resized() override;
    

    private:
        JuceSynthFrameworkAudioProcessor& processor;

        ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackVal;
        ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayVal;
        ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainVal;
        ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseVal;

        Slider attackSlider;
        Slider decaySlider;
        Slider sustainSlider;
        Slider releaseSlider;
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
