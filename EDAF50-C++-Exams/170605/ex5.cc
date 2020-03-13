#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
using std::string;
using std::map;
using std::multimap;

int main(int argc, char** args) {
    map<string, int> words;
    for (auto i = 1; i < argc; ++i){ // first arg is program name
        std::ifstream file(*(args + i));
        if (!file){
            std::cout << "Couldn't open file " << *(args + i) << std::endl;
        } else {
            string line;
            while(getline(file, line)){
                std::istringstream ss(line);
                string word;
                while(ss >> word){
                    ++words[word];
                }
            }
            file.close();
        }
    }
    struct Inserter {
        bool operator () (const int lhs, const int rhs){
            return lhs > rhs;      
        }
    };
    multimap<int, string, Inserter> sorted;
    for(std::pair<string, int> p : words){
        sorted.insert({p.second, p.first});
    }
    for (std::pair<int, string> p: sorted) {
        std::cout << p.second << '\t' << p.first << std::endl;
    }
}
