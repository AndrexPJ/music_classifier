#include "noveltyfunctions.h"

NoveltyFunction::NoveltyFunction(){
    this->values.resize(0);
    this->interval_size = 0;
    this->channels_count = 0;
}

NoveltyFunction::NoveltyFunction(int interval_size, int channels_count){
    this->interval_size = interval_size;
    this->channels_count = channels_count;
    this->values.resize(this->channels_count);
    for(int i = 0 ; i < this->channels_count; i++)
        this->values[i].resize(this->interval_size);
}

int NoveltyFunction::getChannelsCount() const{
    return this->channels_count;
}

int NoveltyFunction::getIntervalSize() const{
    return this->interval_size;
}

double NoveltyFunction::perform(int n, int channel){
    if(n < 0 || n >= this->interval_size || channel < 0 || channel >= this->channels_count) return 0.0;
    else return this->values[channel][n];
}



std::vector < std::vector<double> > NoveltyFunction::getValues() const{
    return this->values;
}

FluxNoveltyFunction::FluxNoveltyFunction(AudioSpectrum<double> &spectrum) : NoveltyFunction(spectrum.getChannelDataSize(),spectrum.getChannelsCount()){
    this->spectrum = spectrum;

    double temp = 0.0;

    int fq_count = this->spectrum.getFrequencyCount();
    for(int ch = 0; ch < this->channels_count; ch++){
        this->values[ch][0] = 0.0;
        for(int fq_i = 0; fq_i < fq_count; fq_i++)
            this->values[ch][0] += sqrt(this->spectrum[ch][0][fq_i]);

        for(int n = 1; n < this->interval_size; n++){
            this->values[ch][n] = 0.0;
            for(int fq_i = 0; fq_i < fq_count; fq_i++){
                temp = this->spectrum[ch][n][fq_i] - this->spectrum[ch][n-1][fq_i];
                temp = (temp + fabs(temp)) / 2;
                this->values[ch][n] += temp;
            }
        }

    }
    //this->normalize();

}

DuxburyNoveltyFunction::DuxburyNoveltyFunction(AudioSpectrum<complex> &specrtum) : NoveltyFunction(specrtum.getChannelDataSize(), specrtum.getChannelsCount()){
    this->spectrum = specrtum;

    int fq_count = this->spectrum.getFrequencyCount();
    for(int ch = 0; ch < this->channels_count; ch++){
        this->values[ch][0] = 0.0;
        for(int fq_i = 0; fq_i < fq_count; fq_i++)
            this->values[ch][0] += this->spectrum[ch][0][fq_i].norm();

        for(int n = 1; n < this->interval_size; n++){
            this->values[ch][n] = 0.0;
            for(int fq_i = 0; fq_i < fq_count; fq_i++){
                this->values[ch][n] += (this->spectrum[ch][n][fq_i] - this->spectrum[ch][n-1][fq_i]).norm();
            }
        }
    }
    //this->normalize();
}

HainsworthNoveltyFunction::HainsworthNoveltyFunction(AudioSpectrum<double> &spectrum) : NoveltyFunction(spectrum.getChannelDataSize(),spectrum.getChannelsCount()){
    this->spectrum = spectrum;
    double epsilon = std::numeric_limits<double>::epsilon();
    int fq_count = this->spectrum.getFrequencyCount();
    double temp = 0.0;

    for(int ch = 0; ch < this->channels_count; ch++){
        this->values[ch][0] = 0.0;
        for(int fq_i = 0; fq_i < fq_count; fq_i++){
            temp = this->spectrum[ch][0][fq_i] / epsilon;
            if(temp > epsilon)
                this->values[ch][0] += log2(temp);
        }

        for(int n = 1; n < this->interval_size; n++){
            this->values[ch][n] = 0.0;
            for(int fq_i = 0; fq_i < fq_count; fq_i++){
            if(this->spectrum[ch][n - 1][fq_i] <= epsilon){
                temp = this->spectrum[ch][n][fq_i] / epsilon;
                if(temp > epsilon)
                    this->values[ch][n] += log2(temp);
            }
            else
                this->values[ch][n] += log2(this->spectrum[ch][n][fq_i] / this->spectrum[ch][n - 1][fq_i]);
            }
        }
    }
    //this->normalize();
}
