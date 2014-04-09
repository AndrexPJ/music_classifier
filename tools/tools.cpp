#include "tools.h"

unsigned int Tools::nearestPowerOfTwoAbove(unsigned int number){
    if(number <= 1) return 1;
    --number;
    number |= (number >> 1);
    number |= (number >> 2);
    number |= (number >> 4);
    number |= (number >> 8);
    number |= (number >> 16);
    return number + 1;
}

std::vector<std::string> Tools::getAllFileNamesInDirectory(std::string dir_path, std::string extension){
    boost::filesystem::path path(dir_path);
    boost::filesystem::path temp_path;
    boost::filesystem::directory_iterator d_it(path), end_it;
    std::vector<std::string> out_files_names;

    for(; d_it != end_it; d_it++){
        if(boost::filesystem::is_regular_file(d_it->status()) && d_it->path().extension().string() == extension)
            temp_path = (d_it)->path();
            if(temp_path.string() != "")
                out_files_names.push_back(temp_path.string());
    }
    return out_files_names;
}


std::vector<std::string> Tools::getRandomFileNames(std::string dir_path, int count,  std::string extension){
    std::vector<std::string> all_files = Tools::getAllFileNamesInDirectory(dir_path,extension);
    std::vector<std::string> out_files;
    if(count > all_files.size())
        count = all_files.size();

    srand(time(NULL));
    int index;
    for(int i = 0; i < count && !all_files.empty(); i++){
        index = rand() % (all_files.size());
        out_files.push_back(all_files[index]);
        all_files.erase(all_files.begin() + index);
    }

    return out_files;
}

std::pair<std::vector<std::string>, std::vector<std::string> > Tools::getTwoFileNamesHeaps(std::string dir_path, int first_count, int second_count,  std::string extension){
    std::vector<std::string> all_files = Tools::getAllFileNamesInDirectory(dir_path,extension);

    std::pair<std::vector<std::string>, std::vector<std::string> > out_pair;
    std::vector<std::string> first_heap, second_heap;

    srand(time(NULL));
    int index;

    for(int i = 0; i < first_count && !all_files.empty(); i++){
        index = rand() % (all_files.size());
        first_heap.push_back(all_files[index]);
        all_files.erase(all_files.begin() + index);
    }

    for(int i = 0; i < second_count && !all_files.empty(); i++){
        index = rand() % (all_files.size());
        second_heap.push_back(all_files[index]);
        all_files.erase(all_files.begin() + index);
    }

    out_pair.first = first_heap;
    out_pair.second = second_heap;

    return out_pair;

}
