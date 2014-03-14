#include "audioampspectrum.h"

AudioAmpSpectrum::AudioAmpSpectrum(){
}

AudioAmpSpectrum::AudioAmpSpectrum(const AudioAmpSpectrum &spectrum) : AudioSpectrum<double>(spectrum){
}


AudioPitchChroma::AudioPitchChroma(){
}

AudioPitchChroma::AudioPitchChroma(const AudioPitchChroma &pitch_chroma): AudioSpectrum<double>(pitch_chroma){
}


AudioBeatSpectrum::AudioBeatSpectrum(){

}

AudioBeatSpectrum::AudioBeatSpectrum(const AudioBeatSpectrum &spectrum) : AudioSpectrum<double>(spectrum){

}

AudioPhaseSpectrum::AudioPhaseSpectrum(){

}

AudioPhaseSpectrum::AudioPhaseSpectrum(const AudioPhaseSpectrum &spectrum) : AudioSpectrum<double>(spectrum){

}
