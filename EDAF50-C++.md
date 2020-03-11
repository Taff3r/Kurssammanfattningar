# Pointers and references
A pointer is simply an integer that represents a location in the memory. A reference is simply the value at that address and can accessed through a pointer using the `*` operator of a pointer.
Ex. 
```c++
int* iPtr = 0; // Same as NULL / nullptr
int ten   = 10;
iPtr = &ten; // Set the value of iPtr to the ADDRESS of ten
*iPtr = 11; // Set the value at the address 
(*iPtr)++; // Same as above but with ++ operator

std::cout << *iPtr << std::endl; // 12
std::cout << ten << std::endl; // 12
std::cout << &ten << std::endl; // Some (hopefully) random address.
std::cout << iPtr << std::endl; // Same as above 
// Therefor we can do the following

bool adrSame = &ten == iPtr;
std::cout << adrSame << std::endl; // true / 1
```

You can also pass references and pointers to functions.

```c++
// The two following functions are equivalent in function.
void changeValueOfPointer(int* iPtr){
    *iPtr = 3; // Set the VALUE of the ADDRESS that the pointer points to.
}

void changeUsingReference(int& ref){
    ref = 4; // Change the VALUE
}

int main(){
    int v = 1;
    int* iPtr = &v;
    changeValueUsingPointer(iPtr); // Send in an ADDRESS / POINTER
    std::cout << *iPtr << std::endl; // 3
    changeUsingReference(*iPtr); // Send in a VALUE to be changed.
    std::cout << *iPtr << std::endl; // 4
    std::cout << ++v << << std::endl; // 5
}
```

When passing objects as parameters you should pass its **reference** for expected behaviour.
For pointers: accessing objects attributes and methods are done by using the `->` operator.
For references: it is done by using the `.` operator.

Ex. : 

```c++

#include <iostream>
#include <memory>
struct Foo {
    const int myNumber = 3;
    void printMyNumber(){
        std::cout << this->myNumber << std::endl;
    }
};

int main(){
    Foo* ptr = new Foo;
    Foo foo; // Objects declared this way are references under the hood.
    auto uPtr = std::make_unique<Foo>();
    ptr->printMyNumber();
    uPtr->printMyNumber();
    foo.printMyNumber();
    delete ptr;
    // uPtr is automatically deleted.
}
```


# Allocating memory
"You're not alive if you're not allocating memory"

Dynamic memory allocation in C++ is done by using the `new` keyword. (Similar to malloc in C) and returns a `pointer` to a position on the **heap**.

Ex.:
```c++
// Notice the asterisk
char* pChar = new char;
```
All memory allocated on the stack must be **explicitly** removed with the `delete` keyword. **Else we have a memory leak.**

```c++
// some time later...
delete pChar;
```
There is also a difference between allocating a pointer to a variable/object and an array when deleteing.
An array has to be deleted using the `delete[]` operator.
```c++
char* pChar = new char;
char* string[] = new char[5];

// some time later...

delete pChar;
delete[] string; // NOTE the [] operator for arrays.
```
Using `new` should be avoided when possible. But are sometimes neccessary. 
When possible instead use the `unique_pointer` and `shared_pointer` functions in the `memory` header.
These "smart" pointers automatically deletes the object to which it points to. 
## unique_pointer
A `unique_pointer` has single ownership of the pointer. Use them when the resource is not shared by muliple objects.

Ex. : 
```c++
# include <memory>
auto unq = std::unique_pointer<Foo>(new Foo);
// or 
std::unique_pointer<Foo> unq = std::unique_pointer<Foo>(new Foo);
```

The raw pointer can be accessed by using the `get()`-function. The object to which the pointer points will get deleted when the smart pointer deletes it. So copying the raw pointer is not adviced. E.g. do not `auto p = unq.get();` because `p` will be removed when unq is deleted.

## shared_pointers
A shared pointer is a smart pointer that is automatically deleted when not used. A `shared_pointer` can be "owned" by multiple resoruces at once.
    The resource is deleted only once **all of the owners** have gone out of scope. This is *usually* done by a counter that decreases once every time a owner calls the destructor.
Below is a example of an implementation of `SharedPointer` class that does not leak memory. (Atleast in the example below, I am not a one of the gods that writes code for the std.)
```c++
// shared.h
#ifndef SHARED_TEST_H
#define SHARED_TEST_H
#include <iostream>
    template <typename T>
    class SharedPointer {
        private:
            T* resource = nullptr;
            unsigned int* counter = new unsigned int;
        public:

            SharedPointer(T* resource): resource(resource){
                *counter = 1;
            }

            SharedPointer(SharedPointer& o): resource(o.resource), counter(o.counter){
                *counter += 1;
            }

            ~SharedPointer(){
                *counter -= 1;
                if (*counter == 0) {
                    delete resource;
                    delete counter;
                }
            }

            T* operator ->(){
                return resource;
            }

            T& operator *(){
                return *resource; 
            }

            void printCounter() const {
                std::cout << *counter << std::endl; 
                std::cout << counter << std::endl; 
            }

            SharedPointer& operator = (SharedPointer& rhs){
                if(this->resource != rhs.resource){ // Compare if resources have the same address
                    *counter -= 1; // Set counter for the current pointer -1
                    if(*counter == 0){
                        delete resource;
                        delete counter;
                    }
                    this->resource = rhs.resource;
                    this->counter = rhs.counter;
                    *(counter) += 1;
                }
                return *this;
            }
    };
#endif
```

