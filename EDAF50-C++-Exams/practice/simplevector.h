#ifndef SIMPLEVEC_H
#define SIMPLEVEC_H
#include <cstddef>
#include <iterator>
#include <iostream>
template <typename T>
class SimpleVIterator;
template <typename T>
class SimpleV {
    friend class SimpleVIterator<T>; 
public:
    SimpleV(T* p, size_t size): p(p), sz(size) {for(size_t i = 0; i != sz; ++i) p[i] = T();}
    // Rule of five 
    ~SimpleV() {delete[] p;}
    SimpleV(const SimpleV&);
    SimpleV& operator = (const SimpleV&);
    SimpleV(SimpleV&&);
    SimpleV& operator = (SimpleV&&);

    // Functions 
    size_t size() const {return sz;}
    void resize(size_t);

    // Iterators
    typedef SimpleVIterator<T> iterator;
    iterator begin() {return SimpleVIterator<T>(*this, 0);}
    iterator end() {return SimpleVIterator<T>(*this, sz);}

    // operators 
    T& operator [] (size_t i) {return p[i];}
    bool operator != (const SimpleV&); 
    bool operator == (const SimpleV&);
private:
    T* p;
    size_t sz;
};
template <typename T>
class SimpleVIterator : public std::iterator<std::forward_iterator_tag, void, void, void, void>{
public:
    SimpleVIterator(SimpleV<T>& v, size_t pos): v(v), pos(pos) {}
    SimpleVIterator& operator = (const SimpleVIterator& rhs) {
        v = rhs.v;
        pos = rhs.pos;
    }
    T& operator *() {return v[pos];}
    SimpleVIterator& operator ++() {++pos; return *this;}
    SimpleVIterator& operator ++(int) {auto ret = *this; ++pos; return ret;}
    bool operator != (const SimpleVIterator& rhs) {return v != rhs.v || pos != rhs.pos;}

private:
    SimpleV<T>& v;
    size_t pos;
};
#endif 
