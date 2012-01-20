#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "wave_header.h"

waveFormatHeader_t * basicHeader(){
    waveFormatHeader_t * wh = malloc(sizeof(waveFormatHeader_t));
    memcpy(wh->ChunkId, &"RIFF", 4);
    memcpy(wh->Format, &"WAVE", 4);
    memcpy(wh->Subchunk1ID, &"fmt ", 4); //notice the space at the end!
    wh -> Subchunk1Size = 16;

    return wh;
}

waveFormatHeader_t * stereo16bit44khzWaveHeader(){
    waveFormatHeader_t * wh = basicHeader();
    
    wh->AudioFormat = 1;
    wh->NumChannels = 2;
    
    wh -> SampleRate = 44100;
    wh -> BitsPerSample = 16;
    
    wh -> ByteRate = wh->NumChannels * wh -> SampleRate * wh -> BitsPerSample/8;
    wh -> BlockAlign = wh->NumChannels * wh -> BitsPerSample/8;
    
    memcpy(wh->SubChunk2ID, &"data", 4);
    return wh;
}

void setLengthForWaveFormatHeader(waveFormatHeader_t * wh, size_t numberOfFrames){
    wh -> ChunkSize = (40 - 8) + wh -> Subchunk2Size; //header-8 + data size; header size is always 40 for stereo16bit44khz
    wh -> Subchunk2Size = numberOfFrames * wh->NumChannels * wh->BitsPerSample/8;  
}

waveFormatHeader_t * stereo16bit44khzWaveHeaderForLength(size_t numberOfFrames){
    waveFormatHeader_t * wh = stereo16bit44khzWaveHeader();
    setLengthForWaveFormatHeader(wh, numberOfFrames);
    return wh;
}

//TODO: write each member just in case your compiler pads any of the struct members, though it shouldn't (do to its layout.)
size_t writeWaveHeaderToFile(waveFormatHeader_t * wh, FILE * file){
    return fwrite(wh, sizeof(waveFormatHeader_t), 1, file); 
}
