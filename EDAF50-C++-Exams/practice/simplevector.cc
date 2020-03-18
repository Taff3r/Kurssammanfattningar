#include "simplevector.h"
#include <algorithm>
#include <iostream>
#include <iterator>
template <typename T>
SimpleV<T>::SimpleV(const SimpleV<T>& o){
    p = o.p;
    sz = o.sz;
}
template <typename T>
SimpleV<T>& SimpleV<T>::operator = (const SimpleV& rhs){
    std::cout << "c" << std::endl;
    if(this != &rhs){
        T* n = new T[rhs.sz];
        for(size_t i = 0; i != rhs.sz; ++i){
            n[i] = rhs.p[i];
        }
        delete[] p;
        p = n;
        sz = rhs.sz;
    }
    return *this;
}
template <typename T>
SimpleV<T>::SimpleV(SimpleV<T>&& temp){
    std::move(temp.p, temp.p + temp.sz, p);
    sz = temp.sz;
    temp.p = nullptr;
}
template <typename T>
SimpleV<T>& SimpleV<T>::operator = (SimpleV&& rhs){
    if(this != &rhs) {
        std::move(rhs.p, rhs.p + rhs.sz, p);
        rhs.p = nullptr;
    }
    return *this;
}

template <typename T>
void SimpleV<T>::resize(size_t newSize){
    T* n = new T[newSize];
    // copy as far as possible
    for (size_t i = 0; i != sz; ++i){
        n[i] = p[i];
    }
    delete[] p;

    // add uninit values as default.
    for(size_t i = sz; i != newSize; ++i){
        n[i] = T(); // T must be default constructable
    }
    p = n;
    sz = newSize;
}
template <typename T>
bool SimpleV<T>::operator == (const SimpleV<T>& rhs){
    if(sz != rhs.sz){
        return false;
    }

    for (size_t i = 0; i != sz; ++i){
        if(p[i] != rhs.p[i]) {
            return false;
        }
    }

    return true;
}
template <typename T>
bool SimpleV<T>::operator != (const SimpleV<T>& rhs){
   return !(*this == rhs);
}

int main(){
SimpleV<std::string> v (new std::string[4], 4);
std::string s[] = {"hello", "there", "general", "kenobi"};
std::copy(s, s+4, v.begin());
for(auto& s: v){
    std::cout << s << " ";
}
}