```c++
#include "shared.h"
int main() {
    {
        SharedPointer<int> shared (new int);
        *shared = 3; 
        std::cout << *shared << std::endl; // 3
        std::cout << "outer" << std::endl;
        shared.printCounter(); 
        {
            std::cout << "inner" << std::endl;
            auto second = shared; // Copy constructor
            *second = 4;
            second.printCounter(); // 2 + some random address
            std::cout << *shared << std::endl; // 4 
            std::cout << *second << std::endl; // 4  
            // second is deleted 
        }
        std::cout << "outer again" << std::endl;
        shared.printCounter(); // 1 + same random address
        // shared is deleted
    }
    // Random struct used for example
    struct Foo {
        int x = 3;
    };

    SharedPointer<Foo> f(new Foo);
    SharedPointer<Foo> b(new Foo);
    f->x = 4;
    b = f; // copy assignment
    std::cout << (*f).x << std::endl; // 4 this weird use is just to prove that the * operator is implemented correctly.
    std::cout << (*b).x << std::endl; // 4
    // f and b is deleted automatically
}
```


## Destructors
Objects that own a resource should always implement a `destructor`. So when a smart pointer deletes itself it calls the destructor of that object. If the objects owns other pointers it is **important** that in the destructor deletes those resources. **Other wise we have a memory leak!**

Ideally a recursive call can be used when deleting resources.
Ex. :
```c++
class LinkedList {
    private:
        template <typename T>
            struct Node {
                T val;
                Node* next;
                // Constructor
                Node(T val, Node* next) : next(next), val(val){};
                // Destructor. NOTE THE DELETION.
                ~Node() {
                    delete next;
                }
            };
        Node* head;
    public:
        // Other functions
        // DESTRUCTOR. NOTE CALLING THE DELETE ON HEAD WILL DELETE HEADS->next which will delete next->next and so on until null is reached;
        ~Node(){
            delete head;
        }
};
```

# Include-guards
Header files can at most be included once in accordance to the **One defintion rule**.
To follow this easily make sure to use include guards in all header files.

```c++
// bar.h
#ifndef BAR_H
#define BAR_H
class Eyes {
    private:
        // some private stuff
    public:
        // some public stuff
};
#endif
```

# Enums
In C++ enumeration can be represented as an Enum-class
Ex.:
```c++
// eyes.h
enum class Eyes {
    brown, // == 0
    blue, // == 1
    green // == 2
};
void print(enum eye_colour c);
```
And can be accessed in other classes by using the `scope operator ::`
Ex.:
```c++
#include "eyes.h"
print(Eyes::brown);
```
**Regular** C-like enums are not namespaces in of themselves. See example below:

Ex. :
```c++
#include <iostream>
using namespace std;
class Foo {
    public:
        enum Lift {
            SQUAT,
            BENCH, 
            DEADLIFT 
        };

        static void printLift(Lift l){
            switch(l){
                case SQUAT:
                    cout << "SQUAT" << endl;
                    break;
                case BENCH:
                    cout << "BENCH" << endl;
                    break;
                case DEADLIFT:
                    cout << "DEADLIFT" << endl;
                    break;
            }
        }
};

int main(){
    Foo::Lift l = Foo::DEADLIFT; // NOTE! Not Foo::Lifts::DEADLIFT;
    Foo::printLift(l); // DEADLIFT
    Foo::printLift(0); // ERROR
    Foo::printLift(static_cast<Foo::Lift>(0)); // SQUAT
    l = 1; // ERROR
}
```
# Classes
Classes are usually split up in two seperate files. The header file (.h) specifying the class, and the source code file (.cc/.cpp). 
Ex. :

```c++
// IN foo.h
#ifndef FOO_H
#define FOO_H
class Foo:{
    private:
        int coolVar;
    public:
        Foo(int v) : coolVar(var){};
        void printVar();
}
#endif

// IN foo.cc
#include "foo.h"
#include <iostream>

void Foo:printVar() {
    // `this` is pointer therfore -> operator can be used.
    std::cout << this->coolVar << std::endl;
}
```
## const 
The keyword `const` can be applied in multiple ways in C++. In the usual way, similar to JS/Java where it is a promise to not change the variable declared `const`.
`const` can also be applied to parameters to functions, also giving a promise not to change the contents of the parameter. Therefor some operations cannot be done on the objects/variables that **can** change the objects contents. Such as ++/-- and [] or other *functions* that are not declared `const`.

Functions in classes can also be declared `const` they make it impossible to change the internal state of the object. But can be used to make sure that get()-like functions aren't used in a bad manner.

## static
Static behaves similary like they do in Java. When used in classes they refer to the same variable across object instances. **Static variables cannot be assigned unless they are also `const`**
Static functions also behave like in Java. They can be used for simple functions that don't require a state to function.

# Templates
Templates are used to achieve generic functions and classes that can be used with multiple different types. 
For each type used in the class they have to be declared at the top of the class. 

Ex.

