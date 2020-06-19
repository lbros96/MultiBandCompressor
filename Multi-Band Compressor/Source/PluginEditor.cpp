#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandCompressorAudioProcessorEditor::MultibandCompressorAudioProcessorEditor (MultibandCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 600);

    int ratioDefault = 1;
    int ratioMinimum = 1;
    int ratioMaximum = 70;

    float thresholdDefault = 0;
    float thresholdMinimum = -70;
    float thresholdMaximum = 0;

    float attackDefault = 20;
    float attackMinimum = 20;
    float attackMaximum = 1000;

    float releaseDefault = 50;
    float releaseMinimum = 5;
    float releaseMaximum = 5000;

    float makeUpGainDefault = 0.0;
    float makeUpGainMinimum = -10.0;
    float makeUpGainMaximum = 10.0;
    
    float kneeWidthDefault = 6;
    float kneeWidthMinimum = 0;
    float kneeWidthMaximum = 18;

    float lowerCutoffMax = 700;
    float higherCutoffMin = 1000;
    
    ////////LOW COMPRESSOR PARAMETERS///////////
    //On/Off Button
    addAndMakeVisible(&buttonLowOnOff);
    buttonLowOnOff.setButtonText(TRANS("Low Compression"));
    buttonLowOnOff.setToggleState(1, false);
    (buttonLowOnOff).addListener(this);

    //Parameters of the Slider
    sliderLowRatio.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderLowRatio.setRange(ratioMinimum, ratioMaximum, 1);
    sliderLowRatio.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderLowRatio.setPopupDisplayEnabled(true, this, nullptr);
    sliderLowRatio.setTextValueSuffix(":1");
    sliderLowRatio.setValue(ratioDefault);
    addAndMakeVisible(&sliderLowRatio);
    sliderLowRatio.addListener(this);

    addAndMakeVisible(labelLowRatio);
    labelLowRatio.setText("Ratio", dontSendNotification);
    labelLowRatio.attachToComponent(&sliderLowRatio, false);
    labelLowRatio.setColour(Label::textColourId, Colours::white);
    labelLowRatio.setJustificationType(Justification::centredTop);
    
    

    //Parameters of the Slider
    sliderLowThreshold.setSliderStyle(Slider::LinearVertical);
    sliderLowThreshold.setRange(thresholdMinimum, thresholdMaximum, 1);
    sliderLowThreshold.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderLowThreshold.setPopupDisplayEnabled(true, this, nullptr);
    sliderLowThreshold.setTextValueSuffix("dB");
    sliderLowThreshold.setValue(thresholdDefault);
    addAndMakeVisible(&sliderLowThreshold);
    sliderLowThreshold.addListener(this);

    addAndMakeVisible(labelLowThreshold);
    labelLowThreshold.setText("Threshold", dontSendNotification);
    labelLowThreshold.attachToComponent(&sliderLowThreshold, false);
    labelLowThreshold.setColour(Label::textColourId, Colours::white);
    labelLowThreshold.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderLowMakeUpGain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderLowMakeUpGain.setRange(makeUpGainMinimum, makeUpGainMaximum, 0.1);
    sliderLowMakeUpGain.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderLowMakeUpGain.setPopupDisplayEnabled(true, this, nullptr);
    sliderLowMakeUpGain.setTextValueSuffix("dB");
    sliderLowMakeUpGain.setValue(makeUpGainDefault);
    addAndMakeVisible(&sliderLowMakeUpGain);
    sliderLowMakeUpGain.addListener(this);

    addAndMakeVisible(labelLowMakeUpGain);
    labelLowMakeUpGain.setText("MakeUp Gain", dontSendNotification);
    labelLowMakeUpGain.attachToComponent(&sliderLowMakeUpGain, false);
    labelLowMakeUpGain.setColour(Label::textColourId, Colours::white);
    labelLowMakeUpGain.setJustificationType(Justification::centredTop);
    

    //Parameters of the Slider
    sliderLowAttack.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderLowAttack.setRange(attackMinimum, attackMaximum, 1);
    sliderLowAttack.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderLowAttack.setPopupDisplayEnabled(true, this, nullptr);
    sliderLowAttack.setTextValueSuffix("ms");
    sliderLowAttack.setValue(attackDefault);
    addAndMakeVisible(&sliderLowAttack);
    sliderLowAttack.addListener(this);

    addAndMakeVisible(labelLowAttack);
    labelLowAttack.setText("Attack", dontSendNotification);
    labelLowAttack.attachToComponent(&sliderLowAttack, false);
    labelLowAttack.setColour(Label::textColourId, Colours::white);
    labelLowAttack.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderLowRelease.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderLowRelease.setRange(releaseMinimum, releaseMaximum, 1);
    sliderLowRelease.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderLowRelease.setPopupDisplayEnabled(true, this, nullptr);
    sliderLowRelease.setTextValueSuffix("ms");
    sliderLowRelease.setValue(releaseDefault);
    addAndMakeVisible(&sliderLowRelease);
    sliderLowRelease.addListener(this);

    addAndMakeVisible(labelLowRelease);
    labelLowRelease.setText("Release", dontSendNotification);
    labelLowRelease.attachToComponent(&sliderLowRelease, false);
    labelLowRelease.setColour(Label::textColourId, Colours::white);
    labelLowRelease.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderLowKneeWidth.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderLowKneeWidth.setRange(kneeWidthMinimum, kneeWidthMaximum, 0.1);
    sliderLowKneeWidth.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderLowKneeWidth.setPopupDisplayEnabled(true, this, nullptr);
    sliderLowKneeWidth.setTextValueSuffix("dB");
    sliderLowKneeWidth.setValue(kneeWidthDefault);
    sliderLowKneeWidth.setSkewFactorFromMidPoint(6);
    addAndMakeVisible(&sliderLowKneeWidth);
    sliderLowKneeWidth.addListener(this);

    addAndMakeVisible(labelLowKneeWidth);
    labelLowKneeWidth.setText("Knee Width", dontSendNotification);
    labelLowKneeWidth.attachToComponent(&sliderLowKneeWidth, false);
    labelLowKneeWidth.setColour(Label::textColourId, Colours::white);
    labelLowKneeWidth.setJustificationType(Justification::centredTop);
    


    ///////MID COMPRESSOR  PARAMETERS/////////////
    //On/Off Button
    addAndMakeVisible(&buttonMidOnOff);
    buttonMidOnOff.setButtonText(TRANS("Mid Compression"));
    buttonMidOnOff.setToggleState(1, false);
    buttonMidOnOff.addListener(this);

    //Parameters of the Slider
    sliderMidRatio.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderMidRatio.setRange(ratioMinimum, ratioMaximum, 1);
    sliderMidRatio.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderMidRatio.setPopupDisplayEnabled(true, this, nullptr);
    sliderMidRatio.setTextValueSuffix(":1");
    sliderMidRatio.setValue(ratioDefault);
    addAndMakeVisible(&sliderMidRatio);
    sliderMidRatio.addListener(this);

    addAndMakeVisible(labelMidRatio);
    labelMidRatio.setText("Ratio", dontSendNotification);
    labelMidRatio.attachToComponent(&sliderMidRatio, false);
    labelMidRatio.setColour(Label::textColourId, Colours::white);
    labelMidRatio.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderMidThreshold.setSliderStyle(Slider::LinearVertical);
    sliderMidThreshold.setRange(thresholdMinimum, thresholdMaximum, 1);
    sliderMidThreshold.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderMidThreshold.setPopupDisplayEnabled(true, this, nullptr);
    sliderMidThreshold.setTextValueSuffix("dB");
    sliderMidThreshold.setValue(thresholdDefault);
    addAndMakeVisible(&sliderMidThreshold);
    sliderMidThreshold.addListener(this);

    addAndMakeVisible(labelMidThreshold);
    labelMidThreshold.setText("Threshold", dontSendNotification);
    labelMidThreshold.attachToComponent(&sliderMidThreshold, false);
    labelMidThreshold.setColour(Label::textColourId, Colours::white);
    labelMidThreshold.setJustificationType(Justification::centredTop);

    //Parameters of the Slider
    sliderMidMakeUpGain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderMidMakeUpGain.setRange(makeUpGainMinimum, makeUpGainMaximum, 0.1);
    sliderMidMakeUpGain.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderMidMakeUpGain.setPopupDisplayEnabled(true, this, nullptr);
    sliderMidMakeUpGain.setTextValueSuffix("dB");
    sliderMidMakeUpGain.setValue(makeUpGainDefault);
    addAndMakeVisible(&sliderMidMakeUpGain);
    sliderMidMakeUpGain.addListener(this);

    addAndMakeVisible(labelMidMakeUpGain);
    labelMidMakeUpGain.setText("MakeUp Gain", dontSendNotification);
    labelMidMakeUpGain.attachToComponent(&sliderMidMakeUpGain, false);
    labelMidMakeUpGain.setColour(Label::textColourId, Colours::white);
    labelMidMakeUpGain.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderMidAttack.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderMidAttack.setRange(attackMinimum, attackMaximum, 1);
    sliderMidAttack.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderMidAttack.setPopupDisplayEnabled(true, this, nullptr);
    sliderMidAttack.setTextValueSuffix("ms");
    sliderMidAttack.setValue(attackDefault);
    addAndMakeVisible(&sliderMidAttack);
    sliderMidAttack.addListener(this);

    addAndMakeVisible(labelMidAttack);
    labelMidAttack.setText("Attack", dontSendNotification);
    labelMidAttack.attachToComponent(&sliderMidAttack, false);
    labelMidAttack.setColour(Label::textColourId, Colours::white);
    labelMidAttack.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderMidRelease.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderMidRelease.setRange(releaseMinimum, releaseMaximum, 1);
    sliderMidRelease.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderMidRelease.setPopupDisplayEnabled(true, this, nullptr);
    sliderMidRelease.setTextValueSuffix("ms");
    sliderMidRelease.setValue(releaseDefault);
    addAndMakeVisible(&sliderMidRelease);
    sliderMidRelease.addListener(this);

    addAndMakeVisible(labelMidRelease);
    labelMidRelease.setText("Release", dontSendNotification);
    labelMidRelease.attachToComponent(&sliderMidRelease, false);
    labelMidRelease.setColour(Label::textColourId, Colours::white);
    labelMidRelease.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderMidKneeWidth.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderMidKneeWidth.setRange(kneeWidthMinimum, kneeWidthMaximum, 0.1);
    sliderMidKneeWidth.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderMidKneeWidth.setPopupDisplayEnabled(true, this, nullptr);
    sliderMidKneeWidth.setTextValueSuffix("dB");
    sliderMidKneeWidth.setValue(kneeWidthDefault);
    sliderMidKneeWidth.setSkewFactorFromMidPoint(6);
    addAndMakeVisible(&sliderMidKneeWidth);
    sliderMidKneeWidth.addListener(this);

    addAndMakeVisible(labelMidKneeWidth);
    labelMidKneeWidth.setText("Knee Width", dontSendNotification);
    labelMidKneeWidth.attachToComponent(&sliderMidKneeWidth, false);
    labelMidKneeWidth.setColour(Label::textColourId, Colours::white);
    labelMidKneeWidth.setJustificationType(Justification::centredTop);




    ////////HIGH COMPRESSOR  PARAMETERS///////////
    //On/Off Button
    addAndMakeVisible(&buttonHighOnOff);
    buttonHighOnOff.setButtonText(TRANS("High Compression"));
    buttonHighOnOff.setToggleState(1, false);
    buttonHighOnOff.addListener(this);

    //Parameters of the Slider
    sliderHighRatio.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderHighRatio.setRange(ratioMinimum, ratioMaximum, 1);
    sliderHighRatio.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderHighRatio.setPopupDisplayEnabled(true, this, nullptr);
    sliderHighRatio.setTextValueSuffix(":1");
    sliderHighRatio.setValue(ratioDefault);
    addAndMakeVisible(&sliderHighRatio);
    sliderHighRatio.addListener(this);

    addAndMakeVisible(labelHighRatio);
    labelHighRatio.setText("Ratio", dontSendNotification);
    labelHighRatio.attachToComponent(&sliderHighRatio, false);
    labelHighRatio.setColour(Label::textColourId, Colours::white);
    labelHighRatio.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderHighThreshold.setSliderStyle(Slider::LinearVertical);
    sliderHighThreshold.setRange(thresholdMinimum, thresholdMaximum, 1);
    sliderHighThreshold.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderHighThreshold.setPopupDisplayEnabled(true, this, nullptr);
    sliderHighThreshold.setTextValueSuffix("dB");
    sliderHighThreshold.setValue(thresholdDefault);
    addAndMakeVisible(&sliderHighThreshold);
    sliderHighThreshold.addListener(this);

    addAndMakeVisible(labelHighThreshold);
    labelHighThreshold.setText("Threshold", dontSendNotification);
    labelHighThreshold.attachToComponent(&sliderHighThreshold, false);
    labelHighThreshold.setColour(Label::textColourId, Colours::white);
    labelHighThreshold.setJustificationType(Justification::centredTop);



    //Parameters of the Slider
    sliderHighMakeUpGain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderHighMakeUpGain.setRange(makeUpGainMinimum, makeUpGainMaximum, 0.1);
    sliderHighMakeUpGain.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderHighMakeUpGain.setPopupDisplayEnabled(true, this, nullptr);
    sliderHighMakeUpGain.setTextValueSuffix("dB");
    sliderHighMakeUpGain.setValue(makeUpGainDefault);
    addAndMakeVisible(&sliderHighMakeUpGain);
    sliderHighMakeUpGain.addListener(this);

    addAndMakeVisible(labelHighMakeUpGain);
    labelHighMakeUpGain.setText("MakeUp Gain", dontSendNotification);
    labelHighMakeUpGain.attachToComponent(&sliderHighMakeUpGain, false);
    labelHighMakeUpGain.setColour(Label::textColourId, Colours::white);
    labelHighMakeUpGain.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderHighAttack.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderHighAttack.setRange(attackMinimum, attackMaximum, 1);
    sliderHighAttack.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderHighAttack.setPopupDisplayEnabled(true, this, nullptr);
    sliderHighAttack.setTextValueSuffix("ms");
    sliderHighAttack.setValue(attackDefault);
    addAndMakeVisible(&sliderHighAttack);
    sliderHighAttack.addListener(this);

    addAndMakeVisible(labelHighAttack);
    labelHighAttack.setText("Attack", dontSendNotification);
    labelHighAttack.attachToComponent(&sliderHighAttack, false);
    labelHighAttack.setColour(Label::textColourId, Colours::white);
    labelHighAttack.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderHighRelease.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderHighRelease.setRange(releaseMinimum, releaseMaximum, 1);
    sliderHighRelease.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderHighRelease.setPopupDisplayEnabled(true, this, nullptr);
    sliderHighRelease.setTextValueSuffix("ms");
    sliderHighRelease.setValue(releaseDefault);
    addAndMakeVisible(&sliderHighRelease);
    sliderHighRelease.addListener(this);

    addAndMakeVisible(labelHighRelease);
    labelHighRelease.setText("Release", dontSendNotification);
    labelHighRelease.attachToComponent(&sliderHighRelease, false);
    labelHighRelease.setColour(Label::textColourId, Colours::white);
    labelHighRelease.setJustificationType(Justification::centredTop);


    //Parameters of the Slider
    sliderHighKneeWidth.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderHighKneeWidth.setRange(kneeWidthMinimum, kneeWidthMaximum, 0.1);
    sliderHighKneeWidth.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderHighKneeWidth.setPopupDisplayEnabled(true, this, nullptr);
    sliderHighKneeWidth.setTextValueSuffix("dB");
    sliderHighKneeWidth.setValue(kneeWidthDefault);
    sliderHighKneeWidth.setSkewFactorFromMidPoint(6);
    addAndMakeVisible(&sliderHighKneeWidth);
    sliderHighKneeWidth.addListener(this);

    addAndMakeVisible(labelHighKneeWidth);
    labelHighKneeWidth.setText("Knee Width", dontSendNotification);
    labelHighKneeWidth.attachToComponent(&sliderHighKneeWidth, false);
    labelHighKneeWidth.setColour(Label::textColourId, Colours::white);
    labelHighKneeWidth.setJustificationType(Justification::centredTop);


    //FREQUENCY CUTOFF SLIDERS//
    sliderLowerCutoff.setSliderStyle(Slider::RotaryHorizontalDrag);
    sliderLowerCutoff.setRange(5, lowerCutoffMax, 1);
    sliderLowerCutoff.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderLowerCutoff.setPopupDisplayEnabled(true, this, nullptr);
    sliderLowerCutoff.setTextValueSuffix("Hz");
    sliderLowerCutoff.setValue(500);   
    addAndMakeVisible(&sliderLowerCutoff);
    sliderLowerCutoff.addListener(this);

    addAndMakeVisible(labelLowerCutoff);
    labelLowerCutoff.setText("Low/Mid Cutoff", dontSendNotification);
    labelLowerCutoff.attachToComponent(&sliderLowerCutoff, false);
    labelLowerCutoff.setColour(Label::textColourId, Colours::white);
    labelLowerCutoff.setJustificationType(Justification::centredTop);


    sliderHigherCutoff.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderHigherCutoff.setRange(higherCutoffMin, 10000, 1);
    sliderHigherCutoff.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    sliderHigherCutoff.setPopupDisplayEnabled(true, this, nullptr);
    sliderHigherCutoff.setTextValueSuffix("Hz");
    sliderHigherCutoff.setValue(3000);
    addAndMakeVisible(&sliderHigherCutoff);
    sliderHigherCutoff.addListener(this);

    addAndMakeVisible(labelHigherCutoff);
    labelHigherCutoff.setText("Mid/High Cutoff", dontSendNotification);
    labelHigherCutoff.attachToComponent(&sliderHigherCutoff, false);
    labelHigherCutoff.setColour(Label::textColourId, Colours::white);
    labelHigherCutoff.setJustificationType(Justification::centredTop);


    //DRY WET MIX SLIDER
    sliderDryWet.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sliderDryWet.setRange(-1, 1, 0.01);
    sliderDryWet.setTextBoxStyle(Slider::TextBoxBelow, true, 1, 1);
    sliderDryWet.setValue(1);
    addAndMakeVisible(&sliderDryWet);
    sliderDryWet.addListener(this);

    addAndMakeVisible(labelDryWet);
    labelDryWet.setText("Dry/Wet", dontSendNotification);
    labelDryWet.attachToComponent(&sliderDryWet, false);
    labelDryWet.setColour(Label::textColourId, Colours::white);
    labelDryWet.setJustificationType(Justification::centredTop);
    
}

