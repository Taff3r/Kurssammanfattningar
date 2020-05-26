## Week 1
### 1. To print out "hello, world" from C program we need "import" the declreation of the function `printf`. How do we import a file in C and which file declraes `printf`?
### Answer:
We import `<stdio.h>` using the preprocessor directive `#include`.

### 2. How can we ask the compiler the size in bytes of a ceratin type variable?
### Answer:
We used the keyword `sizeof`.

### 3. Into which four segments ("memory areas") is the address space of a running program divied?
### Answer:
+ Text: Where machine code instructions are stored, together with other data which will not change. This segment is read only.
+ Data: This where variables with **static storage duration** are stored. Such as global variables and variables declared `static`.
+ Heap: This is where our "objects" are stored. These are manually allocated and deallocated.
+ Stack: This is where local variables are stored. Is also used to store parameters to functions and to keep track of return addresses.

### 4: A register is type of memory which is localed in processor and is the fastest type of memory. What is the purpose of the register called the program counter?
### Answer:
The program counter register holds the address of the next machine code instruction to execute. This register is updated automatically and usually is just incremented to hold the next machine instruction, but for jump instructions it is set to an address someplace else.

### 5: Both local variables and function's return address are stored in a so called called call frame. Why do we nmeed to store reutrn address of a function and in which of the four memory segments are call frames stored?
### Answer:
The call frames are stored on the stack. The functions return address needs to be stored so that the PC can take the value of the return address and continue where it left off.

### 6. Is a pointer simply a variable that contains a number?
### Answer:
Yes.

### 7. Consider a functions as `void f(int a[10000]);` Calling it with an array `int x[10000]` does not result in 10000 int elements to be copied. Why?
### Answer:
An array is just a pointer, and writing a function like `f` would only convert the argument to `int* a`.

### 8. Assume you wish to create an array and return it to the calling function. Why is it not possible to declare the array as variable length array or allocate memory for it using `alloca`?
### Answer:
Because arrays allocated with `alloca` are automatically deallocated when leaving the block that it was declared in.

### 9. How would you allocated memory for an array of `n int` elements and return to the calling function?
### Answer:
```c
int* allocArray(size_t n)
{
    int* ptr = malloc(n * sizeof(int));
    // OR
    // int* ptr = calloc(n, sizeof(int)); // If we want the array to be init with zeros.
    if (ptr != NULL)
        return ptr;
    
    printf("Out of memory!\n");
    exit(1); // Terminate program
}
```

## Week 2
### 1. Consider an array `int a[10]` and a pointer `int *p`. After the statement: `p = &a[2];` what does `p + 2` mean?
### Answer:
It means "address of `a[2]` + 2", that is to say `&a[4]`.

### 2. Continued from the previous question: What does p[2] mean?
### Answer:
The value of `a[4]`. The brackets are just syntax sugar for `*(p + 2)` so, `p[2] == *(p + 2) == a[4] == *(a + 4)`.

### 3. We also have `int *q = &a[5]`, what does q - p mean?
### Answer:
The signed distance of the memory address. In this case it would be 3.

### 4. How can you allocate memory for a matrix of `double` elemnts when the number of rows and cols is unknown at compile-time and you wish to be able to use e.g. `a[i][j]` notation?
### Answer:
Make 1 + i calls to `malloc` / `calloc` like this.
```c
double** a = malloc(i * sizeof(double*));
for (k = 0; k < i; ++k)
    a[k] = calloc(j, sizeof(double));
```

### 5. Continued from the prev. question: if you want to perform onle one call to `malloc`/`calloc`, how can you then solve the problem?
### Answer:
You can stil allocate a matrix, however you will not be able to use bracket notation.
Simply allocate i * j doubles, and then the value of row `r` col `c` is `a[r][c] = a[r * c + c];`

### 6. Which are the potential risk of using `realloc`? 
### Answer:
If there isn't sufficient memory to `realloc` to the original data will be lost.

### 7. A macro can have parameters. Why is it a bad idea to define a macro `square` as:
```c
square a    a*a
```
### Answer:
Because when it is expanded it will simply be put in place of the code and not take into account how the order of operations are done.
E.g. This will not produce the correct output (`1`).
```c
int k  = 100 / square(10); // Will expand to 100 / 10 * 10 => 100
```
Instead use paratheses, sometimes more than you want.
```
#define square(a) ((a) * (a))
```

## Week 3
### If we wish to print the date of compilation of a file, how would you do that?
### Answer:
```c
printf(__DATE__);
```