```c++
#ifndef SIMPLEMAP_H
#define SIMPLEMAP_H
#include <vector>
template <typename K, typename V> // Templates for Key and Value
class SimpleMap {
    private:
        std::vector<V> vec;
        int hash(T& t);
        void grow();
        unsigned int inserted;
        const double MAX_SATIATION = 0.5;
    public:
        void insert(K&, V&);
        V& get(K&) const;
};
#endif
```
Template `functions` have to implemented with a template declaration for each function (Unless they are defined in the header).

Ex. 

```c++

// simplemap.h
#include "simplemap.h"
#include <string>
template <typename K, typename V>
void SimpleMap<K, V>::insert(K& k, V& v){
    if (inserted / vec.size() >= MAX_SATIATION) {
        grow();
    }
    inserted[hash(k)] = v; // Naive
}


// simplemap.cc
template <typename K, typename V>
int SimpleMap<K, V>::hash(K& k){
    int someResult = generic_hash(k);
    return someResult;
}

// Template specialization
template<>
int SimpleMap<std::string, int>::hash(std::string& k){
    return std::hash<std::string>{}(k);
}

// Partial specialization won't work
template<typename V>
int SimpleMap<std::string, V>::hash(std::string& k){
    return std::hash<std::string>{}(k);
}
```

For the partial specialization to work we have to redeclare the class for using `std::string` as the key.

```c++
// still simplemap.h
template <typename V>
class SimpleMap<std::string, V> {
    private:
        std::vector<V> vec;
        int hash(std::string& k);
        void grow();
        unsigned int inserted;
        const double MAX_SATIATION = 0.5;
    public:
        void insert(std::string&, V&);
        V& get(std::string&) const;
};
// now the specialization above will work.
```

# Overloading

**Functions** can be overloaded similarly to that in Java.
Ex.
```c++
#include <iostream>

void printNbr(double n){
    std::cout << "double " << n << std::endl;
}

void printNbr(int n){
    std::cout << "int " << n << std::endl;
}

void printNbr(float n){
    std::cout << "float " << n << std::endl;
}
template <typename D>
void printNbr(D n){
    std::cout << "generic " << n << std::endl;
}
int main() {
    float f = 10.2;
    double d = 10.2;
    int i = 10;
    printNbr(i); // int
    printNbr(d); // double 
    printNbr(f); // float
    printNbr('A'); // generic
    printNbr("Hello there"); // generic
}
```

Unlike in Java `operators` and `keywords` can be overloaded as well. Sometimes operator overloading is necessary for some `std` functions such as `std::sort` to work as expected (without supplying an addtional lambda). Like a `compareTo` in Java. Also the `<<` operator has to be overloaded for it to be able to stream to `std::cout`.
Some operators and keywords can not be overloaded these are: `sizeof . .* :: ?:`.
Ex. 
```c++
#include <algorithm>
#include <vector>
#include <iostream>
struct Date {
    int year, month, day;

    Date(int y, int m, int d): year(y), month(m), day(d){};
    // overload < to be able to sort the list.
    bool operator < (const Date& d){
        int t = year*365 + month*31 + day;
        int o = d.year*365 + d.month*31 + d.day;
        return t < o;
    }

    // Overload << NOTE the friend keyword!
    friend std::ostream& operator << (std::ostream& o, const Date& d){
        o << d.year << d.month << d.day << std::endl;
        return o;
    }
};

int main(){
    Date d(2020, 2, 3);
    Date o(2019, 2, 3);
    Date p(2019, 1, 1);

    std::vector<Date> v;
    v.push_back(o);
    v.push_back(d);
    v.push_back(p);

    std::sort(v.begin(), v.end());

    for(Date& d : v){
        std::cout << d;
    }

    //201911
    //201923
    //202023

}
```
For the Date example the overloading of the relevant operators would look like this (Note that this is a bad implementation):

```c++
    // overload < 
    bool operator < (const Date& d){
        int t = year*365 + month*12 + day;
        int o = d.year*365 + d.month*12 + d.day;
        return t < o;
    }

bool operator > (const Date& d){
    int t = year*365 + month*12 + day;
    int o = d.year*365 + d.month*12 + d.day;
    return t > o;
}

bool operator == (const Date& d){
    int t = year*365 + month*12 + day;
    int o = d.year*365 + d.month*12 + d.day;
    return t == o;
}

bool operator != (const Date& d){
    return !(*this == d);
}

// Also known as copy assignment
Date& operator = (const Date& rhs) {
    if (*this != rhs){ // First need to overload != operator
        year = rhs.year;
        month = rhs.month;
        day = rhs.day;
    }
    return *this;
}

// Overload << 
friend std::ostream& operator << (std::ostream& o, const Date& d){
    o << d.year << d.month << d.day << std::endl;
    return o;
}

friend std::istream& operator >> (std::istream& i, Date& d){
    i >> d.day >> d.month >> d.year;
    return i;
}

// This is used when for example d3 = d1 + d2;
Date operator + (const Date& rhs) const{
    int y = this->year + rhs.year; 
    int m = this->month + rhs.month; 
    int d = this->day + rhs.day; 
    return Date({y, m, d});
}
// Naive
Date operator - (const Date& rhs) const{
    int y = this->year - rhs.year; 
    int m = this->month - rhs.month; 
    int d = this->day - rhs.day; 
    return Date({y, m, d});
}

// Used for d1 += d2;
Date& operator +=(const Date& rhs){
    this->year += rhs.year; 
    this->month += rhs.month; 
    this->day += rhs.day; 
    return *this; 
}

Date& operator -=(const Date& rhs){
    this->year -= rhs.year; 
    this->month -= rhs.month; 
    this->day -= rhs.day; 
    return *this; 
}

// Naive
Date& operator ++ (){
    this->day++;
    return *this;
}

// Naive returning a reference to this allows chaining such as d3 = d1 + d2++;
Date& operator -- (){
    this->day--;
    return *this;
}

```

