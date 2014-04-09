#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorfactory.h"

#include "classificationLibraries/svmclassifier.h"
#include "classificationLibraries/boostclassifier.h"
#include "featureExtractionLibraries/audioDescriptors/audiofeaturesamplesextractor.h"
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

        int size = 10;
        int feature_size = 9;
        string genres[] = {"classical","reggae","blues","rock","jazz","country","disco","hiphop","metal","pop"};
        string features[] = {"PITCHHISTO","MFCC","BEATHISTO","ENERGY","ZCR","SPCENTROID","SPROLLOFF","SPFLATNESS","SPFLUX"};
        double labels[] = {-1.0,-1.0,-1.0,1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
        int training_sizes[] = {6,6,6,60,6,6,6,6,6,6};
        int test_sizes[] = {10,10,10,30,10,10,10,10,10,10};

        vector<string> v_genres(genres,genres+size);
        vector<double> v_labels(labels,labels+size);
        vector<int> v_training_sizes(training_sizes,training_sizes+size);
        vector<int> v_test_sizes(test_sizes,test_sizes+size);
        vector<string> v_features(features,features + feature_size);

        AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,v_features);

        AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
        AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();

        BoostClassifier classifier;

        classifier.train(training_excerpt);
        cout << classifier.test(test_excerpt) << endl;

        return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO: lazy spectrum computation in fabric
    // TODO: SVM classify multiple data
}

