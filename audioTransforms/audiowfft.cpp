#include "audiowfft.h"


bool AudioWFFT::perform(AudioRecord &in_record, AudioSpectrum<complex> &out_spectrum, int window_size, int channels_count){
    if(window_size <= 0) return false;

    if(channels_count < 0) return false;


    if(channels_count > in_record.channelsCount) return false;

    int channels_true_count;
    if(channels_count == 0) // if zero then WWFT for all channels will perfomed
        channels_true_count = in_record.channelsCount;
    else
        channels_true_count = channels_count;


    out_spectrum.setDataSize(channels_true_count,in_record.channelDataSize);

    HannWindowFunction wf;

    for(int channel = 0; channel < channels_true_count; channel++){
        if(! WFFT::perform(in_record[channel],out_spectrum[channel],wf,window_size)) return false;
    }

    return true;
}
