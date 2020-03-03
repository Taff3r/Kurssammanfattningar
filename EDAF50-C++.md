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


