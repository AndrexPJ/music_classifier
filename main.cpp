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
        string path;
        if(argc < 2){
            path = "./basis/";
            filename = "A.wav";
        }
        else{
            path = "./music_classifier-release-build/basis/";
            filename = argv[1];
        }

        AudioRecord ar =  WaveAudioLoader::loadAudioRecord(filename);
        ar = AudioRecordTransforms::performNormalization(ar);

        /*
        AudioRecord blues_b =  WaveAudioLoader::loadAudioRecord(path + "blues_b.wav");
        AudioRecord classical_b =  WaveAudioLoader::loadAudioRecord(path + "classical_b.wav");
        AudioRecord country_b =  WaveAudioLoader::loadAudioRecord(path + "country_b.wav");
        AudioRecord disco_b =  WaveAudioLoader::loadAudioRecord(path + "disco_b.wav");
        AudioRecord hiphop_b =  WaveAudioLoader::loadAudioRecord(path + "hiphop_b.wav");
        AudioRecord jazz_b =  WaveAudioLoader::loadAudioRecord(path + "jazz_b.wav");
        AudioRecord metal_b =  WaveAudioLoader::loadAudioRecord(path + "metal_b.wav");
        AudioRecord pop_b =  WaveAudioLoader::loadAudioRecord(path + "pop_b.wav");
        AudioRecord reggae_b =  WaveAudioLoader::loadAudioRecord(path + "reggae_b.wav");
        AudioRecord rock_b =  WaveAudioLoader::loadAudioRecord(path + "rock_b.wav");
        std::vector< std::vector<double> > basis;
        basis.push_back(blues_b.getData()[0]);
        basis.push_back(classical_b.getData()[0]);
        basis.push_back(country_b.getData()[0]);
        basis.push_back(disco_b.getData()[0]);
        basis.push_back(hiphop_b.getData()[0]);
        basis.push_back(jazz_b.getData()[0]);
        basis.push_back(metal_b.getData()[0]);
        basis.push_back(pop_b.getData()[0]);
        basis.push_back(reggae_b.getData()[0]);
        basis.push_back(rock_b.getData()[0]);
        basis = Tools::getBasis(basis,8192);
        std::vector<double> out = Tools::experiment(ar.getData()[0],basis);
        */
        ZCRDescriptorExtractor zcr_de = ZCRDescriptorExtractor(ar);
        AudioDecriptorCollectorFactory dc_factory(ar);
        string types[] = {"PITCHHISTO"};
        AudioDescriptorCollector *dc = dc_factory.getAudioDescriptorCollector(types,1);
        dc->addDescriptorExtractor(zcr_de);

        std::vector<double> out = dc->extract();

        for(int i = 0; i < out.size(); i++)
            cout << i+1 <<":"<< out[i] << " ";

       return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO : mfcc descriptor extractor
}

