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








