#include "audiowfft.h"


bool AudioWFFT::perform(AudioRecord &in_record, AudioSpectrum<complex> &out_spectrum,WindowFunction &wf, int hop_size, int channels_count){
    int window_size = wf.getWindowSize();
    if(window_size <= 0) return false;

    if(channels_count < 0) return false;


    if(channels_count > in_record.getChannelsCount()) return false;

    int channels_true_count;
    if(channels_count == 0) // if zero then WWFT for all channels will perfomed
        channels_true_count = in_record.getChannelsCount();
    else
        channels_true_count = channels_count;

    out_spectrum.setDataSize(channels_true_count,((in_record.getChannelDataSize() - window_size + 1)/hop_size) +1 , window_size/2);
    out_spectrum.setWindowSize(window_size);
    out_spectrum.setSampleRate(in_record.getSampleRate());



    for(int channel = 0; channel < channels_true_count; channel++){
        if(!WFFT::perform(in_record[channel],out_spectrum[channel],wf,window_size,hop_size)) return false;
    }

    return true;
}
