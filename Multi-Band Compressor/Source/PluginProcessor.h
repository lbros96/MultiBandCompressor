#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "C:\Users\Luke\Desktop\Sound + Music Computing\Digital Audio Effects\Labs\Multi-Band Compressor\Builds\VisualStudio2019\Compressor.h"

//==============================================================================
/**
*/
class MultibandCompressorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MultibandCompressorAudioProcessor();
    ~MultibandCompressorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //=============================================================================

    //Setter Methods
    void setLowOnOff(int buttonState) { lowOnOff  = buttonState;  }
    void setLowRatio(float Ratio) { lowRatio = Ratio; }
    void setLowMakeUpGain(float MakeUpGain) { lowMakeUpGain = MakeUpGain; }
    void setLowThreshold(float Threshold) { lowThreshold = Threshold; }
    void setLowAttack(float Attack) { lowTauAttack = Attack; }
    void setLowRelease(float Release) { lowTauRelease = Release; }
    void setLowKneeWidth(float KneeWidth) { lowKneeWidth = KneeWidth; }

    void setMidOnOff(int buttonState) { midOnOff = buttonState; }
    void setMidRatio(float Ratio) { midRatio = Ratio; }
    void setMidMakeUpGain(float MakeUpGain) { midMakeUpGain = MakeUpGain; }
    void setMidThreshold(float Threshold) { midThreshold = Threshold; }
    void setMidAttack(float Attack) { midTauAttack = Attack; }
    void setMidRelease(float Release) { midTauRelease = Release; }
    void setMidKneeWidth(float KneeWidth) { midKneeWidth = KneeWidth; }

    void setHighOnOff(int buttonState) { highOnOff = buttonState; }
    void setHighRatio(float Ratio) { highRatio = Ratio; }
    void setHighMakeUpGain(float MakeUpGain) { highMakeUpGain = MakeUpGain; }
    void setHighThreshold(float Threshold) { highThreshold = Threshold; }
    void setHighAttack(float Attack) { highTauAttack = Attack; }
    void setHighRelease(float Release) { highTauRelease = Release; }
    void setHighKneeWidth(float KneeWidth) { highKneeWidth = KneeWidth; }

    void setLowerCutoff(float Cutoff) { myLowerCutoff = Cutoff; }
    void setHigherCutoff(float Cutoff) { myHigherCutoff = Cutoff; }

    void setDryWet(float DryWet) { myDryWet = (float)sqrt(0.5F*(1.0F + DryWet)); }

    //Getter Methods
    bool getLowOnOff() { return lowOnOff;  }
    float getLowRatio() { return lowRatio; }
    float getLowMakeUpGain() { return lowMakeUpGain; }
    float getLowThreshold() { return lowThreshold; }
    float getLowAttack() { return lowTauAttack; }
    float getLowRelease() { return lowTauRelease; }
    float getLowKneeWidth() { return lowKneeWidth; }

    float getMidRatio() { return midRatio; }
    float getMidMakeUpGain() { return midMakeUpGain; }
    float getMidThreshold() { return midThreshold; }
    float getMidAttack() { return midTauAttack; }
    float getMidRelease() { return midTauRelease; }
    float getMidKneeWidth() { return midKneeWidth; }

    float getHighRatio() { return highRatio; }
    float getHighMakeUpGain() { return highMakeUpGain; }
    float getHighThreshold() { return highThreshold; }
    float getHighAttack() { return highTauAttack; }
    float getHighRelease() { return highTauRelease; }
    float getHighKneeWidth() { return highKneeWidth; }

    float getLowerCutoff() { return myLowerCutoff; }
    float getHigherCutoff() { return myHigherCutoff; }

    float getDryWet() { return myDryWet; }

private:
    //Compressor
    ScopedPointer<Compressor> lowCompressor;
    ScopedPointer<Compressor> midCompressor;
    ScopedPointer<Compressor> highCompressor;

    // Parameters
    int numChannels;
    float pOverallGain;
    float pKneeWidth;

    //Low band compressor values
    bool lowOnOff;
    float lowMakeUpGain;
    float lowThreshold;
    float lowRatio;
    float lowTauAttack;
    float lowTauRelease;
    float lowKneeWidth;

    // Mid band compressor values
    bool midOnOff;
    float midMakeUpGain;
    float midThreshold;
    float midRatio;
    float midTauAttack;
    float midTauRelease;
    float midKneeWidth;

    //High band compressor values
    bool highOnOff;
    float highMakeUpGain;
    float highThreshold;
    float highRatio;
    float highTauAttack;
    float highTauRelease;
    float highKneeWidth;


    // Cutoff Frequencies
    float myLowerCutoff;
    float myHigherCutoff;

    //Dry/Wet Mix
    float myDryWet;


    // Filter Definition
    IIRFilter lowBandFilterLeft1;
    IIRFilter lowBandFilterLeft2;
    IIRFilter lowBandFilterRight1;
    IIRFilter lowBandFilterRight2;

    IIRFilter midBandLowPassFilterLeft1;
    IIRFilter midBandLowPassFilterLeft2;
    IIRFilter midBandLowPassFilterRight1;
    IIRFilter midBandLowPassFilterRight2;
    
    IIRFilter midBandHighPassFilterLeft1;
    IIRFilter midBandHighPassFilterLeft2;
    IIRFilter midBandHighPassFilterRight1;
    IIRFilter midBandHighPassFilterRight2;

    IIRFilter highBandFilterLeft1;
    IIRFilter highBandFilterLeft2;
    IIRFilter highBandFilterRight1;
    IIRFilter highBandFilterRight2;

    IIRCoefficients coefficients;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandCompressorAudioProcessor)
};
