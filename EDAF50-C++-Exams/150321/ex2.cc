#include <string>
#include <algorithm>
#include <random>
#include <iostream>
void censor(std::string& badWords){
    const std::string WOVELS = "aeiouyåäöAEIOUYÅÄÖ";    
    const std::string REPLACEABLE = "@$!*#&%";
    std::uniform_int_distribution<unsigned> d(0, REPLACEABLE.size() - 1);
    std::default_random_engine e;
    for(auto& c : badWords) {
        if(WOVELS.find(c) != std::string::npos){
            c = REPLACEABLE[d(e)];
        }
    }
}

int main(){
    std::string s("hello there!");
    censor(s);
    std::cout << s << std::endl;
}