### Functors
Functors are special objects that overload the `()` operator. Functors can be thought of "a function with a state".
They are usually used with `std` functions such as `std::transform`

```c++
#include <algorithm>
#include <iostream>
#include <vector>
struct Adder {
    int x;
    Adder(int c): x(c){};
    int operator ()(int& d) {
        return d+x;
    }
};

int main() {
    std::vector<int> v = {1,2,3,4,5};
    std::transform(v.begin(), v.end(), v.begin(), Adder(1));
    for (int& i : v){
        std::cout << i << " ";
    }
    // 2 3 4 5 6
}

```
# Iterators
Iterators are special classes that keep a reference to a reference to a specific value. An iterator has overload specific operators: `!=`, `==`, `=` and `++`(Depending on the type of iterator), it also has to be copy constructible.
Iterators a simply keeping track of a value at specific position. A simple example is shown below.
Iterators are objects are usually created by calling the parent classes functions `begin()` and `end()` where `begin()` points to the first element, and `end()` points to last + 1. 
Iterators are present in almost all `std` containers.
Containers that don't have a `begin()` and `end()` functions cant use for-each loops.
Example:
```c++
std::vector<int> v = {1,2,3,4,5};
auto b = v.begin(); // copy iterator
int i = 5;
while (b != v.end()){
    *b = i++; // Set the value of that the iterator points to to i and increase i by one.
    b++; // Increment the position of the iterator.
}
for(int& d : v) { // Can use for-each since std::vector has iterators.
    std::cout << d << " ";
}
// 5 6 7 8 9
```
`TODO: Implement a iterator yourself`

# Polymorphism and Inhertiance
### Static binding
The meaning of a construct is decided at *compile-time*.
Applies to:
    1. Overloading
    2. Generic programming (Templates)
### Dynamic binding
The meaning of a construct is decided at *run-time*.
Applies to:
    1. `virtual` functions.

Dynamic binding gets some performance overhead but barely noticable. 

### Concrete types
Behaves just like "built-in" types.
    1. Can be copied.
    2. Can be directly referred to.
    3. Can be placed on the stack and in other objects.
    4. The *representation* is part of the *definition*. (Can be private, but is known.)

A concrete type: Vector.
```c++
class Vector {
public:
    Vector(int l = 0): elem(new int[l], sz(l)) {}
    ~Vector() {delete[] elem;}
    int size() const {return sz;}
    int& operator[](int i) {return elem[i];}
private:
    int* elem;
    int sz;
};
```
### Abstract type
An **abstract type** decouples the interface from the representation.
1. Isolates the user from the implematation details.
2. The representation of objects (including the size!) is now known!
3. Can only be accessed through pointers or references.
4. Cannot be instantiated. (Only concrete subclasses)
5. Code using the abstract type *does not need to be recompiled* if the conrecte subclasses are changed.

An abstact type abstact class (interface in Java):
```c++
class Container {
public:
    virtual int size() const = 0; // Pure virtual function
    virtual int& operator[](int o) = 0;
    virtual ~Container() = default; // A polymorphic type needs a virtual destructor
    // copy && move
};
```
In C++ member functions are **NOT** `virtual` unless declared so!
1. It is possible to inherit from a class and *hide* functions.
2. Base class functions can be explicitly called.
3. Can be used to "extend" a function. (Add things before and after the function).
```c++
struct Clock {
private:
    int seconds;
public:
    Clock& tick(); // NOTE! Not virtual
    int getTicks() {return seconds;}
};

stuct AlarmClock : public Clock {
    using Clock::Clock;
    AlarmClock& tick(); // Hides Clock::tick() 
private:
    int alarmTime;
}

AlarmClock& AlarmClock::tick() {
    Clock::tick(); // Default behaviour of base class.
    if (getTicks() == alarmTime){
        // Sound the alarm!
    }
    return *this;
}
```
### Implementing an interface
```c++
class Vector : public Container {
public:
    Vector(int l = 0): p{new int[l]}, sz{l} {}
    ~Vector() {delete[] elem;}
    int size() const override {return sz;} // NOTE Override <=> @Override in Java (C++11) Not acctually necessary but is useful for preventing errors when writing code.
    int& operator[](int i) override {return elem[i];}
private:
    int *elem;
    int sz;
};
```

**Destuctors** must be `virtual`.
```c++
Container* c = new Vector(10);

// ...

delete c; // The destuctor of Container is called
```
In the example above `~Container()` is called. If it is not virtual `~Vector()` is never called and we have a **memory leak**. 
We therefore declare the `Container` destuctor virtual to make sure every class the implements it **has to** implement the destructor to compile without errors.


