#include "audioexceptions.h"

const char* AudioFilePathException::what() const throw(){
    return "Bad audio file path!";
}

const char* AudioFormatException::what() const throw(){
    return "Unsupported audio format!";
}


WaveFormatException::WaveFormatException(const char *message){
    this->message = message;
}

const char* WaveFormatException::what() const throw(){
    return this->message;
}
