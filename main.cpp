#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


enum Option {
    lines = 1,
    bytes = 2,
    words = 3,
    chars = 4
};

struct Counters{
    /*
     * 0 - number of lines
     * 1 - file size
     * 2 - number of words
     * 3 - number of symbols
     */
    uint64_t counters[4] = {0, 0, 0, 0};
    void addLine(){
        counters[0] += 1;
    }
    void setSize(unsigned int size){
        counters[1] = size;
    }
    void addWords(){
        counters[2] += 1;
    }
    void addSymbol(){
        counters[3] += 1;
    }
    uint64_t getInfo(int num){
        return counters[num];
    }
};

std::vector<int> OptionsChecker(std::string& opt){
    // Choose option(-s) which was/were got from the user
    std::vector <int> opt_vector;
    if (opt[1] == '-'){
        if (opt == "--lines"){
            opt_vector.push_back(Option::lines);
        } else if (opt == "--bytes"){
            opt_vector.push_back(Option::bytes);
        } else if (opt == "--words"){
            opt_vector.push_back(Option::words);
        } else if (opt == "--chars"){
            opt_vector.push_back(Option::chars);
        } else {
            std::cout << "There's no " << opt << " option." << std::endl;
        }
    } else {
        for (int i = 1; i < opt.length(); i++){
            if (opt[i] == 'l') {
                opt_vector.push_back(Option::lines);
            } else if (opt[i] == 'c'){
                opt_vector.push_back(Option::bytes);
            } else if (opt[i] == 'w'){
                opt_vector.push_back(Option::words);
            } else if (opt[i] == 'm'){
                opt_vector.push_back(Option::chars);
            } else {
                std::cerr << "There's no -" << opt[i] << " option." << std::endl;
            }
        }
    }
    return opt_vector;
}

std::string ParseName(const std::string& path_file) {
    // Parse name of the file from the path
    for (uint64_t i = path_file.size() - 1; i >= 0; i--) {
        if (path_file[i] == '\\'){
            return path_file.substr(i, path_file.size());
        }
    }
    return path_file;
}

void PrintOpt(const std::string& path_file, const bool opt_cond[]){
    Counters counter;
    std::string str_file;
    bool in_spaces  = true;
    std::ifstream file(path_file);
    if (!file.is_open()){
        std::cout << "File " << ParseName(path_file) <<" can't be opened." << std::endl;
    } else {
        while (std::getline(file, str_file)) {
            counter.addLine();
            for (char t : str_file) {
                if (isspace(t) != 0) {
                    in_spaces = true;
                } else {
                    if (in_spaces){
                        counter.addWords();
                        in_spaces = false;
                    }
                    counter.addSymbol();
                }
            }
        }

        std::filesystem::path p{path_file};
        counter.setSize(std::filesystem::file_size(p));
        if (!opt_cond[0]) {
            for (int i = 0; i < 4; i++) {
                std::cout << counter.getInfo(i) << '\t';
            }
            std::cout << ParseName(path_file) << std::endl;
        } else {
            for (int t = 1; t < 5; t++) {
                if (opt_cond[t]) {
                    std::cout << counter.getInfo(t - 1) << '\t';
                }
            }
            std::cout << ParseName(path_file) << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    /*
     * 0 - Хотя бы одна опция задана
     * 1 - -l, --lines вывод количества строк
     * 2 - -c, --bytes вывод размера файла в байтах
     * 3 - -w, --words вывод количества слов
     * 4 - -m, –chars вывод количества букв
     */
    bool opt_cond[6] = {false, false, false, false, false};
    std::vector<std::string> path_vector;
    std::string argv_str;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            argv_str = argv[i];
            for (int id_tmp: OptionsChecker(argv_str)) {
                opt_cond[id_tmp] = true;
            }
            opt_cond[0] = true;
        } else {
            path_vector.emplace_back(argv[i]);
        }
    }

    for (const std::string& path_file: path_vector) {
        PrintOpt(path_file, opt_cond);
    }
}
