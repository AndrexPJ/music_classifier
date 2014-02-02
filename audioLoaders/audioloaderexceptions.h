#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class AudioFilePathException : public std::exception{
    virtual const char* what() const throw();
};

class AudioFormatException : public std::exception{
    virtual const char* what() const throw();
};

class WaveFormatException : public std::exception{
private:
    const char* message;
public:
    WaveFormatException(const char* message = "Unsupported wave format!");
    virtual const char* what() const throw();
};

#endif // EXCEPTIONS_H
