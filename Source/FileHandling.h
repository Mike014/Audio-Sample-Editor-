#pragma once

#include <JuceHeader.h>

namespace FileHandling
{
    void loadFile(const juce::File& file, juce::AudioFormatManager& formatManager, std::unique_ptr<juce::AudioFormatReaderSource>& readerSource, juce::AudioTransportSource& transportSource, juce::AudioThumbnail& thumbnail);
    void saveFile(const juce::File& file, juce::AudioFormatReader* reader, juce::Slider& volumeSlider);
}
