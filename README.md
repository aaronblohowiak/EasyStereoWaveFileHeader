# Easy Stereo Wave-File Header.
## The easiest way to write audio files.
### MIT-license

* Trivial to use WAV-file output!
* Created by Aaron Blohowiak on 11/15/11
* Based on the documentation from here: https://ccrma.stanford.edu/courses/422/projects/WaveFormat/

This library makes writing out stereo wave files very easy by populating the header with nice defaults.

I assume you are on a little-endian platform with 8-bit `char`, like x86/64 or ARM. (Works on iPhone.)

Here is an easy example of how to use this to write some uint16_t audio samples to disk:

    int16_t left_channel[NUMBER_OF_SAMPLES]; //some mono samples as signed integers;
    int16_t right_channel[NUMBER_OF_SAMPLES]; //some mono samples as signed integers;

    FILE * file;
    file = fopen("output.wav", "w");
    waveFormatHeader_t * wh = stereo16bit44khzWaveHeaderForLength(NUMBER_OF_SAMPLES);
    writeWaveHeaderToFile(wh, file);
    free(wh);

    for(int i=0;i<NUMBER_OF_SAMPLES;i++){
    //write the same data to both channels if you have a mono source.
    //you could make a mono file, but this is just easier =)
    fwrite(left_channel[i], sizeof(int16_t), 1, file); //left channel
    fwrite(right_channel[i], sizeof(int16_t), 1, file); //right channel
    }

    fclose(file);


## Alternatives:

On Osx, *nix:
  libsndfile (http://www.mega-nerd.com/libsndfile/) offers reading **and** writing.  Installs system-wide and is quite large.  Pretty easy to use, but GPL
  
On Osx:
  ExtAudioFile, though it is annoying to use if your needs are trivial it does offer lots of flexibility.