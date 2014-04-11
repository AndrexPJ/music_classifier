#include "audiofeaturesamplesextractor.h"

AudioFeatureSamplesExtractor::AudioFeatureSamplesExtractor(){}

std::vector< std::vector<double> > AudioFeatureSamplesExtractor::extract(std::vector<std::string> &file_names, std::vector<std::string> &feature_names){

    AudioDescriptorCollector *dc;
    AudioRecord ar;

    std::vector< std::vector<double> > out(file_names.size());

    for(int i  = 0; i < file_names.size(); i++){
        ar = WaveAudioLoader::loadAudioRecord(file_names[i]);
        AudioDescriptorCollectorFactory dc_factory(ar);
        dc = dc_factory.getAudioDescriptorCollector(feature_names);
        out[i] = dc->extract();
        delete dc;
    }
    return out;
}


AudioSamplesCreator::AudioSamplesCreator(std::vector<std::string> &genres, std::vector<double> &labels, std::vector<int> &training_sizes, std::vector<int> &test_sizes,
                                         std::vector<std::string> &feature_names, std::string path){
    int genres_size = genres.size();
    AudioFeatureSamplesExtractor samples_extractor;
    std::pair<std::vector<std::string>,std::vector<std::string> > temp_pair;
    std::vector<std::vector<double> > temp_samples;
    std::vector<double> temp_labels;

    for(int i = 0; i < genres_size; i++){
        //std::cout << genres[i] << " started..." << std::endl;

        temp_pair = Tools::getTwoFileNamesHeaps(path + genres[i],training_sizes[i],test_sizes[i],".wav");

        // training samples
        temp_samples = samples_extractor.extract(temp_pair.first,feature_names);
        this->training_samples.insert(this->training_samples.begin(),temp_samples.begin(),temp_samples.end());

        temp_labels.assign(temp_samples.size(),labels[i]);
        this->training_labels.insert(this->training_labels.begin(),temp_labels.begin(),temp_labels.end());
        // ----------------

        // test samples
        temp_samples = samples_extractor.extract(temp_pair.second,feature_names);
        this->test_samples.insert(this->test_samples.begin(),temp_samples.begin(),temp_samples.end());

        temp_labels.assign(temp_samples.size(),labels[i]);
        this->test_labels.insert(this->test_labels.begin(),temp_labels.begin(),temp_labels.end());
        // ------------

        //std::cout << genres[i] << " completed!" << std::endl;
    }

}


AudioFeatureExcerpt AudioSamplesCreator::getTrainingExcerpt(){
    return AudioFeatureExcerpt(this->training_samples,this->training_labels);
}

AudioFeatureExcerpt AudioSamplesCreator::getTestExcerpt(){
    return AudioFeatureExcerpt(this->test_samples,this->test_labels);
}
