#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MultibandCompressorAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Button::Listener
{
public:
    MultibandCompressorAudioProcessorEditor (MultibandCompressorAudioProcessor&);
    ~MultibandCompressorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultibandCompressorAudioProcessor& processor;

    //Compressor Slider

    ToggleButton buttonLowOnOff;
    Slider sliderLowRatio;
    Slider sliderLowThreshold;
    Slider sliderLowMakeUpGain;
    Slider sliderLowAttack;
    Slider sliderLowRelease;
    Slider sliderLowKneeWidth;
    
    ToggleButton buttonMidOnOff;
    Slider sliderMidRatio;
    Slider sliderMidThreshold;
    Slider sliderMidMakeUpGain;
    Slider sliderMidAttack;
    Slider sliderMidRelease;
    Slider sliderMidKneeWidth;

    ToggleButton buttonHighOnOff;
    Slider sliderHighRatio;
    Slider sliderHighThreshold;
    Slider sliderHighMakeUpGain;
    Slider sliderHighAttack;
    Slider sliderHighRelease;
    Slider sliderHighKneeWidth;

    Slider sliderLowerCutoff;
    Slider sliderHigherCutoff;

    Slider sliderDryWet;

    Label labelLowRatio;
    Label labelLowThreshold;
    Label labelLowMakeUpGain;
    Label labelLowAttack;
    Label labelLowRelease;
    Label labelLowKneeWidth;

    Label labelMidRatio;
    Label labelMidThreshold;
    Label labelMidMakeUpGain;
    Label labelMidAttack;
    Label labelMidRelease;
    Label labelMidKneeWidth;

    Label labelHighRatio;
    Label labelHighThreshold;
    Label labelHighMakeUpGain;
    Label labelHighAttack;
    Label labelHighRelease;
    Label labelHighKneeWidth;

    Label labelLowerCutoff;
    Label labelHigherCutoff;

    Label labelDryWet;


    void sliderValueChanged(Slider* sliderMoved) override;
    void buttonClicked(Button* clickedButton) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandCompressorAudioProcessorEditor)
};
