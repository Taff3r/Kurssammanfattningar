#include <string>
#include <vector>
#include <cstddef>
#include <iostream>
struct StringHolder {
    std::vector<std::string*> v;

    ~StringHolder() {
        for(size_t i = 0; i != v.size(); ++i){
            delete v[i];
        }
    }
    void insert(const std::string& s){
        v.push_back(new std::string(s));
    }

    std::string& operator [] (size_t pos) {return *v[pos];}
};

int main () {
    StringHolder sh;
    sh.insert("hello");
    sh.insert("there");
    std::cout << sh[0] << " ";
    std::cout << sh[1];
}
