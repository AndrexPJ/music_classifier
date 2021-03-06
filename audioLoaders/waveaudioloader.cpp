#include "waveaudioloader.h"
#include "iostream"

AudioRecord WaveAudioLoader::loadAudioRecord(string fileName){
    ifstream inFileStream;


    inFileStream.open(fileName,ios::binary);


    if(!inFileStream){
        std::cerr << fileName << std::endl;
        throw(AudioFilePathException());
    }


    WavHeader header;
    inFileStream.read((char*)&header,sizeof(WavHeader));


    if(header.audioFormat != 1){
        throw(AudioFormatException());
    }



    if((header.bitsPerSample !=8) && (header.bitsPerSample != 16))
        throw(WaveFormatException("Supported only 8bit and 16bit wave!"));

    AudioRecord resultRecord;


    resultRecord.setDataSize(header.numChannels,(8 * header.subchunk2Size) / (header.numChannels
                                                                            * header.bitsPerSample));

    resultRecord.setBitsPerSample(header.bitsPerSample);

    resultRecord.setSampleRate(header.sampleRate);


    // ---------- wave data reading ----------

    short int tInt;
    unsigned char tChar;


    int maxIntValue;
    int bps = resultRecord.getBitsPerSample();

    switch (bps) {
    case 8:
        maxIntValue = int(pow(2, bps) - 1);
        break;
    case 16:
        maxIntValue = int(pow(2, bps - 1) - 1);
        break;
    default:
        throw(WaveFormatException("Supported only 8bit and 16bit wave!"));
        break;
    }

    for(int step = 0; (step < resultRecord.getChannelDataSize()) && inFileStream.good(); step++){
        for(int ch = 0; ch < resultRecord.getChannelsCount(); ch++){
            switch(bps){
            case 8:
                {
                    inFileStream.read((char*)&tChar,sizeof(unsigned char));
                    resultRecord.setSpecificData((double(tChar)/maxIntValue)*2 - 1,ch,step); // normalized [-1..1]
                    break;
                }
            case 16:
                {
                    inFileStream.read((char*)&tInt,sizeof(short int));
                    resultRecord.setSpecificData((double(tInt)/maxIntValue),ch,step); // normalized [-1..1]
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

AudioRecord BinaryAudioLoader::loadAudioRecord(string filename){

    ifstream inFileStream;
    inFileStream.open(filename,ios::binary);

    if(!inFileStream)
        throw(AudioFilePathException());

    AudioRecord resultRecord;




    resultRecord.setBitsPerSample(16);

    resultRecord.setSampleRate(44100);


    // ---------- wave data reading ----------

    short int tInt;
    int maxIntValue =  int(pow(2, 16 - 1) - 1);

    std::vector< std::vector<double> > temp;
    temp.resize(1);

    while(inFileStream.good()){
          inFileStream.read((char*)&tInt,sizeof(short int));
          temp[0].push_back((double(tInt)/maxIntValue));
    }

    resultRecord.setData(temp);

    inFileStream.close();

    return resultRecord;

}
