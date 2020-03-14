#include <memory>


/*
 * 3a. The Vector needs to implement the following:
 *      + size() function
 *      + [] operator
 */

/*
 * 3b. The Vector now additionaly needs to implement the following:
 *      + operator ==
 *      + Vector(std::initizalizer_list<T> il);
 */
template <typename T>
class Vector {
private:
    int sz{0};
    std::unique_ptr<T[]> elem{nullptr};
public:
    Vector() = default;
    Vector(int size): sz(size), elem(new T[size]) {};

    // 3a. size()
    int size() const {return sz;}

    // 3a. [] operator NOTE has to overloaded for read only.
    const T& operator [] (int i) const {
        return elem[i];
    }

    T& operator [] (int i) {
        return elem[i];
    }

    // 3b. operator ==
    bool operator == (const Vector<T>& rhs) {
        if (sz != rhs.sz) return false;
        for (int i = 0; i < size(); ++i){
            if(elem[i] != rhs.elem[i]) return false;
        }
        return true;
    }

    // 3b. Vector(std::initzalizer_list<T> li)
    Vector(std::initializer_list<T> l): Vector(l.size()) {
        std::copy(l.begin(), l.end(), elem.get());
    }
};
#include <iostream>
#include <cassert>
template <typename T>
void test_assign(Vector<T>& v, const T& val1, const T& val2){
    assert(v.size() >= 2);
    assert(val1 != val2);
    std::cout << v[1] << std::endl;
    v[1] = val2;
    std::cout << v[1] << std::endl;
    assert(v[1] == val2);
    assert(v[0] != v[1]);
}

template <typename T>
void test_read(const Vector<T>& v, const T& val1, const T& val2){
    assert(v.size() >= 2);
    assert(v[0] == val1);
    assert(v[1] == val2);
}
void test_create(){
    Vector<int> v1(5);
    assert(v1.size() == 5);
    for(int i = 0; i < v1.size(); ++i){
        v1[i] = 1;
    }

    Vector<int> v2{0,1,2,3,4};
    assert(v2.size() == v1.size());
    assert(v1 == v2);
}

int main() {
    Vector<int> v(2);
    auto val1 = 17;
    auto val2 = 42;
    test_assign(v, val1, val2);
    test_read(v, val1, val2);
    test_create();
    std::cout << "Tests passed." << std::endl;
}
