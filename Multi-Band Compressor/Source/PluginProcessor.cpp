#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandCompressorAudioProcessor::MultibandCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

    // Default Compressor values
    lowOnOff = true;
    lowMakeUpGain = 0.0;
    lowThreshold = 0.0;
    lowRatio = 1.0;
    lowTauAttack = 1.0;
    lowTauRelease = 1.0;
    lowKneeWidth = 0.0;

    // Default Compressor values
    midOnOff = true;
    midMakeUpGain = 0.0;
    midThreshold = 0.0;
    midRatio = 1.0;
    midTauAttack = 1.0;
    midTauRelease = 1.0;
    midKneeWidth = 0.0;

    // Default Compressor values
    highOnOff = true;
    highMakeUpGain = 0.0;
    highThreshold = 0.0;
    highRatio = 1.0;
    highTauAttack = 1.0;
    highTauRelease = 1.0;
    highKneeWidth = 0.0;

    lowCompressor = new Compressor;
    midCompressor = new Compressor;
    highCompressor = new Compressor;

    // Default Cutoff Frequencies
    myLowerCutoff = 500;
    myHigherCutoff = 3000;

    //Default Dry/Wet Mix
    myDryWet = 1.0;

}

MultibandCompressorAudioProcessor::~MultibandCompressorAudioProcessor()
{
}

//==============================================================================
const String MultibandCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultibandCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultibandCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultibandCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultibandCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultibandCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultibandCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultibandCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const String MultibandCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultibandCompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MultibandCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    numChannels = getTotalNumInputChannels();


    //Calculate Filter Coefficients
    //Setup coefficients for the low-pass filter for the low band
    lowBandFilterLeft1.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));
    lowBandFilterLeft2.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));
    lowBandFilterRight1.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));
    lowBandFilterRight2.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));

    //Setup coefficients for the makeshift band pass filter for the mid band
    //Made by overlapping low-pass and high-pass filters
    midBandHighPassFilterLeft1.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));
    midBandHighPassFilterLeft2.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));
    midBandHighPassFilterRight1.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));
    midBandHighPassFilterRight2.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));
    midBandLowPassFilterLeft1.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));
    midBandLowPassFilterLeft2.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));
    midBandLowPassFilterRight1.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));
    midBandLowPassFilterRight2.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));
    

    //Setup coefficients for the high-pass filter for the high band
    highBandFilterLeft1.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));
    highBandFilterLeft2.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));
    highBandFilterRight1.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));
    highBandFilterRight2.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));

    //Prepare the compressor
    (*lowCompressor).prepareToPlay(sampleRate, samplesPerBlock, numChannels);
    (*midCompressor).prepareToPlay(sampleRate, samplesPerBlock, numChannels);
    (*highCompressor).prepareToPlay(sampleRate, samplesPerBlock, numChannels);

    // Initialise the Compressor Parameters
    (*lowCompressor).updateParameters(lowThreshold, lowRatio, lowTauAttack, lowTauRelease, lowMakeUpGain, lowKneeWidth, sampleRate);
    (*midCompressor).updateParameters(midThreshold, midRatio, midTauAttack, midTauRelease, midMakeUpGain, midKneeWidth, sampleRate);
    (*highCompressor).updateParameters(highThreshold, highRatio, highTauAttack, highTauRelease, highMakeUpGain, highKneeWidth, sampleRate);
}

void MultibandCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MultibandCompressorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();


    // Initialise Buffer for Each Band
    AudioSampleBuffer dryOutput;
    AudioSampleBuffer lowOutput;
    AudioSampleBuffer midOutput;
    AudioSampleBuffer highOutput;

    dryOutput.clear();
    lowOutput.clear();
    midOutput.clear();
    highOutput.clear();

    // Set each buffer to an input
    dryOutput.makeCopyOf(buffer);
    lowOutput.makeCopyOf(buffer);
    midOutput.makeCopyOf(buffer);
    highOutput.makeCopyOf(buffer);

    
    float sampleRate = getSampleRate();


    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());



    // Recalculate filter coefficients

    //Setup coefficients for the low-pass filter for the low band
    lowBandFilterLeft1.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));
    lowBandFilterLeft2.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));
    lowBandFilterRight1.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));
    lowBandFilterRight2.setCoefficients(coefficients.makeLowPass(sampleRate, myLowerCutoff));


    //Setup coefficients for the makeshift band pass filter for the mid band
    //Made by overlapping low-pass and high-pass filters
    midBandHighPassFilterLeft1.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));
    midBandHighPassFilterLeft2.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));
    midBandHighPassFilterRight1.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));
    midBandHighPassFilterRight2.setCoefficients(coefficients.makeHighPass(sampleRate, myLowerCutoff));


    midBandLowPassFilterLeft1.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));
    midBandLowPassFilterLeft2.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));
    midBandLowPassFilterRight1.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));
    midBandLowPassFilterRight2.setCoefficients(coefficients.makeLowPass(sampleRate, myHigherCutoff));


    //Setup coefficients for the high-pass filter for the high band
    highBandFilterLeft1.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));
    highBandFilterLeft2.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));
    highBandFilterRight1.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));
    highBandFilterRight2.setCoefficients(coefficients.makeHighPass(sampleRate, myHigherCutoff));


    //Apply filters
    //Low-Band Filtering
    lowBandFilterLeft1.processSamples(lowOutput.getWritePointer(0), numSamples);
    lowBandFilterLeft2.processSamples(lowOutput.getWritePointer(0), numSamples);
    lowBandFilterRight1.processSamples(lowOutput.getWritePointer(1), numSamples);
    lowBandFilterRight2.processSamples(lowOutput.getWritePointer(1), numSamples);

    //Crossover 1//

    //Mid-Band Filtering
    midBandHighPassFilterLeft1.processSamples(midOutput.getWritePointer(0), numSamples);
    midBandHighPassFilterLeft2.processSamples(midOutput.getWritePointer(0), numSamples);
    midBandHighPassFilterRight1.processSamples(midOutput.getWritePointer(1), numSamples);
    midBandHighPassFilterRight2.processSamples(midOutput.getWritePointer(1), numSamples);

    midBandLowPassFilterLeft1.processSamples(midOutput.getWritePointer(0), numSamples);
    midBandLowPassFilterLeft2.processSamples(midOutput.getWritePointer(0), numSamples);
    midBandLowPassFilterRight1.processSamples(midOutput.getWritePointer(1), numSamples);
    midBandLowPassFilterRight2.processSamples(midOutput.getWritePointer(1), numSamples);

    //Crossover 2//

    // High-Band Filtering
    highBandFilterLeft1.processSamples(highOutput.getWritePointer(0), numSamples);
    highBandFilterLeft2.processSamples(highOutput.getWritePointer(0), numSamples);
    highBandFilterRight1.processSamples(highOutput.getWritePointer(1), numSamples);
    highBandFilterRight2.processSamples(highOutput.getWritePointer(1), numSamples);
    
    // Update compressor parameters!
    (*lowCompressor).updateParameters(lowThreshold, lowRatio, lowTauAttack, lowTauRelease, lowMakeUpGain, lowKneeWidth, sampleRate);
    (*midCompressor).updateParameters(midThreshold, midRatio, midTauAttack, midTauRelease, midMakeUpGain, midKneeWidth, sampleRate);
    (*highCompressor).updateParameters(highThreshold, highRatio, highTauAttack, highTauRelease, highMakeUpGain, highKneeWidth, sampleRate);

    if (lowOnOff) {
        (*lowCompressor).processBlock(lowOutput);
    }
    if (midOnOff) {
        (*midCompressor).processBlock(midOutput);
    }
    if (highOnOff) {
        (*highCompressor).processBlock(highOutput);
    }

    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    buffer.clear();
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        buffer.addFrom(channel, 0, dryOutput, channel, 0, numSamples, 1.0 * (1.0 - myDryWet));
        buffer.addFrom(channel, 0, lowOutput, channel, 0, numSamples, 1.0 * myDryWet);
        buffer.addFrom(channel, 0, midOutput, channel, 0, numSamples, 1.0 * myDryWet);
        buffer.addFrom(channel, 0, highOutput, channel, 0, numSamples, 1.0 * myDryWet);
        
    }

    // Apply the Overall Gain
    //buffer.applyGain(myCompressor.);
}

//==============================================================================
bool MultibandCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MultibandCompressorAudioProcessor::createEditor()
{
    return new MultibandCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void MultibandCompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultibandCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultibandCompressorAudioProcessor();
}
