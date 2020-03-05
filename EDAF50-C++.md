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
        int t = year*365 + month*12 + day;
        int o = d.year*365 + d.month*12 + d.day;
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








