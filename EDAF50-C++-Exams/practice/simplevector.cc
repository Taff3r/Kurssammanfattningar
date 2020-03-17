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
    SimpleV<int> sv(new int[5], 5);
    for(size_t i = 0; i != sv.size(); ++i){
        sv[i] = i;
    }
    std::cout << (sv == sv)  << std::endl;
    SimpleV<int> c(new int[5], 5);
    sv.resize(10);
    std::for_each(sv.begin(), sv.end(), [] (int& i) {std::cout << i << " ";});
    std::cout << std::endl;
    c.resize(10);
    std::copy(sv.begin(), sv.end(), c.begin());
    for(auto& i : c){
        std::cout << i << std::endl;
    }
}
