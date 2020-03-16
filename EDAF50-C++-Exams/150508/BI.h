#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
class BI {
public:
    // Constructors
    BI(unsigned int i = 0);
    BI(const std::string);
    BI(const BI& other);

    // operators
    BI& operator = (const BI&);
    BI& operator + (const BI&);
    BI& operator += (const BI&);
   
    friend BI& operator + (const BI&, const BI&);
    friend std::ostream& operator << (std::ostream&, const BI&);
    friend std::istream& operator >> (std::istream&, const BI&);
private:
    std::vector<unsigned char> digits;
};

BI::BI(unsigned int i){
    std::string digRep = std::to_string(i);
    std::string rev;
    std::reverse_copy(digRep.begin(), digRep.end(), rev.begin());
    for(auto& c : rev) {
        digits.push_back(c); // least significant digit first
    }

    for(auto& c : digits){
        std::cout << c << std::endl;
    }
}

BI::BI(const std::string s){
    std::string rev;
    std::reverse_copy(s.begin(), s.end(), rev.begin());
    for(auto& c : rev) {
        digits.push_back(c); // least significant digit first
    }
}

int main(){
    BI(1000);

}
