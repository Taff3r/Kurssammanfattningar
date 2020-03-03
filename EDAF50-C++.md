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
An array has to be deletedk
```c++
char* pChar = new char;
char[]* string = new char[5];

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

### Destructors
Objects that own a resource should always implement a `destructor`. So when a smart pointer deletes itself it calls the destructor of that object. If the objects owns other pointers it is **important** that in the destructor deletes those resources. **Other wise we have a memory leak!**

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


