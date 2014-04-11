 #include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorfactory.h"

#include "classificationLibraries/svmclassifier.h"
#include "classificationLibraries/boostclassifier.h"
#include "featureExtractionLibraries/audioDescriptors/audiofeaturesamplesextractor.h"
#include "featureExtractionLibraries/audioDescriptors/audioextradescriptors.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    try{
        /*string filename;
        vector<string> features;
        if(argc < 3){
            filename = "country.wav";
            features.push_back("SPFLUX");
        }
        else{
            filename = argv[1];
            for(int i = 2; i < argc; i++)
                features.push_back(string(argv[i]));
        }*/

        string path = "./../genre_classifiers/";
        int size = 10;
        int feature_size = 1;
        int test_size = 2;
        int training_size = 40;
        string genres[] = {"reggae","blues","rock","metal","jazz","hiphop","classical","disco","pop","country"};
        string features[] = {"PITCHHISTO","MFCC","BEATHISTO","ENERGY","ZCR","SPCENTROID","SPROLLOFF","SPFLATNESS","SPFLUX"};
        //string features[] = {"CLASSIFIER"}; // very very bad

        vector<string> v_genres(genres,genres+size);
        vector<double> v_labels;
        v_labels.assign(size,-1.0);
        vector<int> v_training_sizes;
        v_training_sizes.assign(size,training_size);
        vector<int> v_test_sizes;
        v_test_sizes.assign(size,test_size);
        vector<string> v_features(features,features + feature_size);

        /*AudioRecord ar = WaveAudioLoader::loadAudioRecord("blues.wav");
        ClassifierDescriptorExtractor cl_de(ar,v_genres,v_features);

        std::vector<double> out = cl_de.extract();

        for(int i = 0; i < out.size(); i++)
            cout << out[i] << " ";
        cout << endl;*/

        for(int i = 0; i < size; i++){
            cout << v_genres[i] << ":"  << endl;
            v_labels[i] = 1.0;
            v_test_sizes[i] = 20;
            v_training_sizes[i] = 50;
            AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,v_features);

            AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
            AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();

            BoostClassifier classifier;

            classifier.train(training_excerpt);
            cout << "test: " << classifier.test(test_excerpt) << endl;
            cout << "training: " << classifier.test(training_excerpt) << endl;
            //classifier.save(path+v_genres[i]);
            v_labels[i] = -1.0;
            v_test_sizes[i] = test_size;
            v_training_sizes[i] = training_size;
        }
        return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO: lazy spectrum computation in fabric
    // TODO: SVM classify multiple data
}

