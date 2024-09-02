#include "AudioProcessing.h"

#include "AudioProcessing.h"

namespace AudioProcessing
{
    void applyAdvancedSmoothing(juce::AudioBuffer<float>& buffer, int numSamples)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            auto* samples = buffer.getWritePointer(channel);
            for (int i = 1; i < numSamples - 1; ++i)
            {
                // Smoothing avanzato usando una media mobile
                samples[i] = (samples[i - 1] + samples[i] + samples[i + 1]) / 3.0f;
            }
        }
    }

    float getNextSineSample(double frequency, double sampleRate, double& currentAngle, double amplitude)
    {
        double angleDelta = (2.0 * juce::MathConstants<double>::pi * frequency) / sampleRate;
        float sample = static_cast<float>(std::sin(currentAngle) * amplitude);
        currentAngle += angleDelta;
        if (currentAngle >= 2.0 * juce::MathConstants<double>::pi)
            currentAngle -= 2.0 * juce::MathConstants<double>::pi;
        return sample;
    }

    // Implementa altre funzioni di elaborazione audio qui
}