### Using an abstract class.
```c++
void fill(Container& c, int v){
    for(int i = 0; i != c.size(); ++i){
        v[i] = v;
    }
}

void print(Container& c) {
    for (int i = 0; i != c.size(); ++i) {
        cout << c[i] << " ";
    }
    cout << endl;
}

int main() {
    Vector v(10); // Vector implements Container
    print(v);
    fill(v, 3);
    print(v);
}
```
Assume we have two other classes that implements `Container`.
```c++
class MyArray : public Container { // ... };
class List : public Container { // ... };

int main() {
    Vector v(10); // Vector implements Container
    print(v);
    fill(v, 3);
    print(v);

    MyArray a(5);
    print(a);
    fill(a, 3);
    print(a);

    List l{1,2,3,4,5};
    print(l);
}
```
In the example above *dynamic binding* of `Container::size()` and `Container::operator[]()`.

### Templates and abstract types
```c++
template <typename T>
class Container {
public:
    virtual size_t size() const = 0;
    virtual T& operator[](size_t o) = 0;
    virtual ~Container() = default;
    virtual void print() const = 0;
};

template <typename T>
class Vector : public Container<T> {
public:
    Vector(size_t l = 0) p{new T[l]}, sz{l} {}
    ~Vector() {delete[] p;}
    T& operator[](size_t i) override {return p[i];}
    virtual void print() const override;
private:
    T *p;
    size_t sz;
};
```

### Rules for base class constructor
+ The default constructor of the base class is called (If it exists!)
+ Arguments to the base class constructor
    - Are given in the memember init. list in the derived class constructor.
    - The name of the base class must be `used`. (`super()` like in Java does not exists because of the possiblity of mulitple inheritence.)

Order of init. in constuctor (for a derived class)
1. The base class is initizalized: The base class construcotr is called.
2. The derived class is initilized: Data members (in the derived class) is initizalized.
3. The constructor body of the derived class is executed.

Explicit call of base class constructor in the member initizalizer list:
```c++
D::D(// params ) : B( //params ), //... {//...}
``` 

Note:
+ Constructors are not inherited
+ **DO NOT CALL VIRTUAL FUNCTIONS IN A CONSTUCTOR**: In the base class B `this` is of a type `B*`.

**WRONG WAY**:
```c++
class Base {
public:
    Base(int i): x(i) {}
    virtual void print() {cout << "Base: " << x << endl;}
private:
    int x;
};

class Derived : public Base {

};

int main() {
    Derived b1; // Use of deleted function
                // Derived::Derived()
    Derived d2(5); // No matching fucntion for call to 
                   // Derived::Derived(int)
}
```

**RIGHT WAY**:
```c++
class Base {
public:
    Base(int i=0): x(i) {} // NOTE default value of i!
    virtual void print() {cout << "Base: " << x << endl;}
private:
    int x;
};

class Derived : public Base {
    Derived(int i) : Base(i) {} // Calls constrctor of Base.
};

int main() {
    Derived b1; // OK!
    d.print();
    Derived d2(5); // OK!
    d2.print();
}
```
### Rules for inherited constructors
+ `using` makes all base class constructors inherited, except:
    - Those hidden by the derived class (with the same parameters)
    - default, copy, and move constructors
        + If not defined, synthesized as usual
+ Default arguments in the super class gives multiple inherited constructors.
+ The copy constructor shall copy the **entire** object.
    - Typically done by calling the base class constructor.
+ The same applies to the `operator=`.
+ Different from the destructor
    - A destructor shall only deallocate what has been allocated in the class itself. The base class destructor is implictly called.
+ the synthesized default constructor or the copy contril members are deleted in a derived class if the correspoing function is deleted in the base class. (i.e. `private` or `=delete`)
    - Default constructor
    - copy constructor
    - copy assignment operator
    - (destructor, but avoid classes without a destructor)
+ Base classes should (typically) define these `=default`

### Accessibility and inheritance
```c++
class D1: public B { // public inheritance
 // ..
};

class D1: protected B { // protected inheritance
 // ..
};

class D1: private B { // private inheritance
 // ..
};
```
| Inheritance type | Access. in B               | Access. in D                  |
|------------------|----------------------------|-------------------------------|
| `public`         | `public protected private` |`public protected private`     |
| `protected`      | `public protected private` | `protected protected private` |
| `private`        | `public protected private` | `private private private`     |

The accessibility inside D is **not** affected by the type of inheritance.

### Function overloading and inheritance
Functon overloading does not work as usual between levels in a class hierarchy.A
```c++
class C1 {
public:
void f(int) {cout << "C1::f(int)\n";}
};

class C2: public C1 {
public:
    void f() {cout << "C2::f(void)\n";}
};

int main() {
C1 a;
C2 b;

a.f(5); // OK. Calls C1::f(int)
b.f(); // OK. Calls C2::f(void)
b.f(2); // Error. Calls C1::f(int) is hidden
b.C1::f(10); // OK
}
```

