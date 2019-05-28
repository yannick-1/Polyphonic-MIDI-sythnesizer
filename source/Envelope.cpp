
#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

Envelope::Envelope(JuceSynthFrameworkAudioProcessor& p):
    processor(p)
{
    setSize (200, 200);
    
    // Slider initialisation values.
    attackSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    attackSlider.setRange (0.1f, 5000);
    attackSlider.setValue (0.1f);
    attackSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 20, 10);
    addAndMakeVisible (&attackSlider);

    decaySlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    decaySlider.setRange (0.1f, 5000);
    decaySlider.setValue (0.1f);
    decaySlider.setTextBoxStyle (Slider::TextBoxBelow, true, 20, 10);
    addAndMakeVisible (&decaySlider);

    sustainSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange (0.1f, 5000);
    sustainSlider.setValue (0.1f);
    sustainSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 20, 10);
    addAndMakeVisible (&sustainSlider);

    releaseSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange (0.1f, 5000);
    releaseSlider.setValue (0.1f);
    releaseSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 20, 10);
    addAndMakeVisible (&releaseSlider);

    // Send the value of the sliders to the tree state in the processor.
    attackVal  = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    decayVal   = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    sustainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    releaseVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);

}

Envelope::~Envelope() {}

void Envelope::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour (Colours::white);
    g.drawText ("Envelope", titleArea, Justification::centred);
    
    g.drawText ("A", 53, 150, 20, 20, Justification::centred);
    g.drawText ("D", 77, 150, 20, 20, Justification::centred);
    g.drawText ("S", 103, 150, 20, 20, Justification::centred);
    g.drawText ("R", 128, 150, 20, 20, Justification::centred);

    Rectangle<float> area (25, 25, 150, 150);
    
    g.setColour (Colours::yellow);
    g.drawRoundedRectangle (area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth  = 25;
    int sliderHeight = 175;
    
    attackSlider.setBounds (area.removeFromLeft (sliderWidth)
                                 .removeFromTop (sliderHeight)
                                 .withTrimmedTop (10));
    decaySlider.setBounds (area.removeFromLeft (sliderWidth)
                                .removeFromTop (sliderHeight)
                                .withTrimmedTop (10));
    sustainSlider.setBounds (area.removeFromLeft (sliderWidth)
                                  .removeFromTop (sliderHeight)
                                  .withTrimmedTop (10));
    releaseSlider.setBounds (area.removeFromLeft (sliderWidth)
                                 .removeFromTop (sliderHeight)
                                 .withTrimmedTop (10));
}

