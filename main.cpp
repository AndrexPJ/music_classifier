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
        string genres[] = {"classical","rock","metal","jazz","blues","country","reggae","disco","hiphop","pop"};
        string features[] = {"PITCHHISTO","MFCC","BEATHISTO","ENERGY","ZCR","SPCENTROID","SPROLLOFF","SPFLATNESS","SPFLUX"};
        //string features[] = {"SPROLLOFF","MFCC","ENERGY","SPFLATNESS","BEATHISTO"};
        double labels[] = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
        int training_sizes[] = {6,6,6,6,6,6,6,6,6,6};
        int test_sizes[] = {10,10,10,10,10,10,10,10,10,10};

        //int n_genre = 0;
        //labels[n_genre] = 1.0;
        //training_sizes[n_genre] = 50;
        //test_sizes[n_genre] = 20;

        vector<string> v_genres(genres,genres+size);
        vector<double> v_labels(labels,labels+size);
        vector<int> v_training_sizes(training_sizes,training_sizes+size);
        vector<int> v_test_sizes(test_sizes,test_sizes+size);
        std::pair<double, double> test_result;

        /*vector<string> v_features(features,features + feature_size);

        AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,v_features);

        AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
        AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();

        SVMClassifier classifier;

        classifier.train(training_excerpt);
        test_result = classifier.test(test_excerpt);
        cout <<"test: "<< " pos:" << test_result.first << " neg:" << test_result.second << endl;

        test_result = classifier.test(training_excerpt);
        cout <<"training: "<< " pos:" << test_result.first << " neg:" << test_result.second << endl;*/


        ofstream out_stream;

        for(int i = 0; i < size; i++){
            out_stream.open("./results/"+genres[i],ios_base::out);
                for(int j = 0; j < feature_size; j++){

                    v_labels[i] = 1.0;
                    v_training_sizes[i] = 50;
                    v_test_sizes[i] = 20;
                    vector<string> v_features(features + j,features + j + 1);

                    AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,v_features);

                    AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
                    AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();

                    SVMClassifier classifier;

                    classifier.train(training_excerpt);
                    test_result = classifier.test(test_excerpt);
                    out_stream << features[j] << endl;
                    out_stream <<"test: "<< " pos:" << test_result.first << " neg:" << test_result.second << endl;

                    test_result = classifier.test(training_excerpt);
                    out_stream <<"training: "<< " pos:" << test_result.first << " neg:" << test_result.second << endl;

                    v_test_sizes[i] = 10;
                    v_training_sizes[i] = 6;
                    v_labels[i] = -1.0;
                }

            out_stream.close();
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

