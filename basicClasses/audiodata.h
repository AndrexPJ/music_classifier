#ifndef AUDIODATA_H
#define AUDIODATA_H

#include <vector>

class AudioData
{
private:
      std::vector< std::vector<double> > channelsData;
public:
      AudioData();
      ~AudioData();
      bool setData(std::vector< std::vector<double> > const &data);
      std::vector< std::vector<double> > getData() const;

      bool getSpecificData(double &out_data ,int channel, int n) const;
      bool setSpecificData(double data,int channel, int n);

      bool checkDataAvailability(int channel, int n) const;

      bool setDataSize(int channels_count, int data_size);
      bool setDataSize(int channels_count);
};

#endif // AUDIODATA_H
