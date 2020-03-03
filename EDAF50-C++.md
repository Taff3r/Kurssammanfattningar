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
## unique_pointer

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


