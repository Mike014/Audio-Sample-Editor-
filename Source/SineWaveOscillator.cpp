#include "SineWaveOscillator.h"

SineWaveOscillator::SineWaveOscillator()
    : currentSampleRate(48000.0), currentAngle(0.0), angleDelta(0.0), frequency(440.0), amplitude(0.5) {}

SineWaveOscillator::~SineWaveOscillator() {}

void SineWaveOscillator::setSampleRate(double sampleRate)
{
    currentSampleRate = sampleRate;
    updateAngleDelta();
}

void SineWaveOscillator::setFrequency(double newFrequency)
{
    frequency = newFrequency;
    updateAngleDelta();
}

void SineWaveOscillator::setAmplitude(double newAmplitude)
{
    amplitude = newAmplitude;
}

float SineWaveOscillator::getNextSample()
{
    const float sample = static_cast<float>(amplitude * std::sin(currentAngle));
    currentAngle += angleDelta;
    if (currentAngle >= 2.0 * M_PI)
        currentAngle -= 2.0 * M_PI;
    return sample;
}

void SineWaveOscillator::updateAngleDelta()
{
    if (currentSampleRate > 0)
    {
        // Assicurati che la frequenza non superi la frequenza di Nyquist
        if (frequency > currentSampleRate / 2.0)
        {
            frequency = currentSampleRate / 2.0;
        }
        angleDelta = (2.0 * M_PI * frequency) / currentSampleRate;
    }
}

double SineWaveOscillator::getSampleRate() const
{
	return currentSampleRate;
}






