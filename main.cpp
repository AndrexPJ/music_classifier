#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorfactory.h"

#include "classificationLibraries/svmclassifier.h"
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


        /*AudioRecord ar =  WaveAudioLoader::loadAudioRecord(filename);
        //ar = AudioRecordTransforms::performNormalization(ar);

        AudioDecriptorCollectorFactory dc_factory(ar);
        AudioDescriptorCollector *dc = dc_factory.getAudioDescriptorCollector(features);

        std::vector<double> out = dc->extract();

        for(int i = 0; i < out.size(); i++)
            cout << i+1 <<":"<< out[i] << " ";

        delete dc;*/

        /*double _v1[] = {0.0,0.0};
        double _v2[] = {0.0,1.0};
        double _v3[] = {1.0,1.0};
        double _v4[] = {1.0,0.0};
        double _labels[] = {0.0,1.0,0.0,1.0};

        std::vector<double> v1(_v1,_v1+2);
        std::vector<double> v2(_v2,_v2+2);
        std::vector<double> v3(_v3,_v3+2);
        std::vector<double> v4(_v4,_v4+2);
        std::vector<double> labels(_labels,_labels+4);

        std::vector<std::vector<double> > samples;
        samples.push_back(v1);
        samples.push_back(v2);
        samples.push_back(v3);
        samples.push_back(v4);


        SVMClassifier svm;
        svm.train(samples,labels);

        cout << svm.classify(v1) << endl;
        cout << svm.classify(v2) << endl;
        cout << svm.classify(v3) << endl;
        cout << svm.classify(v4) << endl;*/

        return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO: lazy spectrum computation in fabric
    // WARNING: check mfcc
}

