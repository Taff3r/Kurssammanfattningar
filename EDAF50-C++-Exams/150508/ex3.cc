#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstddef>
#include <numeric>
class BI {
public:
    // Constructors
    BI(unsigned int i = 0);
    BI(const std::string);
    BI(const BI& other);

    // operators
    BI& operator = (const BI&);
    BI& operator += (const BI&);
   
    friend BI operator + (const BI&, const BI&);
    friend std::ostream& operator << (std::ostream&, const BI&);
    friend std::istream& operator >> (std::istream&, const BI&);
private:
    std::vector<unsigned char> digits;
};

BI::BI(unsigned int i){
    std::string digRep = std::to_string(i);
    std::reverse_copy(digRep.begin(), digRep.end(), std::back_inserter(digits));
}

BI::BI(const std::string s){
    std::reverse_copy(s.begin(), s.end(), std::back_inserter(digits));
}

BI::BI(const BI& other){
    std::copy(other.digits.begin(), other.digits.end(), std::back_inserter(digits));
}

BI& BI::operator = (const BI& rhs){
    if(this != &rhs){
        digits.clear();
        std::copy(rhs.digits.begin(), rhs.digits.end(), std::back_inserter(digits));
    }
    return *this;
}

BI operator + (const BI& lhs, const BI& rhs){
    std::vector<unsigned char> newDigits;
    unsigned char carry = 0;
    size_t pos = 0;    
    while(pos < lhs.digits.size() || pos < rhs.digits.size()){
        unsigned char dig1 = pos < lhs.digits.size() ? lhs.digits[pos] : 0;
        unsigned char dig2 = pos < rhs.digits.size() ? rhs.digits[pos] : 0;
        unsigned char sum = dig1 + dig2 + carry;
        std::cout << sum << std::endl;
        newDigits.push_back(sum % 10);
        carry = sum / 10;
        ++pos;
    }
    if(carry == 1) {
        newDigits.push_back(carry);
    }
    std::string result;
    auto it = newDigits.rbegin();
    while(it != newDigits.rend()){
        result += *it++;
    }
    std::cout << result << std::endl;
    return BI(result);
}

std::ostream& operator << (std::ostream& os, const BI& bi){
    std::string result;
    auto it = bi.digits.rbegin();
    while(it != bi.digits.rend()){
        result += *it++;
    }
    return os;
}

BI& BI::operator += (const BI& rhs){
    BI a = *this + rhs;
    *this = a;
    return *this;
}

int main(){
    BI a(1239999);
    BI b(9999);
    BI c = a + b;
    std::cout << c << std::endl;
}
