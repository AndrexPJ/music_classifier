#include "audiosavers.h"


bool WaveAudioSaver::saveAudioRecord(const AudioRecord &record, std::string filename){

    std::ofstream out_stream;
    out_stream.open(filename, std::ios_base::binary);
    // header saving
    out_stream.write("RIFF",4);

    unsigned int subchunk2Size = record.channelDataSize * record.channelsCount * record.bitsPerSample / 8;
    unsigned int chunkSize = 36 + subchunk2Size;

    out_stream.write((char*)&chunkSize,sizeof(unsigned int));

    out_stream.write("WAVE",4);

    //char fmt[4] = {'f','m','t',' '};
    out_stream.write("fmt ",4);


    unsigned int subchunk1Size = 16;
    out_stream.write((char*)&subchunk1Size,sizeof(unsigned int));

    unsigned short audioFormat = 1;
    out_stream.write((char*)&audioFormat,sizeof(unsigned short));

    unsigned short numChannels = record.channelsCount;
    out_stream.write((char*)&numChannels,sizeof(unsigned short));

    unsigned int sampleRate = record.sampleRate;
    out_stream.write((char*)&sampleRate,sizeof(unsigned int));


    unsigned int byteRate = record.sampleRate * record.channelsCount * record.bitsPerSample / 8;
    out_stream.write((char*)&byteRate,sizeof(unsigned int));

    unsigned short blockAlign = record.channelsCount * record.bitsPerSample / 8;
    out_stream.write((char*)&blockAlign,sizeof(unsigned short));

    unsigned short bitsPerSample = record.bitsPerSample;
    out_stream.write((char*)&bitsPerSample,sizeof(unsigned short));

    //char subchunk2Id[4] = {'d','a','t','a'};
    out_stream.write("data",4);

    out_stream.write((char*)&subchunk2Size,sizeof(unsigned int));



    std::vector< std::vector <double> > data = record.getData();

    short int tInt;
    unsigned char tChar;

    int maxIntValue;

    switch (record.bitsPerSample) {
        case 8:
            maxIntValue = int(pow(2, record.bitsPerSample) - 1);
            break;
        case 16:
            maxIntValue = int(pow(2, record.bitsPerSample - 1) - 1);
            break;
        default:
            throw(WaveFormatException("Supported only 8bit and 16bit wave!"));
            break;
        }

        for(int step = 0; step < record.channelDataSize; step++){
            for(int ch = 0; ch < record.channelsCount; ch++){
                switch(record.bitsPerSample){
                case 8:
                    {
                        tChar = ((data[ch][step] + 1)/2)* maxIntValue;
                        out_stream.write((char*)&tChar,sizeof(unsigned char));
                        break;
                    }
                case 16:
                    {
                        tInt = data[ch][step] * maxIntValue;
                         out_stream.write((char*)&tInt,sizeof(short int));
                        break;
                    }
                default:
                    throw(WaveFormatException("Supported only 8bit and 16bit wave!"));
                    break;
                }
            }
        }
        // ---------- ----------------- ----------

        out_stream.close();



    return true;

}
