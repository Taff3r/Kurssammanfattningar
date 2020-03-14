#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;
class Foo {
public:
    Foo() : Foo(-1, "Foo") {}
    Foo(int x, const char* cs) : v{x}, s{new char[std::strlen(cs) + 1]} {std::strcpy(s, cs);}
    ~Foo() {delete[] s;}
    std::string get_s() const {return std::string(s);}
    int get_v() const {return v;}

    // Copy assignment
    Foo& operator = (const Foo& f) {
        if(this != &f) {
            delete[] s;
            s = new char[std::strlen(f.s) + 1];
            std::strcpy(s, f.s);
            this->v = f.v;
        }
        return *this; 
    }

    Foo(const Foo& f) {
        s = new char[std::strlen(f.s) + 1];
        std::strcpy(s, f.s);
        this->v = f.v;
    }
private:
    int v;
    char* s;
};

/*
2a.
The problem is that the class doesn't follow the rule of three, that is when owning a resource destructor, copy assignemnt, and copy constructor should be explicitly implemented and rely on synthezied ones. The problem arises when the lambda takes a Foo by copy value istead of reference calling the synthezied copy assignment, which doesn't function properly, causing the copy to now work.
*/

/**
 * 2b. Yes change the lambda so that it uses a reference to the Foo instead.
 */

/**
 * 2c.
 * Yes add the copy constructor in the class (also the copy assignment for best practices).j
 */

int main() {
    std::vector<Foo> v;
    v.reserve(4);
    v.emplace_back(1, "Hello");
    v.emplace_back(2, "World");
    v.emplace_back(3, "Testing");
    v.emplace_back(5, "Testing");

    auto res = std::find_if(begin(v), end(v), [] (Foo f) {return f.get_v() == 2;});

    if(res != v.end()) {
        cout << "found " << res->get_s() << endl;
    } else {
        cout << "not found" << endl;
    }
}
