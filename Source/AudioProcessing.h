#pragma once

#include <JuceHeader.h>

namespace AudioProcessing
{
    void applyAdvancedSmoothing(juce::AudioBuffer<float>& buffer, int numSamples);
    float getNextSineSample(double frequency, double sampleRate, double& currentAngle, double amplitude);
    // Aggiungi altre dichiarazioni di funzioni di elaborazione audio qui
}
