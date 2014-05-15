#include "audiofeaturesamplesextractor.h"

AudioFeatureSamplesExtractor::AudioFeatureSamplesExtractor(){}

std::vector< std::vector<double> > AudioFeatureSamplesExtractor::extract(std::vector<std::string> &file_names, std::vector<std::string> &feature_names){

    std::vector< std::vector<double> > out(file_names.size());

    for(int i  = 0; i < file_names.size(); i++){
        out[i] = this->extract(file_names[i],feature_names);
    }
    return out;
}

std::vector<double> AudioFeatureSamplesExtractor::extract(string &file_name, std::vector<string> &feature_names){
    AudioRecord ar = WaveAudioLoader::loadAudioRecord(file_name);
    ar = AudioRecordTransforms::performDCRemoval(ar);

    AudioDescriptorCollectorFactory dc_factory(ar);
    AudioDescriptorCollector *dc = dc_factory.getAudioDescriptorCollector(feature_names);

    std::vector<double> out = dc->extract();
    delete dc;

    return out;
}


AudioSamplesCreator::AudioSamplesCreator(std::vector<std::string> &genres, std::vector<double> &labels, std::vector<int> &training_sizes, std::vector<int> &test_sizes,
                                         std::vector<std::string> &feature_names, std::string path){
    int genres_size = genres.size();
    AudioFeatureSamplesExtractor samples_extractor;
    std::pair<std::vector<std::string>,std::vector<std::string> > temp_pair;
    std::vector<std::vector<double> > temp_samples;
    std::vector<double> temp_labels;

    std::vector<std::vector<double> > training_samples;
    std::vector<std::vector<double> > test_samples;
    std::vector<double> training_labels;
    std::vector<double> test_labels;
    std::vector<std::string> training_class_names;
    std::vector<std::string> test_class_names;

    for(int i = 0; i < genres_size; i++){
        std::cout << genres[i] << " started..." << std::endl;

        temp_pair = Tools::getTwoFileNamesHeaps(path + genres[i],training_sizes[i],test_sizes[i],".wav");

        // training samples
        training_class_names.insert(training_class_names.begin(),temp_pair.first.begin(),temp_pair.first.end());
        temp_samples = samples_extractor.extract(temp_pair.first,feature_names);
        training_samples.insert(training_samples.begin(),temp_samples.begin(),temp_samples.end());

        temp_labels.assign(temp_samples.size(),labels[i]);
        training_labels.insert(training_labels.begin(),temp_labels.begin(),temp_labels.end());
        // ----------------

        // test samples
        test_class_names.insert(test_class_names.begin(),temp_pair.second.begin(),temp_pair.second.end());
        temp_samples = samples_extractor.extract(temp_pair.second,feature_names);
        test_samples.insert(test_samples.begin(),temp_samples.begin(),temp_samples.end());

        temp_labels.assign(temp_samples.size(),labels[i]);
        test_labels.insert(test_labels.begin(),temp_labels.begin(),temp_labels.end());
        // ------------

        std::cout << genres[i] << " completed!" << std::endl;
    }

    this->test_excerpt = AudioFeatureExcerpt(test_samples,test_labels,test_class_names);
    this->training_excerpt = AudioFeatureExcerpt(training_samples,training_labels,training_class_names);

}


AudioFeatureExcerpt AudioSamplesCreator::getTrainingExcerpt(){
    return this->training_excerpt;
}

AudioFeatureExcerpt AudioSamplesCreator::getTestExcerpt(){
    return this->test_excerpt;
}
