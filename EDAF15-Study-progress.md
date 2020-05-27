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
### 1. If we wish to print the date of compilation of a file, how would you do that?
### Answer:
```c
printf(__DATE__);
```
### 2. What is the proper way to "comment out code" using the C preprocessor instead of comments and why?
### Answer:
Like this:

```c

#if 0
    char* someCode = "That won't run\n";
#endif
    char* someCode = "That will run\n";
```
Using the preprocessor is superior for the following reasons:
+ The comments can be nested.
+ They stand out from the rest of the source code and are recognizable as something that should be investigated.

### 3. What is the `#` operator, called the stringizer operator, and how can it be used?
### Answer:
The Stringizer operator takes a parameter that is replaced with a string literal constructed from the argument's tokens.
```c
#define W 124
#define xstr(a) (#a)
#define str(b) (xstr(b))

xstr(W) => "W"
str(w)  => "124"
```
### 4. Which storage classes does C have and what are they used for?
### Answer:
+ `static` : static storage
+ `register` : Tells the compiler that you would prefer to have this variable stored in a register. However optimizing compliers are better than the programmer at doing this so this is deprecated.
+ `typedef` : introduces a synonym for a type. E.g. `typedef long long ll;` or `typedef unsigned int uint;`
+ `extern` : Used to give a symbol external linkage, and split its definition and declaration.
Example:
```c
// This main will crash because var is declare but not defined anywhere.
extern int var;
int main(void)
{
    var = 10;
    return 0;
}
// This main will work if we assume that somefile.h has defined var somewhere.
#include "somefile.h"
extern int var;
int main(void){
    var = 10;
    return 0;
}
```
+ `_Thread_local_` : Gives the declared object thread storage duration and may only be used with objects that have static storage duration.
+ `auto` : Completely useless.

### 5. What is a designated initializer?
### Answer: 
Designated initializers are used to specify a particular array elemtn or struct/union member to be initialized by tyhe next expression:
```c
struct {
    int a;
    int b;
    int c;
} d = { .b = 1, 2 };
int e[] = { [8] = 3, 4 };
```
In the code above the struct will have value 1 for `b` and 2 for `c`.
The array `e` will have it's elements `e[8] = 3` and `e[9] = 4`.
It can also be used in code like such:
```c
typdef struct {
    char a;
    double b;
} type_t
int main(void)
{
    type_t c = {0}; // Both values set to 0.
    type_t d = {'a', 1.2f}; // Both values set respectively.

}
```

## Week 4.
### 1. Which are the five main steps in instruction execution on RISC processor?
### Answer:
1. Instruction fetch : Use the address in the PC and fetch the instruction at that address from RAM. Save the instruction fetched into the processor's instruction register. Increment the PC with four so that it can fetch the instruction after this one next time.
2. Instruction decode : Inspect the contents of the instruction register and determine the primary opcode, and possibly the extended opcode, and extract the register numbers of the source regsiter operandes and read the data of these registers. Other options can be to fetch a consant operand from the Instruction register.
3. Execute: Perform the operation specifed in opcode(s). In the case load-immediate instruction no poåeration other than copying form the instruction register.
4. Memory access: Read from or write to the RAM, if the instruction should do so.
5. Finally, if the instruction should save the result in a destionation register, that is done. GOTO 1.

### 2. In a five-stage pipeline of processor which can issue (i.e. start executing) one instruction every clock cycle, what is the idea of perfromance improvement over non-pipeline instruction execution?
### Answer:
Since the instruction is constant length (on a RISC chip) the five different steps above can be performed by five different parts of the CPU.The jobs of each part can be done concurrently allowing us to start a new instruction every clock cycle.
There are some restrictions which limit this can speed up computation. If an instruction want to read a register valuie that currently being updated by an earlier instruction, that value of the regiser cannot be read as normal since that would give obsolete value. Therre are two options for this problem:
+ More logic in the chip that can detect the situation and provide the new register value
+ The second instruction can wait.

Both techniques are used. If the value exists when it is needed, the first approcah is used but if does not, the other instruction _must_ wait. An unused slot in the pipeline is called a **pipeline stall**. 

## Week 5.
### 1. Which are the forms of locality?
### Answer:
1. Temporal locality : Address that is used once will most likely be used again soon.
2. Spatial locality : Address that is accessed at a point in memory will most likely use the data around it. (If _A_ is accessed it is likely that _A + 1_ will be as well)

### 2. What is meant by a cache block?
### Answer:
When a cache miss occurs instead of loading only one word, we can exploit spatial locality and read a block of data into the cache, i.e. a **cache block**.

### 3. A cache is divided into a number of sets, and when an address is searched all rows in a particular set are checked to see if if that row contains the searched address and needed data. What is cache calld if it is described as follows:
1. The cache has only one set
2. each set has four rows
3. The number of sets and rows are equal.
### Answer:
1. Fully associative cache.
2. (4-way) set-associative cache.
3. Direct-mapped cache.

