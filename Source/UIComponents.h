#pragma once

#include <JuceHeader.h>

class UIComponents
{
public:
    UIComponents(juce::Component& parent);
    ~UIComponents();

    void resizedComponents(juce::Component& parent);

    juce::TextButton importButton;
    juce::TextButton exportButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    juce::TextButton toneGeneratorButton;
    juce::ComboBox waveTypeComboBox;
    juce::Slider volumeSlider;
    juce::Slider frequencySlider;
    juce::Slider amplitudeSlider;
};


