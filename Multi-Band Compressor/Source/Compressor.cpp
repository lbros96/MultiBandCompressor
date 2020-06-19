//Based on the compressor example plug-in by Reiss and McPherson

#include "Compressor.h"
#include <stdio.h>

void Compressor::updateParameters(float threshold, float ratio, float tauAttack, float tauRelease, float makeUpGain, float kneeWidth, float sampleRate)
{
    threshold_ = threshold;
    ratio_ = ratio;
    tauAttack_ = tauAttack;
    tauRelease_ = tauRelease;
    makeUpGain_ = makeUpGain;
    kneeWidth_ = kneeWidth;
    sampleRate_ = sampleRate;
}

void Compressor::prepareToPlay(double samplerate, int samplesPerBlock, int numInputChannels)
{
    sampleRate_ = samplerate;
    previousYLevel_ = 0;
}

void Compressor::processBlock(AudioSampleBuffer& buffer)
{
    int bufferSize = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels(); // number of channels
    int M = round(numChannels / 2); // number of stereo channels

    //Initialise a new buffer to hold the samples we are processing and clear it
    AudioSampleBuffer inputBuffer(1, bufferSize);
    inputBuffer.clear(0, 0, bufferSize);

    for (int m = 0; m < M; ++m) {

        //Store samples from both channels and mix them together into the input buffer so that we may process them
        inputBuffer.addFrom(m, 0, buffer, (m * 2), 0, bufferSize, 0.5);
        inputBuffer.addFrom(m, 0, buffer, (m * 2) + 1, 0, bufferSize, 0.5);

        //Calculate alphaAttack/Release according to the sample rate
        float alphaAttack = exp(-1 / (0.001 * sampleRate_ * tauAttack_));
        float alphaRelease = exp(-1 / (0.001 * sampleRate_ * tauRelease_));

        for (int i = 0; i < bufferSize; ++i) {

            //Level Detection step
            //If the level is too low, simply set the gain to -120db
            if(fabs(buffer.getWritePointer(m)[i]) < 0.000001){
                xGain_ = -120;
            }
            //Otherwise convert the level to decibels
            else {
                xGain_ = 20 * log10(fabs(buffer.getWritePointer(m)[i]));
            }

            //Gain Computer step incorporating knee width//

            //If above knee
            if (2 * (xGain_ - threshold_) >= kneeWidth_)
            {
                //Apply full compression
                yGain_ = threshold_ + (xGain_ - threshold_) / ratio_;
            }

            //If in knee
            else if (2 * fabs(xGain_ - threshold_) <= kneeWidth_)
            {
                //Apply compression scaled by knee width
                yGain_ = xGain_ + (1 / ratio_ - 1) * pow(xGain_ - threshold_ + kneeWidth_ / 2, 2) / (2 * kneeWidth_);
            }

            //If below knee
            else {
                //No compression applied
                yGain_ = xGain_;
            }

            //Calculate Input Level
            xLevel_ = xGain_ - yGain_;

            //Ballistics step
            if (xLevel_ > previousYLevel_) {
                yLevel_ = alphaAttack * previousYLevel_ + (1 - alphaAttack) * xLevel_;
            }
            else {
                yLevel_ = alphaRelease * previousYLevel_ + (1 - alphaRelease) * xLevel_;
            }

            //Control Calculation step
            //Calculate the control voltage and set the save the current output level as the previous output level for the next sample
            controlVoltage_ = pow(10, (makeUpGain_ - yLevel_) / 20);
            previousYLevel_ = yLevel_;

            //Apply control voltage to signal
            buffer.getWritePointer(m*2)[i] *= controlVoltage_;
            buffer.getWritePointer((m*2) + 1)[i] *= controlVoltage_;
        }

    }
}