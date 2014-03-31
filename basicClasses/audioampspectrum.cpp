#include "audioampspectrum.h"

AudioAmpSpectrum::AudioAmpSpectrum() : AudioSpectrum<double>(){
}

AudioAmpSpectrum::AudioAmpSpectrum(const AudioAmpSpectrum &spectrum) : AudioSpectrum<double>(spectrum){
}


AudioPitchChroma::AudioPitchChroma() : AudioSpectrum<double>(){
}

AudioPitchChroma::AudioPitchChroma(const AudioPitchChroma &pitch_chroma): AudioSpectrum<double>(pitch_chroma){
}


AudioBeatSpectrum::AudioBeatSpectrum() : AudioSpectrum<double>(){

}

AudioBeatSpectrum::AudioBeatSpectrum(const AudioBeatSpectrum &spectrum) : AudioSpectrum<double>(spectrum){

}

AudioPhaseSpectrum::AudioPhaseSpectrum() : AudioSpectrum<double>(){

}

AudioPhaseSpectrum::AudioPhaseSpectrum(const AudioPhaseSpectrum &spectrum) : AudioSpectrum<double>(spectrum){

}