### 4. When there are multiple rows in a set, are they serached in sequence or are the hardware address comparators duplicated so that they work in parallel?
### Answer:
They are duplicated and work in parallel.

### 5. What is the cache lobk size on LTH's POWER machine?
### Answer:
128 bytes.

### 6. Modern optimizing compilers use a representation which makes it relatively easy analyze which statment has modified a variable. What is this representation called?
### Answer:
Static Single Assignment form (SSA form)
### 7. What is the purpose of instruction scheduling?
### Answer:
Reorder the instruction so that they can be performed without interfering with each other (pipeline stalls), i.e. using the same registers.

## Week 6
### 1. On which format are signed integers almost always represented in C?
### Answer:
Twos-complement form.

### 2. Represent -2 using four bits.
### Answer:
To represent the negative number _-Y_ the number _2^n - Y_ is is stored in _n_ bits instead. Thus, the procedure to convert a negative number to its two's complement representation is to subtract its absolujte value from _2^n_.
Note that:
_2^n = 1 + Sum i = 0 -> i = n - 1 of 2^i_
is 1 plus the binary number represnt by _n_ ones. 

2 in base 2 is in 4 bits is `0010`, _1 + Sum i = 0 -> i = 4 - 1 of 2^i = 1 + (1 + 10 + 101) = 1 + (10 + 111) = 1 + (1111)_
So _1 + 1111 - 0010 = 1 + 1101 = 1110_
So -2 = 1110 in two's complement form
For practice reasons:
In 8 bits it would be:
_1 + 11111111 - 00000010 = 1 + 11111101 = 11111110_

### 3. What does arithmetic underflow mean?
Answer:
An exception when the rest of a calculation is smaller absolute value than the computer can actually represent in memory.
Overflow is the same thing but for large values.

### 4. What is the result of "dividing by arithmetic shift" when you divide _-1_ by _2_? Why is it wrong?
### Answer:
If were dealing with integers, the -0.5 is lost due to integer cut of rounding.


### 5. What is a subnormal floating point value?
### Answer:
When a value is larger than 0, but smaller than smallest representable floating point value able to be represented.

### 6. While it is obvious that it is the common case that should be optimized, how can you know which is the common case?
### Answer:
Either by working it out yourself if you know what your data is, or by running a profilers such as `gcov`, `operf`, etc. If that doesn't give more insight try running the program in simulator.

### 7. Suppose you need to make sure a pointer is aligned on a certain power of two. What does that mean and how can you do it?
### Answer:
It means that we want to have the pointers close to each other in memory so that it becomes faster to get to them, since they are aligned(?).
It can be done by first allocating a big block _p_ which has the size of 
????

## Week 7
### 1. When optimizing a program, what is the purpose of first developing a simpler, not optimized, and obviously correct reference implementation?
### Answer:
To keep and compare the correctness of the program in the future, also measure if your changes had any relevant impact at all.
### 2. What is SIMD-vectorization?
### Answer:
SIMD (Single Instruction Multiple Data) vectorization means that with a single instruction multiple data can be operated on by utilizing the special vector registers in the CPU.
For example:
```c
#define N (100)
int main(void)
{
    double a[N];
    int i;
    for (i = 0; i < N; ++i)
       a[i] *= 1.2f;
```
Can be vectorized since the operation(s) corresponding to `a[i] *= 1.2f;` can be performed on multiple elements at once (depending on the size of the vector register) and remove overhead from having multiple instructions.

### 3. How can you determine, efficiently if a number `x >= 1` is a power of 2?
### Answer:
If a positive integer is a power of 2 it only has one 1 and the rest zeros in its binary representation.
In C we can check this (inefficently) by:
```c
int is_power_of_two(unsigned int a)
{
    // check a != 0
    if(a == 0)
        return 0;
    else if (a & (a - 1) == 0) // Assume a is power of 2 then subtracting 1 from it will flip all bits and thus the result of the & will be 0
        return 1;
    else
        return 0;
        
}
```
Or efficiently (no branches):
```c
int is_power_of_two(unsigned int a)
{
    return (a != 0) && (a & (a - 1) == 0);
}
```

### 4. Which advantages and disadvantages have a free-list compared to using malloc and free for each allocation?
### Answer:
Advantages:
+ Less frees (instead of freeing put it in the freelist) 
+ Reuse memory. Things in the free list can be reused.
Disadvantages:  
+ Occupies memory while its alive, needs to have a check if there are objects in the free-list we have to check if we can reuse them first.

### 5. Which advantages and disadvantages have an arena compared to using `malloc` and `free` for each allocation?
### Answer:
Advantages:
+ Only one call to malloc and free.
Disadvantages:
+ No deallocation of any part of the data structure is permitted or possible, so it cannot be deallocated before every object in it has been used.


