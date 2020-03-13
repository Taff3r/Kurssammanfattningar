#include <iostream>
#include <string>
using std::string;
class Ptr {
public:
    Ptr(int* p) : curr(p) {}
    // 1.a: Change the return type from int to int&, const can stay.
    int& operator* () const { return *curr; }
private:
    int* curr;
};

// 1.b:  
// For the class to handle multiple types make it a template class
template <typename T>
class NuPtr {
private:
    T* curr;
public:
    NuPtr(T* p) : curr(p) {};
    // The class needs to specifiy operators, ++, *, and !=
    // The parameters SHOULD be a NuPtr refernce since x + 3 can be cast to a NuPtr
    bool operator != (const NuPtr& rhs) const {
       // Check the values of both pointers.
        return curr != rhs.curr;
    }

    NuPtr& operator ++ () {
        curr++; // Move pos of pointer 
        return *this;
    }
    T& operator * () const { return *curr; }
};
int main () {
    int x[] = {1, 2, 3};
    for (NuPtr<int> p = x; p != x + 3; ++p) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;
    string y[] = {"Despite", "the", "constant", "negative", "press", "covfefe"};
    for(NuPtr<string> p = y; p != y + 6; ++p) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;
}
