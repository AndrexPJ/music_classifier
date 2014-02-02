#include "waveaudioloader.h"
#include "iostream"

AudioRecord WaveAudioLoader::loadAudioRecord(string fileName){
    ifstream inFileStream;
    inFileStream.open(fileName,ios::binary);

    if(!inFileStream)
        throw(AudioFilePathException());

    WavHeader header;
    inFileStream.read((char*)&header,sizeof(WavHeader));


    if(header.audioFormat != 1)
        throw(AudioFormatException());


    if((header.bitsPerSample !=8) && (header.bitsPerSample != 16))
        throw(WaveFormatException("Supported only 8bit and 16bit wave!"));


    AudioRecord resultRecord;


    resultRecord.channelDataSize = (8 * header.subchunk2Size) / (header.numChannels
                                * header.bitsPerSample);
    resultRecord.channelsCount = header.numChannels;

    resultRecord.channelsData.resize(resultRecord.channelsCount);

    for(int i = 0; i< resultRecord.channelsCount; i++){
        resultRecord.channelsData[i].resize(resultRecord.channelDataSize);
    }

    // ---------- wave data reading ----------

    short int tInt;
    unsigned char tChar;

    resultRecord.bitsPerSample = header.bitsPerSample;
    resultRecord.sampleRate = header.sampleRate;

    int maxIntValue;

    switch (resultRecord.bitsPerSample) {
    case 8:
        maxIntValue = int(pow(2, resultRecord.bitsPerSample) - 1);
        break;
    case 16:
        maxIntValue = int(pow(2, resultRecord.bitsPerSample - 1) - 1);
        break;
    default:
        throw(WaveFormatException("Supported only 8bit and 16bit wave!"));
        break;
    }

    for(int step = 0; (step < resultRecord.channelDataSize) && inFileStream.good(); step++){
        for(int ch = 0; ch < resultRecord.channelsCount; ch++){
            switch(resultRecord.bitsPerSample){
            case 8:
                {
                    inFileStream.read((char*)&tChar,sizeof(unsigned char));
                    resultRecord.channelsData[ch][step] = (double(tChar)/maxIntValue);
                    break;
                }
            case 16:
                {
                    inFileStream.read((char*)&tInt,sizeof(short int));
                    resultRecord.channelsData[ch][step] = ((double(tInt)/maxIntValue) + 1)/2;
                    break;
                }
            default:
                throw(WaveFormatException("Supported only 8bit and 16bit wave!"));
                break;
            }
        }
    }
    // ---------- ----------------- ----------

    inFileStream.close();

    return resultRecord;
}
