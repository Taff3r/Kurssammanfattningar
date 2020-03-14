#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <algorithm>
using std::string;
int main (int argc, char** args){

    struct Inserter {
        bool operator() (const std::string& lhs, const std::string& rhs){
            // rbegin / rend is reverse iterator
            return std::lexicographical_compare(lhs.rbegin(), lhs.rend(), rhs.rbegin(), rhs.rend());
        }
    };
    std::set<string, Inserter> words; 
    std::ifstream file(*(args + 1)); // Open file
    string word;
    while(file >> word) {
        string low;
        std::for_each(word.begin(), word.end(), [&low] (const char& c) {low += std::tolower(c);});
        words.insert(low);
    }
    file.close();
    std::ofstream out("backwords.txt");
    std::for_each(words.begin(), words.end(), [&out] (const string& s) {out << s << '\n';});
    out.close();
}
