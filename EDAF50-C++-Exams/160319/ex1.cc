/**
 * 1a. Det saknas följande:
 *      + operator << för att kunna skriva ut objektet
 *      + copy assignment (operator = ) för att kunna kopiera objekt
 */

/**
 * 1b. Det saknas deconstructor för när A går ur scope, samt en copy constructor för att call-by-value ska fungera.
 */

/**
 * 1c. Rule of five utökar rule of three genom att säga att utöver de 3 reglerna ska även move-assignment operator implementeras (operator = (A&& other))
 * och move constructor (A(A&& other)) implementeras. Detta är för mycket av nya funktioner i c++11 använder "move-semantics" för att det kan ge performance förbättringar när objektet man "move:ar" ifrån ändå ska förstöras.
 *
 */

/**
 * 1d.
 * Om de inte är virtuella kommer alltid en abstrakts class destruktor kallas vid destruktion vid objekt som ärver av den abstrakta klassen.
 * class Foo {
 * ~A(){...}
 *
 * };
 *
 * class Bar : public Foo {
 * private:
 *  int* a;
 *
 * public:
 *  Bar(int size) : a(new int[size]) {}
 *  ~Bar() {delete[] a;}
 * };
 *
 * int main() {
 *  A* a = new B(10);
 *
 *
 *  delete a; // Will call destructor in Foo but not in Bar causing memory leak.
 *
 * }
 *
 *
 *
 */
#include<cstddef>
#include<iostream>
#include<string>
class A {
public:
    A(size_t sz = 10) : storage(new int[size = sz]) {}
    int operator[] (int pos) const {return storage[pos];}
    int& operator[] (int pos) {return storage[pos];}
    ~A() {delete[] storage;}
    A& operator = (const A& rhs) {
        if(this != &rhs){ // protect against invalid self-assignemt
            int* copy = new int[rhs.size]; // allocate new memory and copy the elements
            std::copy(rhs.storage, rhs.storage + rhs.size, copy);
            delete [] storage;
            storage = copy;
            size = rhs.size;
        }
        return *this;
    }
    A(const A& other) {
        storage = new int[other.size];
        size = other.size;
        std::copy(other.storage, other.storage + size, storage);
    }

    friend std::ostream&  operator << (std::ostream& os, const A& a);
private:
    int* storage;
    size_t size;
};


std::ostream& operator << (std::ostream& os, const A& a) {
    for (size_t i = 0; i != a.size; ++i){
        os << a[i] << " ";
    }
    return os;
}

using std::cout;
using std::endl;
void print(const std::string& msg, A a){
    cout << msg << " " << a << endl;
}
int main() {
    A a1;
    for(size_t i = 0; i != 10; ++i){
        a1[i] = i + 1;
    }
    print("this is a1: " , a1);
    A a2;
    a2 = a1;
    print("this is a2: ", a2);
}