The fix;
```c++
class C1 {
public:
void f(int) {cout << "C1::F(int)\n";}
};

class C2: public C1 {
public:
    using C1::f;
    void f() {cout << "C2::f(void)\n";}
};

int main() {
C1 a;
C2 b;

a.f(5); // OK. Calls C1::f(int)
b.f(); // OK. Calls C2::f(void)
b.f(10); // OK. Calls C1::f(int)
}
```
### Calling functions of base class in derived class.
**Exercise:** What is wrong with the following code?
```c++
#include <string>
#include <iostream>
using std::string;
using std::ostream;

class Base {
public:
    Base(string s) : basename(s){}
    string name() { return basename; }
    virtual void print(ostream& os) { os << basename; }
private:
    string basename;
};

class Derived : public Base {
public:
    Derived(string s, int i): Base(s), i(i){} // Call constructor of Base.
    void print(ostream& os) override {print(os); os << " " << i;}
private:
    int i;
};

int main () {
    Derived d("hello", 2);
    d.print(std::cout);
}
```

**Solution:** Calling `print` in derived results in an endless loop because it call itself and not the function in Base.
**The fix:** In Deriveds `print` explicitly call the Base class's `print`.
```c++
// In Derived
void print(ostream& os) override {Base::print(os); os << " " << i;} // Now works. :) (hello 2)
```
### Memory allocation of abstract types
** YOU CANNOT ALLOCATE AN OBJECT OF AN ABSTRACT TYPE **
```c++
Dog d;
Cat c;
Bird b;
Vector<Animal> zoo {d,c,b}; // ERROR cannot allocate an object of abstract type `Animal`
```
The fix: **USE POINTERS**
```c++
Dog d;
Cat c;
Bird b;
Vector<Animal*> zoo {&d,&c,&b}; // OK!

for (auto animal: zoo) {
    animal->speak(); 
}
```

## Mulitple inheritance
In C++ a class can inherit from mulitple base classes.
The diamond problem:
How many `MotorVehicle` are there in a minibus?

```c++
class MotorVehical{ //... };
class Bus : public MotorVehicle { //... };
class Car: public MotorVehicle { //... };
class MiniBus : public Bus, public Car { //... };
```
+ A common base class is included multiple times
    - Multiple copies of member varibles
    - Members must be caccessed as Base::name to avoid ambiguity.
+ If `virtual` inheritance is not used!

### Virtual inheritance
Virtual inheritance: Derived classes share the base class instance. (The base class is only included once)
```c++
class MotorVehical{ //... };
class Bus : public virtual MotorVehicle { //... }; // NOTE VIRTUAL
class Car: public virtual MotorVehicle { //... };  // NOTE VIRTUAL
class MiniBus : public Bus, public Car { //... };
```
The *most derived class* (MiniBus) must call the *constructor of the grandparent* (MotorVehicle).

# Containers
## Sequences (Homogeneous)
+ `vector<T>`
+ `deque<T>`
+ `list<T>`

### Vector and deque
`deque<T>`: **D**ouble-**e**nded **que**ue.

| Function         | `vector` | `deque` | Return type |
|------------------|----------|---------|-------------|
| `clear()`        |   YES    |   YES   | `void`      |
| `size()`         |   YES    |   YES   | `size_t`    |
| `empty()`        |   YES    |   YES   | `void`      | 
| `push_back()`    |   YES    |   YES   | `void`      | 
| `pop_back()`     |   YES    |   YES   |  `void`     |
| `emplace_back()` |   YES    |   YES   | `void`      |
| `front()`        |   YES    |   YES   | `T&`        |
| `back()`         |   YES    |   YES   | `T&`        |
| `at()`           |   YES    |   YES   | `T&`        |
| `operator[]()`   |   YES    |   YES   | `T&`        |
| `assign()`       |   YES    |   YES   | `void`      | 
| `insert()`       |   YES    |   YES   | `void`      |
| `emplace()`      |   YES    |   YES   | `void`      |
| `resize()`       |   YES    |   YES   | `void`      |
| `reserve()`      |   YES    |   YES   | `void`      |
| `push_front()`   |   NO     |   YES   | `void`      |
| `pop_front()`    |   NO     |   YES   | `void`      |
| `emplace_front()`|   NO     |   YES   | `void`      |

**NOTE** The `void` return types of `pop` functions. If you want to get the elements at the front and remove it you need to first do `front()` followed by a `pop_front`!

The constructors and the function assign have three overloads:
1. fill: *n* elements with the same value.
    + `void assign (size_type n, const value_type& val);`
2. initializer list:
    + `void assign (initializer_list<value_type> il);`
3. range: copies the elements in the interval [first, last).
    + `void assign (InputIterator first, InputIterator last);`

Ex. 
```c++
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
int main() {
    // fill
    vector<int> l(10, 1);
    for(auto& i : l) {
        cout << i << " "; // 1 1 1 1 1 1 1 1 1 1
    }
    cout << endl;

    // init. list
    vector<int> v({1,2,3,4,5});
    for(auto& i : v) {
        cout << i << " "; // 1 2 3 4 5 
    }
    cout << endl;
    // iterator
    vector<int> q(v.begin(), v.end());
    for(auto& i : q) {
        cout << i << " "; // 1 2 3 4 5
    }
    cout << endl;
}
```

