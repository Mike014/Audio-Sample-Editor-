#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class SineWaveOscillator
{
public:
    SineWaveOscillator();
    ~SineWaveOscillator();

    void setSampleRate(double sampleRate);
    void setFrequency(double newFrequency);
    void setAmplitude(double newAmplitude);
    float getNextSample();
    double getSampleRate() const;

private:
    void updateAngleDelta();

    double currentSampleRate;
    double currentAngle;
    double angleDelta;
    double frequency;
    double amplitude;
};

