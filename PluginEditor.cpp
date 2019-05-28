
#include "PluginProcessor.h"
#include "PluginEditor.h"


JuceSynthFrameworkAudioProcessorEditor::JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor& p):
    AudioProcessorEditor (&p),
    processor (p),
    oscGui(p),
    envGui(p),
    filterGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.    
    setSize (600, 200);
    
    addAndMakeVisible (&oscGui);
    addAndMakeVisible (&envGui);
//    addAndMakeVisible(&filterGui);
}

JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor() {}

void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // Our component is opaque, so we must completely fill the background with a solid colour
    g.fillAll(Colours::black);
}

// This is generally where you'll want to lay out the positions of any
// subcomponents in your editor..
void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth  = 200;
    const int componentHeight = 200;
    
    oscGui.setBounds (area.removeFromLeft (componentWidth)
                          .removeFromTop (componentHeight));
    envGui.setBounds (area.removeFromLeft (componentWidth)
                          .removeFromTop (componentHeight));
    filterGui.setBounds (area.removeFromLeft(componentWidth)
                             .removeFromTop(componentHeight));
}
