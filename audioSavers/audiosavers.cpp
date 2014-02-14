#include "audiosavers.h"


bool WaveAudioSaver::saveAudioRecord(const AudioRecord &record, std::string filename){

    std::ofstream out_stream;
    out_stream.open(filename, std::ios_base::binary);
    // header saving
    out_stream.write("RIFF",4);

    unsigned short numChannels = record.getChannelsCount();
    unsigned int sampleRate = record.getSampleRate();
    unsigned short bitsPerSample = record.getBitsPerSample();

    int dataSize = record.getChannelDataSize();

    unsigned int subchunk2Size = dataSize * numChannels * bitsPerSample / 8;
    unsigned int chunkSize = 36 + subchunk2Size;

    out_stream.write((char*)&chunkSize,sizeof(unsigned int));

    out_stream.write("WAVE",4);

    //char fmt[4] = {'f','m','t',' '};
    out_stream.write("fmt ",4);


    unsigned int subchunk1Size = 16;
    out_stream.write((char*)&subchunk1Size,sizeof(unsigned int));

    unsigned short audioFormat = 1;
    out_stream.write((char*)&audioFormat,sizeof(unsigned short));


    out_stream.write((char*)&numChannels,sizeof(unsigned short));


    out_stream.write((char*)&sampleRate,sizeof(unsigned int));


    unsigned int byteRate = sampleRate * numChannels * bitsPerSample / 8;
    out_stream.write((char*)&byteRate,sizeof(unsigned int));

    unsigned short blockAlign = numChannels * bitsPerSample / 8;
    out_stream.write((char*)&blockAlign,sizeof(unsigned short));


    out_stream.write((char*)&bitsPerSample,sizeof(unsigned short));

    //char subchunk2Id[4] = {'d','a','t','a'};
    out_stream.write("data",4);

    out_stream.write((char*)&subchunk2Size,sizeof(unsigned int));



    std::vector< std::vector <double> > data = record.getData();

    short int tInt;
    unsigned char tChar;

    int maxIntValue;

    switch (bitsPerSample) {
        case 8:
            maxIntValue = int(pow(2, bitsPerSample) - 1);
            break;
        case 16:
            maxIntValue = int(pow(2, bitsPerSample - 1) - 1);
            break;
        default:
            throw(WaveFormatException("Supported only 8bit and 16bit wave!"));
            break;
        }

        for(int step = 0; step < dataSize; step++){
            for(int ch = 0; ch < numChannels; ch++){
                switch(bitsPerSample){
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
