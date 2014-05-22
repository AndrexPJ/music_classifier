#include "audioLoaders/waveaudioloader.h"
#include "audioSavers/audiosavers.h"

#include "genreClassificationSystem/genreclassificationsystem.h"
#include "genreClassificationSystem/genreclassificator.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    try{
        string filename;
        string mode;


        if(argc < 2){
            cerr << "Try: music_classifier [f/s] filepath" << endl;
            return 1;
        }

        if(argc == 2){
            mode = "f";
            filename = argv[1];
        }
        else{
            mode = argv[1];
            filename = argv[2];
        }


        std::vector<double> result;
        if(mode == "f"){
             MultipleGenresClassificator *mgc = MultipleGenresClassificatorFactory::getMultipleGenreClassificator();
             result = mgc->getGenreHistogram(filename);
             delete mgc;
        }

        if(mode == "s"){
            GenreClassificationSystem *gcs = new GenreClassificationSystem();
            result = gcs->getGenreHistogram(filename);
            delete gcs;

        }


        string genres[] = {"классика","метал","джаз","блюз","регги","хип-хоп","поп","рок","кантри","диско"};

        for(int i = 0; i < result.size() - 1; i++)
            cout << genres[i] << ": " << result[i] << ", ";

        cout << genres[result.size() - 1] << ": " << result[result.size() - 1] << " ";
                cout << endl;



        return 0;
    }
    catch(exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}

