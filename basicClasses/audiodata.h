#ifndef AUDIODATA_H
#define AUDIODATA_H

#include <vector>


template < class T >
class AudioData
{
private:
      std::vector< std::vector<T> > channelsData;
public:
      int channelsCount, channelDataSize,sampleRate;

      AudioData();
      ~AudioData();
      bool setData(std::vector< std::vector<T> > const &data);
      std::vector< std::vector<T> > getData() const;

      bool getSpecificData(T &out_data ,int channel, int n) const;
      bool setSpecificData(T data,int channel, int n);
      bool setSpecificData(const std::vector<T> &data, int channel);

      bool checkDataAvailability(int channel, int n) const;
      bool checkDataAvailability(int channel) const;

      bool setDataSize(int channels_count, int data_size);
      bool setDataSize(int channels_count);

      std::vector<T>& operator[] (int i);
};


// ##### methods implementation #####

template <class T>
AudioData<T>::AudioData(){
    this->channelsData.resize(0);
}

template <class T>
AudioData<T>::~AudioData(){
    this->channelsData.clear();
}

template <class T>
bool AudioData<T>::setData(std::vector<std::vector<T> > const &data){
    this->channelsData = std::vector< std::vector<T> >(data);
    return true;
}

template <class T>
std::vector<std::vector<T> > AudioData<T>::getData() const{
    return this->channelsData;
}

template <class T>
bool AudioData<T>::setSpecificData(T data,int channel, int n){

    if(checkDataAvailability(channel,n)){
        this->channelsData[channel][n] = data;
        return true;
    }
    else{
        return false;
    }

}

template <class T>
bool AudioData<T>::setSpecificData(const std::vector<T> &data, int channel){
    if(!checkDataAvailability(channel)) return false;
    if(this->channelsData[this->channelsData.size()-1].size() != data.size()) return false;

    this->channelsData[channel] = std::vector<T>(data);
    return true;
}

template <class T>
bool AudioData<T>::getSpecificData(T &out_data, int channel, int n) const{
    if(!checkDataAvailability(channel,n)) return false;

    out_data =  this->channelsData[channel][n];
    return true;
}

template <class T>
bool AudioData<T>::checkDataAvailability(int channel) const{
    int channel_size = this->channelsData.size();
    if(channel_size == 0) return false;
    if((channel > channel_size - 1) || (channel < 0)) return false;
    return true;
}

template <class T>
bool AudioData<T>::checkDataAvailability(int channel, int n) const{

    if(!this->checkDataAvailability(channel)) return false;

    int data_size = this->channelsData[this->channelsData.size() - 1].size();
    if((n > data_size - 1) || (n < 0 )) return false;

    return true;

}

template <class T>
bool AudioData<T>::setDataSize(int channels_count){
    if(channels_count < 0) return false;
    this->channelsData.resize(channels_count);
    this->channelsCount = channels_count;

    return true;
}

template <class T>
bool AudioData<T>::setDataSize(int channels_count, int data_size){
    if(this->setDataSize(channels_count)){
        if(data_size < 0) return false;

        for(int i = 0; i < channels_count; i++)
            this->channelsData[i].resize(data_size);

        this->channelDataSize = data_size;
        return true;
    }
    else return false;

}

template <class T>
std::vector<T>& AudioData<T>::operator [](int i){
    return (this->channelsData[i]);
}


#endif // AUDIODATA_H

