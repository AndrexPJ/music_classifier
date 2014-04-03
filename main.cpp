#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"
#include "audioTransforms/audiowfft.h"
#include "audioTransforms/audiodwt.h"
#include "audioTransforms/audiorecordtransforms.h"
#include "audioTransforms/audiospectrumtransforms.h"
#include "audioDescriptors/audiodescriptorextractor.h"
#include "audioDescriptors/audiospectrumdescriptors.h"
#include "audioDescriptors/audiorecorddescriptors.h"
#include "audioDescriptors/audiorhythmdescriptors.h"
#include "audioDescriptors/audiotonalitydescriptors.h"
#include "audioTransforms/audiowavelettransforms.h"
#include "audioDescriptors/audiodescriptorfactory.h"

#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    try{
        string filename;
        vector<string> features;
        if(argc < 3){
            filename = "country.wav";
            features.push_back("BEATHISTO");
        }
        else{
            filename = argv[1];
            for(int i = 2; i < argc; i++)
                features.push_back(string(argv[i]));
        }

        AudioRecord ar =  WaveAudioLoader::loadAudioRecord(filename);
        //ar = AudioRecordTransforms::performNormalization(ar);

        AudioDecriptorCollectorFactory dc_factory(ar);
        AudioDescriptorCollector *dc = dc_factory.getAudioDescriptorCollector(features);

        std::vector<double> out = dc->extract();

        for(int i = 0; i < out.size(); i++)
            cout << i+1 <<":"<< out[i] << " ";

        delete dc;
        return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO: lazy spectrum computation in fabric
    // WARNING: check mfcc
}

