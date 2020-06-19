# MultiBandCompressor
A multi-band compressor audio plugin. Programmed in Juce/C++.

For this implementation, the multiband compressor features three bands, low, mid and
high, which may be adjusted by the user by altering the cutoff frequency of the low/mid
band crossover and the mid/high band crossover. For each compressor applied to the
three bands, the user may separately alter the Ratio of compression, Threshold, Attack
time, Release time, Knee Width and Makeup Gain as well as enabling/disabling that
compressor completely. Finally, the user may also alter the Dry/Wet mix of the audio
effect’s output i.e. how much of the processed signal is output compared to the original
input signal.

![CompressorGUI](https://github.com/lbros96/MultiBandCompressor/blob/master/Multi-Band%20Compressor/CompressorGUI.PNG?raw=true "Title")
