#include <string>
#include <exception>
#include <iostream>
#include <cstring>
class string_view {
public:
    using size_type = std::string::size_type;
    using const_iterator = const char*;
    using iterator = const_iterator;
    
    constexpr static size_type npos = std::string::npos;

    string_view();
    ~string_view() = default;
    string_view(const string_view&) = default;
    string_view(const std::string&);
    string_view(const std::string&, size_type pos, size_type len);
    string_view(const char*, size_type len);
    string_view(const char*);
    bool empty() const;
    size_type size() const;
    const_iterator begin() const;
    const_iterator end() const;
    char operator[](size_type idx) const;
    char at(size_type idx) const;
    string_view substr(size_type pos, size_type len) const;
    size_type find(char ch, size_type pos=0) const;
    size_type find(string_view s, size_type pos=0) const;

    friend bool operator == (const string_view&, const string_view&);
    friend std::ostream& operator << (std::ostream&, const string_view&);
private:
    const char* str;
    size_type sz;
};

/**
 * Constructs from std::string
 */
string_view::string_view(const std::string& copy) : str{copy.c_str()}, sz{copy.size()} {}

string_view::string_view(const char* c) : str{c}, sz{strlen(c)} {}
char string_view::operator [] (size_type idx) const {return str[idx];}

string_view::string_view(const std::string& c, size_type pos, size_type len) : str{c.c_str() + pos}, sz{len - pos} {
    if (len > c.size() ) throw "len > size";
}
string_view::size_type string_view::size() const {return sz;}

std::ostream& operator << (std::ostream& os, const string_view& sv){
    for(size_t i = 0; i != sv.size(); ++i){
        os << sv[i];
    }
    return os;
}

bool string_view::empty() const {return sz == 0;}

string_view::size_type string_view::find(char ch, string_view::size_type pos) const {
    for(size_type i = pos; pos != sz; ++i){
        if(ch == str[i]){
            return i;
        }
    }
    return npos;
}

string_view string_view::substr(size_type pos, size_type len) const {
    return string_view(str, pos, len);
}

string_view::iterator string_view::begin() const{
    return str;
}

string_view::iterator string_view::end() const{
    return str + sz;
}

char string_view::at(size_type i) const {
    if( i > sz ){
        throw std::out_of_range("Out of bounds ::at()");
    } 
    return (*this)[i];
}
int main(){
    string_view s("hello there\0");
    std::cout << s << std::endl;
    std::string str = "hello there\0";
    string_view c (str, 0, 5);
    std::cout << c << std::endl;

}
