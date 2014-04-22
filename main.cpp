#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"

#include "featureExtractionLibraries/audioDescriptors/audiodescriptorfactory.h"

#include "classificationLibraries/svmclassifier.h"
#include "classificationLibraries/boostclassifier.h"
#include "featureExtractionLibraries/audioDescriptors/audiofeaturesamplesextractor.h"
#include "classificationLibraries/committeeclassifier.h"
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
        string genres[] = {"classical","metal","jazz","blues","reggae","hiphop","pop","rock","country","disco"};
        string features[] = {"PITCHHISTO","MFCC","BEATHISTO","ENERGY","ZCR","SPCENTROID","SPROLLOFF","SPFLATNESS","SPFLUX"};
        vector<string> v_features(features,features + feature_size);


        //string features[] = {"MFCC","SPROLLOFF","SPFLATNESS","ENERGY"};
        double labels[] = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
        int training_sizes[] = {0,0,0,0,0,0,0,0,0,0};
        //int training_sizes[] = {8,8,8,8,8,8,8,8,8,8};
        //int training_sizes[] = {50,50,50,50,50,50,50,50,50,50};
        //int test_sizes[] = {20,20,20,20,20,20,20,20,20,20};
        int test_sizes[] = {18,18,18,18,18,18,18,18,18,18};
        //int test_sizes[] = {0,0,0,0,0,0,0,0,0,0};



          vector<string> v_genres(genres,genres+size);
          vector<double> v_labels(labels,labels+size);
          vector<int> v_training_sizes(training_sizes,training_sizes+size);
          vector<int> v_test_sizes(test_sizes,test_sizes+size);
          std::pair<double,double> test_result;
       //double test_result;
          double total_result;



        //int n_genre = 7;
        //v_labels[n_genre] = 1.0;
        //v_training_sizes[n_genre] = 0;
        //v_test_sizes[n_genre] = 18;

        AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,v_features,"./test/");

        //AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
        AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();

        std::vector<CommitteeClassifier*> classifiers;
        classifiers.resize(size);

        for(int i = 0; i < size; i++){
           classifiers[i] = CommitteeClassiferFactory::getCommitteeClassifier(genres[i]);
        }

        std::vector<std::vector<double> > samples = test_excerpt.getFeatureSamples();
        std::vector<std::string> classes = test_excerpt.getClassNames();
        for(int i = 0; i < samples.size();i++){
            cout << classes[i] << endl;
            for(int k = 0; k < size; k++){
                cout << classifiers[k]->classifyPercent(samples[i]) << " ";
            }
            cout << endl;
        }

        for(int i = 0; i < size; i++){
           delete classifiers[i];
        }

        //classifier.train(training_excerpt);
        //test_result = classifier.test(test_excerpt);
        //total_result = classifier.testTotal(test_excerpt);
        //cout <<"test: "<< " pos:" << test_result.first << " neg:" << test_result.second << " total:" << total_result << endl;

        //test_result = classifier.test(training_excerpt);
        //total_result = classifier.testTotal(training_excerpt);
        //cout <<"training: "<< " pos:" << test_result.first << " neg:" << test_result.second << " total:" << total_result << endl;

        //classifier.save("./master_classifiers/"+genres[n_genre]);

        /*std::vector<double> temp_test_results;
        std::vector<double> temp_training_results;

        std::vector<double> test_results;
        std::vector<double> training_results;*/


        /*ofstream out_stream;
        int repeats = 3;
        for(int i = 0; i < size; i++){

            out_stream.open("./results_all_genres/"+genres[i],ios_base::out);
            v_labels[i] = 1.0;
            v_training_sizes[i] = 50;
            v_test_sizes[i] = 20;

                for(int j = 0; j < feature_size; j++){
                    vector<string> v_features(features + j,features + j + 1);

                    for(int k = 0; k < repeats; k++){
                        AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,v_features);

                        AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
                        AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();

                        SVMClassifier classifier; // !!!

                        classifier.train(training_excerpt);
                        test_result = classifier.testTotal(test_excerpt);
                        temp_test_results.push_back(test_result);
                        //out_stream << features[j] << endl;
                        //out_stream <<"test: "<< " pos:" << test_result.first << " neg:" << test_result.second << endl;

                        test_result = classifier.testTotal(training_excerpt);
                        temp_training_results.push_back(test_result);
                        //out_stream <<"training: "<< " pos:" << test_result.first << " neg:" << test_result.second << endl;
                    }

                    double avr_test = 0.0;
                    double avr_training = 0.0;

                    for(int k = 0; k < repeats; k++){
                        avr_test += temp_test_results[k];
                        avr_training += temp_training_results[k];
                    }

                    avr_test/= repeats;
                    avr_training /= repeats;
                    test_results.push_back(avr_test);
                    training_results.push_back(avr_training);


                }

            std::vector<double>::iterator temp_max_it = std::max_element(test_results.begin(),test_results.end());
            double temp_max = *temp_max_it;
            int max_index = temp_max_it - test_results.begin();
            vector<string> temp_features;
            temp_features.push_back(features[max_index]);

            for(int j = 0; j < feature_size; j++){
                if(j == max_index) continue;
                temp_features.push_back(features[j]);
                test_result = 0;
                for(int k = 0; k < repeats; k++){
                    AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,temp_features);

                    AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
                    AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();

                    SVMClassifier classifier; // !!!

                    classifier.train(training_excerpt);
                    test_result += classifier.testTotal(test_excerpt);
                }
                test_result /= repeats;
                if(temp_max <= test_result){
                        temp_max = test_result;
                }
                else{
                        temp_features.pop_back();
                }

            }

            for(int f_i = 0; f_i < temp_features.size(); f_i++)
                out_stream << temp_features[f_i] << " ";
            out_stream << "res:" << temp_max << endl;

            v_test_sizes[i] = 2;
            v_training_sizes[i] = 6;
            v_labels[i] = -1.0;
            out_stream.close();

            temp_test_results.clear();
            temp_training_results.clear();

            test_results.clear();
            training_results.clear();
        }*/


        /*double test_result;
        double total_result;

        vector<string> v_features(features,features + feature_size);

        ofstream out_stream;

        int repeats = 1;

        vector<double> v_labels;
        v_labels.push_back(1.0);
        v_labels.push_back(-1.0);
        vector<int> v_training_sizes;
        v_training_sizes.assign(2,50);
        vector<int> v_test_sizes;
        v_test_sizes.assign(2,0);

        std::vector<double> temp_test_results;
        std::vector<double> temp_training_results;

        vector<string> v_genres;
        for(int i = 0; i < size; i++){
            out_stream.open("./results_all_genres/"+genres[i],ios_base::app);
            v_genres.push_back(genres[i]);
            for(int j = 0; j < size; j++){
                if(i == j) continue;
                v_genres.push_back(genres[j]);
                for(int k = 0; k < repeats; k++){
                    AudioSamplesCreator samples_creator(v_genres,v_labels,v_training_sizes,v_test_sizes,v_features);
                    AudioFeatureExcerpt training_excerpt = samples_creator.getTrainingExcerpt();
                    AudioFeatureExcerpt test_excerpt = samples_creator.getTestExcerpt();
                    BoostClassifier classifier; // !!!
                    classifier.train(training_excerpt);
                    test_result = classifier.testTotal(test_excerpt);
                    temp_test_results.push_back(test_result);
                    test_result = classifier.testTotal(training_excerpt);
                    temp_training_results.push_back(test_result);
                    classifier.save("./expert_classifiers/"+genres[i]+"_"+genres[j]);
                }

                double avr_test = 0.0;
                double avr_training = 0.0;

                for(int k = 0; k < repeats; k++){
                    avr_test += temp_test_results[k];
                    avr_training += temp_training_results[k];
                }

                avr_test/= repeats;
                avr_training /= repeats;
                out_stream << genres[j] << " train:" << avr_training << " test:" << avr_test << endl;
                v_genres.pop_back();
                temp_test_results.clear();
                temp_training_results.clear();
            }
            v_genres.pop_back();
            out_stream.close();
        }*/
        return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    // TODO: lazy spectrum computation in fabric
    // TODO: SVM classify multiple data
}