### List
`list<T>` is doubly linked list. 
If you want a simply linked list, use `forward_list<T>` which is only forwards iterable. You can still use `begin()` and `end()` though.

## Containers and resource management
+ Elements are *copied* into the container.
+ When an element is removed, it is *destroyed.**
+ The destructor of a container destorys all elements.
+ Usually a bad idea to store owning raw pointers in a container.
    - Requires explicit destruction of the elements.
    - *Use smart pointers*
+ Avoid making unnecessary copies
    - Use `emplace_back` instead of `push_back` of a temporary variable.
    - Use `reserve` before doing a known number of `push_back`.
    - Reuse capacity when possible
    - Call by `const  & ` as default.

## Sets and maps

|        Name |      Attributes                |
|-------------|--------------------------------|
|     map<K,V>| Unique keys                    |
|multimap<K,V>| Can contain duplicate keys     |
|     set<K>  | Unique keys                    |
|multiset<K,V>| Can contain duplicate keys     |

By default orders elements with `operator <`.
A custom comperator can be provided.

Ex.
```c++
template <class Key, class Compare = std::less<Key>>
class set {
    explicit set (const Compare& comp = Compare());
    //...
};
```
### Operations on sets and maps

| Function        | `std::map`      | `std::set`      | return type                |
|-----------------|-----------------|-----------------|----------------------------|
| `insert`        | YES             | YES             | `pair<iterator, bool>`     |
| `emplace`       | YES             | YES             | `void`                     |
| `operator[]`    | YES             | NO              | `T&`                       |
| `at`            | YES             | NO              | `T&`                       |
| `find`          | YES             | YES             | `iterator`                 |
| `count`         | YES             | YES             | `size_type`                |
| `erase`         | YES             | YES             | `void`                     |
| `clear`         | YES             | YES             | `void`                     |
| `size`          | YES             | YES             | `size_type`                |
| `empty`         | YES             | YES             | `bool`                     |                       
| `lower_bound`   | YES             | YES             | `iterator`                 |
| `upper_bound`   | YES             | YES             | `iterator`                 |
| `equal_range`   | YES             | YES             | `pair<iterator, iterator>` |

### unordered_map
There is also `std::unordered_map<T>` which is essentially just a hash map.

# Lambdas / anon. functions
Lambdas or anon. functions are useful for when you want to write function objects that are used seldomly or doesn't affect the internal state of the object but has to be used somewhere else, i.e. a comperator.
Lambdas are written in the following form:
```c++
// [capture] (params) -> return_type {body};
int x = 3;
auto lambda = [&x] (int i) -> int {
    x += i;
    return x;
};
int result = lambda(3);
cout << result << ": " << x << endl;  // 6: 6
```

As you could see the lambda is saved in a variable. But can also be written in-line, e.g. as a parameter for function.
```c++
vector<int> v = {2,4,l,2,8,6,7,5};
v.erase(std::remove_if(v.begin(), v.end(), [] (const int& i) { return i <= 5; }), v.end()); // remove_if returns an iterator
std::for_each(v.begin(), v.end(), [] (int& i) { i += 1;});
std::for_each(v.begin(), v.end(), [] (const int& i) { cout << i << " ";}); // 9 7 8
```
## Anatomy of a lambda
As mentioned above a lambda consists of three or four parts, the capture `[]`, the parameters `()`, the return type `-> type`, and the function body.

### Capture
The caputure part of the lambda "captures" variables available in the scope. They can either be captured by reference as in the example above, or by value with the added cost of copying. If you want to change the internal state of the current object you can also capture `this`.

### Params
The parameters to the lambda are different depending on where and how you use it. For example a call to sort would have two parameters at all times, which you have to beware of when you write the lambda. But you as the programmer can decide if you want to pass by reference or by value, and if you wish that the parameters should be `const`.

Both the following examples work, but one calls by copy, and the other calls by const and reference.
Call by copy:
```c++
vector<int> v = {1,2,3,4,5,6,7,8,9};
std::sort(v.begin(), v.end(), [] (int lhs, int rhs) { return lhs > rhs;}); // Sort in descending order.
std::for_each(v.begin(), v.end(), [] (const int& i ) {cout << i << " ";}); // 9 8 7 6 5 4 3 2 1
```
Call by reference with `const`:
```c++
vector<int> v = {1,2,3,4,5,6,7,8,9};
std::sort(v.begin(), v.end(), [] (const int& lhs, const int& rhs) { return lhs > rhs;}); // Sort in descending order.
std::for_each(v.begin(), v.end(), [] (const int& i ) {cout << i << " ";}); // 9 8 7 6 5 4 3 2 1
```
### Function body
Can be as many lines as you wish. :)

# Algorithms
The standard library has many built in algos that will simplify the life of the programmer especially when working with containers.

## finding/removing
The standard library has multiple functions for finding and removing content from containers, such as `find`, `find_if`, `remove`, and `remove_if`.

