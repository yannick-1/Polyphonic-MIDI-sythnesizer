
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class Filter:
    public Component
{
public:
    Filter(JuceSynthFrameworkAudioProcessor& p);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JuceSynthFrameworkAudioProcessor& processor;
    
    ComboBox filterMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>   filterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>   resVal;
    
    Slider filterCutoff;
    Slider filterResonance;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
