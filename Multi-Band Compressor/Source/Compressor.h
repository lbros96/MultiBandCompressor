#pragma once
#ifndef Compressor_h
#define Compressor_h
#include "../JuceLibraryCode/JuceHeader.h"

class Compressor
{
public:
    Compressor() {}
    ~Compressor() {}

    void updateParameters(float threshold, float ratio, float tauAttack, float tauRelease, float makeUpGain, float kneeWidth, float sampleRate);
    void prepareToPlay(double samplerate, int samplesPerBlock, int numInputChannels);
    void processBlock(AudioSampleBuffer& buffer);

private:

    // On/Off
    int state_ = 1;

    // Compressor Parameters
    float threshold_;
    float ratio_;  
    float tauAttack_;
    float tauRelease_;
    float makeUpGain_;
    float kneeWidth_;
    float sampleRate_;

    // Gain and Levels
    //HeapBlock <float> xGain_, xLevel_, yGain_, yLevel_, controlVoltage_;// input, output, control

    float xGain_;
    float xLevel_;
    float yGain_;
    float yLevel_;
    float previousYLevel_;
    float controlVoltage_;

};

#endif /* Compressor_h */