MultibandCompressorAudioProcessorEditor::~MultibandCompressorAudioProcessorEditor()
{

}

//==============================================================================
void MultibandCompressorAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("MultiBand Compressor", getLocalBounds(), Justification::centredTop, 1);

    Line<float> line1(Point<float>(650, 20), Point<float>(650, 570));
    g.drawLine(line1, 1.0f);

    Line<float> line2(Point<float>(40, 150), Point<float>(760, 150));
    g.drawLine(line2, 1.0f);

    Line<float> line3(Point<float>(40, 290), Point<float>(760, 290));
    g.drawLine(line3, 1.0f);

    Line<float> line4(Point<float>(40, 430), Point<float>(760, 430));
    g.drawLine(line4, 1.0f);
}

void MultibandCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    const int border = 40;
    const int dialWidth = ((getWidth() - (2* border)) / 7 );
    const int dialHeight = ((getHeight() - (5*border)) /4);
    const int buttonWidth = ((getWidth() - (2 * border)) / 7);
    const int buttonHeight = ((getHeight() - (5 * border)) / 8);

    //LOW COMPRESSOR DIALS//

    buttonLowOnOff.setBounds(border, border + (buttonHeight/2), buttonWidth, buttonHeight);
    sliderLowRatio.setBounds(border + dialWidth, border, dialWidth, dialHeight);
    sliderLowThreshold.setBounds(border + dialWidth*2, border, dialWidth, dialHeight);
    sliderLowAttack.setBounds(border + dialWidth * 3, border, dialWidth, dialHeight);
    sliderLowRelease.setBounds(border + dialWidth * 4, border, dialWidth, dialHeight);
    sliderLowKneeWidth.setBounds(border + dialWidth * 5, border, dialWidth, dialHeight);
    sliderLowMakeUpGain.setBounds(border + dialWidth * 6, border, dialWidth, dialHeight);


     //sets the position and size of the slider with arguments (x, y, width, height)
    buttonMidOnOff.setBounds(border, border + dialHeight + (buttonHeight / 2) + border, buttonWidth, buttonHeight);
    sliderMidRatio.setBounds(border + dialWidth, border + dialHeight + border, dialWidth, dialHeight);
    sliderMidThreshold.setBounds(border + dialWidth *2, border + dialHeight + border, dialWidth, dialHeight);
    sliderMidAttack.setBounds(border + dialWidth*3, border + dialHeight + border, dialWidth, dialHeight);
    sliderMidRelease.setBounds(border + dialWidth*4, border + dialHeight + border, dialWidth, dialHeight);
    sliderMidKneeWidth.setBounds(border + dialWidth*5, border + dialHeight + border, dialWidth, dialHeight);
    sliderMidMakeUpGain.setBounds(border + dialWidth * 6, border + dialHeight + border, dialWidth, dialHeight);

    //HIGH COMPRESSOR DIALS//
    //sets the position and size of the slider with arguments (x, y, width, height)
    buttonHighOnOff.setBounds(border, border + (dialHeight * 2) + (buttonHeight / 2) + border*2, buttonWidth, buttonHeight);
    sliderHighRatio.setBounds(border + dialWidth, border + dialHeight * 2 + border * 2, dialWidth, dialHeight);
    sliderHighThreshold.setBounds(border + dialWidth *2, border + dialHeight * 2 + border * 2, dialWidth, dialHeight);
    sliderHighAttack.setBounds(border + dialWidth * 3, border + dialHeight * 2 + border * 2, dialWidth, dialHeight);
    sliderHighRelease.setBounds(border + dialWidth * 4, border + dialHeight * 2 + border * 2, dialWidth, dialHeight);
    sliderHighKneeWidth.setBounds(border + dialWidth * 5, border + dialHeight * 2 + border * 2, dialWidth, dialHeight);
    sliderHighMakeUpGain.setBounds(border + dialWidth * 6, border + dialHeight * 2 + border * 2, dialWidth, dialHeight);

    //Frequency Cutoff Dials
    sliderLowerCutoff.setBounds(border + dialWidth * 2, border + dialHeight * 3 + border * 3, dialWidth, dialHeight);
    sliderHigherCutoff.setBounds(border + dialWidth * 4, border + dialHeight * 3 + border * 3, dialWidth, dialHeight);

    //Dry Wet Mix Dial
    sliderDryWet.setBounds(border + dialWidth * 6, border + dialHeight * 3 + border * 3, dialWidth, dialHeight);
}


void MultibandCompressorAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasMoved)
{
    
    //LOW COMPRESSOR SLIDER CHANGES//
    if (sliderThatWasMoved == &sliderLowRatio) {
        processor.setLowRatio(sliderLowRatio.getValue());
    }
    else if (sliderThatWasMoved == &sliderLowThreshold) {
        processor.setLowThreshold(sliderLowThreshold.getValue());
    }
    else if (sliderThatWasMoved == &sliderLowMakeUpGain) {
        processor.setLowMakeUpGain(sliderLowMakeUpGain.getValue());
    }
    else if (sliderThatWasMoved == &sliderLowAttack) {
        processor.setLowAttack(sliderLowAttack.getValue());
    }
    else if (sliderThatWasMoved == &sliderLowRelease) {
        processor.setLowRelease(sliderLowRelease.getValue());
    }
    else if (sliderThatWasMoved == &sliderLowKneeWidth) {
        processor.setLowKneeWidth(sliderLowKneeWidth.getValue());
    }


    //MID COMPRESSOR SLIDER CHANGES//
    else if (sliderThatWasMoved == &sliderMidRatio) {
        processor.setMidRatio(sliderMidRatio.getValue());
    }
    else if (sliderThatWasMoved == &sliderMidThreshold) {
        processor.setMidThreshold(sliderMidThreshold.getValue());
    }
    else if (sliderThatWasMoved == &sliderMidMakeUpGain) {
        processor.setMidMakeUpGain(sliderMidMakeUpGain.getValue());
    }
    else if (sliderThatWasMoved == &sliderMidAttack) {
        processor.setMidAttack(sliderMidAttack.getValue());
    }
    else if (sliderThatWasMoved == &sliderMidRelease) {
        processor.setMidRelease(sliderMidRelease.getValue());
    }
    else if (sliderThatWasMoved == &sliderMidKneeWidth) {
        processor.setMidKneeWidth(sliderMidKneeWidth.getValue());
    }

    //HIGH COMPRESSOR SLIDER CHANGES//
    else if (sliderThatWasMoved == &sliderHighRatio) {
        processor.setHighRatio(sliderHighRatio.getValue());
    }
    else if (sliderThatWasMoved == &sliderHighThreshold) {
        processor.setHighThreshold(sliderHighThreshold.getValue());
    }
    else if (sliderThatWasMoved == &sliderHighMakeUpGain) {
        processor.setHighMakeUpGain(sliderHighMakeUpGain.getValue());
    }
    else if (sliderThatWasMoved == &sliderHighAttack) {
        processor.setHighAttack(sliderHighAttack.getValue());
    }
    else if (sliderThatWasMoved == &sliderHighRelease) {
        processor.setHighRelease(sliderHighRelease.getValue());
    }
    else if (sliderThatWasMoved == &sliderHighKneeWidth) {
        processor.setHighKneeWidth(sliderHighKneeWidth.getValue());
    }

    //FREQUENCY CUTOFF SIDER CHANGES
    else if (sliderThatWasMoved == &sliderLowerCutoff) {
        processor.setLowerCutoff(sliderLowerCutoff.getValue());
    }
    else if (sliderThatWasMoved == &sliderHigherCutoff) {
        processor.setHigherCutoff(sliderHigherCutoff.getValue());
    }

    //DRY WET MIX SLIDER CHANGE
    else if (sliderThatWasMoved == &sliderDryWet) {
        processor.setDryWet(sliderDryWet.getValue());
    }

}

void MultibandCompressorAudioProcessorEditor::buttonClicked(Button* clickedButton)
{
    //LOW COMPRESSOR SLIDER CHANGES//
    if (clickedButton == &buttonLowOnOff) {
        processor.setLowOnOff(buttonLowOnOff.getToggleState());
    }
    else if (clickedButton == &buttonMidOnOff) {
        processor.setMidOnOff(buttonMidOnOff.getToggleState());
    }
    else if (clickedButton == &buttonHighOnOff) {
        processor.setHighOnOff(buttonHighOnOff.getToggleState());
    }
}