### `find` `remove`
`find` and `remove` takes two iterators as arguments, as well as a value to determine which element to find or remove.
Important to know is that the value that is sent as a parameter **HAS TO OVERRIDE THE `operator==`**. If you check the implementation for the remove and find it explicitly uses the `operator==` to determine if the value is the one to remove or find.
```c++
template <class ForwardIterator, class T>
ForwardIterator remove (ForwardIterator first, ForwardIterator last, const T& val){
  ForwardIterator result = first;
  while (first!=last) {
    if (!(*first == val)) {
      *result = move(*first);
      ++result;
    }
    ++first;
  }
  return result;
}
```
As you can see the find/remove function returns an iterator to the position of the removed/found element.

NOTE! That the length of the vector is **NOT** changed but the value is removed. This is best demonstrated through the following example:

```c++
vector<int> v = {1,2,3,4,5,6};
cout << v.size() << endl; // 6
std::remove(v.begin(), v.end(), 3);
cout << v.size() << endl; // 6
std::for_each(v.begin(), v.end(), [] (const int& i) {cout << i << " ";});
cout << endl;
std::remove(v.begin(), v.end(), 5);
cout << v.size() << endl; // 6
std::for_each(v.begin(), v.end(), [] (const int& i) {cout << i << " ";}); // 1 2 4 6 6 6
```
To solve this issue in the example above it is better to use a combination of `find`/`remove` and the `erase` function for the container.
```c++
vector<int> v = {1,2,3,4,5,6};
cout << v.size() << endl; // 6
auto iterator = std::remove(v.begin(), v.end(), 3);
v.erase(iterator);
cout << v.size() << endl; // 5
std::for_each(v.begin(), v.end(), [] (const int& i) {cout << i << " ";}); // 1 2 4 5 6
```

### `find_if` and `remove_if`
`find_if`/`remove_if` just like `remove`/`find` take two iterators as arguments as well as an additional lambda/function. The function/lambda describes how the element should be selected. 

Ex.
```c++
vector<int> v = {1,2,3,4,5,6};
v.erase(std::remove_if(v.begin(), v.end(), [] (int& i) {return i < 4;}), v.end());
std::for_each(v.begin(), v.end(), [] (const int& i) {cout << i << " ";}); // 4 5 6 
```
Just like `remove` and `find` doesn't have to power to alter the container. An additonal call to `vector.erase()` has to be done, like in the example above.

# Transform, copy_if, accumulate, and for_each
### `std::transform`
`std::transform` is the equivalent to map in many languages taking a "stream" of inputs and doing operations on those inputs.
The input to `transform` is three iterators, the first two is the range for the transform and the third being the start of the application of the function(?), and a function or a function object (functor).

```c++
vector<int> v = {1,2,3,4,5,6};
vector<int> v2 = {1,2,3,4,5,6};
struct Functor {
public:
    Functor(int x): x(x){};
    int operator()(int& i) { return i +=this->x;  }
private:
    int x;
};

auto lambda = [] (int& i) -> int { return i+=1; };
// With lambda
// NOTE! that this starts the transformation at the second element of v by moving the vector forward one position.
std::transform(++v.begin(), v.end(), ++v.begin(), lambda); 
std::for_each(v.begin(), v.end(), [](const int& i) {cout << i << " ";}); // 1 3 4 5 6 7
cout << endl;
std::transform(v2.begin(), v2.end(), v.begin(), Functor(3));
std::for_each(v2.begin(), v2.end(), [](const int& i) {cout << i << " ";}); // 4 5 6 7 8 9
```
### `copy_if`
`copy_if` is the equivalent to filter in many languages.
`copy_if` takes four arguments the beginning of the origin, the end of the origin, the beginning of the output, and a function that describes if the element should be copied.
```c++
vector<int> v = {1,2,3,4,5,6};
vector<int> v2;
v2.resize(v.size()); // NOTE! The output vector must have available space
std::copy_if(v.begin(), v.end(), v2.begin(), [&v2] (const int& i) { return i < 4;});
std::for_each(v2.begin(), v2.end(), [](const int& i) {cout << i << " ";}); // 1 2 3 0 0 0
cout << endl;
v2.erase(std::remove(v2.begin(), v2.end(), 0), v2.end());
std::for_each(v2.begin(), v2.end(), [](const int& i) {cout << i << " ";}); // 1 2 3
```
### Accumulate
`std::accumulate` is the equivalent to reduce in many other languages, and is defined in the `numeric` header and **NOT** in `algorithm`.
`std::accumulate` takes two iterators and a value that should be accumulated.

```c++
vector<int> v = {1,2,3,4,5,6};
auto res = std::accumulate(v.begin(), v.end(), 0);
cout << res << endl; // 21
```
Elements that should be accumulated has to implement the `operator+` for the relevant input.
```c++
class StringBuilder {
private:
    string s;
public:
    StringBuilder(string s = ""): s(s){};
    // Note that operator + has to be defined for the relevant input, which in this case is std::strings.
    StringBuilder& operator + (string& rhs){ s += rhs; return *this;};
    // to be able to print StringBuilder
    friend ostream& operator << (ostream& os, StringBuilder& sb);
};

ostream& operator << (ostream& os, StringBuilder& sb) {
    os << sb.s;
    return os;
}

int main () {
    vector<string> v = {"hello","there","General","Kenobi","!"};
    auto res = std::accumulate(v.begin(), v.end(), StringBuilder());
    cout << res << endl; // hellotheregeneralkenobi!
}
```
