## Stack Architectures
With stack architectures more compact code can be written. This is achieved by not having a operand in the instruction, thus using smaller instructions. The operand is instead implicit, and are put on the stack instead. For example multiplying 7 and 8. Is done by placing first 7 on the stack, followed by 8. Then the multiply instruction is read and the top two elements on the stack are multiplied and stored at the top of the stack. 


## Pipelined Computers
Hailing from the automotive industry pipelining means spliting the assembly of automoblies into smaller, faster steps.
A key part of pipelining is that the assembly always moves in one direction, forwards.

For computers if all steps are simple the implementation of these steps can be very efficient, allowing a high clock frequeny.
The steps performed for an operation in a computer are the following:

1. Instruction fetch    -   Read next instruction into processor.
2. Instruction decode   -   Figure out what to do.
3. Operand fetch        -   Get data from registers.
4. Execture             -   Perform an arithmetic operation.
5. Write back           -   Put result in a register.

Some of these steps can be performed concurrently, namely Instruction decode (2) and Operand fetch (3), if the instruction is always a fixed length these can be read at the same time.

### The Software Crisis and the Semantic Gap
In the 1960's hardware costs were huge compared with software costs. This however switched in the early 1970's and more and more complex software started to become painfully expensive.
Some people thought (wrong) that the solution was to design machines which would simplify compilation of high-level languages and a so called "semantic gap" was identified (utter nonsense).

For example polynomial evaluation and stack frame control which are very complicated instructions used in high level languages that couldn't be pipelined.

Because what ultimately decides the clock-frequency (speed) is the slowest part of the pipeline. So if the are complicated instructions that are hard or not able to be pipelined at all this makes it so that the clock-frequency can be high.
These instructions were also rarely used by compilers making most programs slow.

More reason for these complicated instruction sets were that the code size had to be smaller.

At the end of 1970's a group of researchers at IBM got free reign of any previous constraints that made sure the backwards compability was possible from older computers. 
What they developed was a computer with :
+ Load-store architecture.
+ No complex instructions that reduced the clock-frequency.
+ 16 general purpose registers (later changed to 32 register).
+ Intended to be used only with high level languages and an optimizing compiler.

This was the concept of RISC (Reduced Instruction Set Computer)

*In RISC having many specific instructions that are short is not an issue, and the clock-frequency can be kept high!*
*The problem with CISC is that having any instructions that are complicated to perform in hardware slows down the clock-frequency!*

## The PowerPC Architecture
+ There are 32 general purpose registers 32/64 bits, R0 means zero for some instructions.
+ 32 floating point register, 64 bits.
+ 32 vector registers, 128 bits.
+ A number of special purpose registers, such as for:
    - Storing loop iteratoin count to avoid i++ and i < n.
    - Function call return address.
+ Fixed point exception register XER, 32 bits
    - Three bits hold: summary overflow, overflow, and carry. The summary overfolow is set when overflow is set but only cleard explicitly by writing to XER.

### Power Registers
+ The *link register* (32/64 bits) holds the return addres for function calls and is written implicitly: `bl printf /* function call */`
+ The *count register* (32/64 bits) can be used to control loop termination, which is faster than using general purpose registers, compare, and branch. Only for one inner loop.
+ *Condition registers* (4 bits) can be used in if-statments to read if a comparison was negative, positive, or zero.

### Power Instruction Formats
An instruction format defines what the instrcution bits mean. The Power has several formats and the more commmonly used include:

* I-form: Eg for function calls
* B-form: For conditional branches.

### Power Instructions
The are hundereds of instructions, here are a few:
+ Compare instructions.
+ Branch instructions.
+ Arithmetic instructions.
+ Logical instrctuctions.
+ Memory Access instructions.
+ (Floating point instructions)
+ (Vector instructions)


#### Compare Instructions
Four integer compare instructions:
+ Signed compare, register - register.
+ Signed compare, register - sign-extended immediate. 
+ Unsigned compare, register - register.
+ Unsigned comapre, register - immediate.

The destination is condition register (any of the eight).
By default the assembler uses CR0 for integer compare.
By sign-extended is meant the most significant bit of the 16 bit constant is copied to positions 0..15 of a 32 bit word, and placing the 16 bit constant into positions 16..31.

#### Branch Instructions
??? (Skipped for some reason in lecture)

#### Arithmetic Instrcitons
Many arithmetic instructions _optionally_ can set the three first bits of the CR0 register (i.e. negative, positive, or zero).
In assembler, these are specfied witha dot and o as suffixes: `addo. 1,2,3` means R1 = R2 + R3; One of <,>,= and overflow are stored in CR0 bits 0..3.


#### Power Fuction Call Conventions
The functiion call conventions specify:
+ Which register is the stack pointer?
+ Which register is the fram pointer (if any)?
+ How should paramenters and return values be passed?
+ Where is the return value saved?

Basics:
The stack grows toward lower adresses. (Towards the heap)
Register R1 is the stack pointer and its value is always 16 byte aligned (the value in R1 is a multiple of 16).
Callee may destroy R0, R2 - R12, F0 - F13, V0 - V19, LR, CTR, CR0, CR1, CR5 - CR7.
Integer parameters are passed in R3-R10 and remaining parameters in are coptied to the _caller's_ stack frame.
return value are passed in R3.
Small struct/union parameters are copied to the callee as any other parameters.
For larger struct/unions the address is used and if it is modified in the called function it is copied there in order not to break the copy semantics for parameters in C/C++.


## Basics of digital circuits on a processor chip
+ *Clock*: a signal which oscillates between high and low values.
+ *Register* of width N bits: a storage element which stores the value on its input when the clock signal goes from low to high. A register is clocked.
+ *Gates*: and, or, xor, not. Not clocked.
+ *Combinational logic*: gates combined to ake up a more complex functions e.g. to add two numbers. Also not clocked.
+ Werner Diagam: Registers are drawn on vertical lines and combinational logic between the lines. 

Recall the stages in instruction execution
+ Fetch: read an instruction from memory.
+ Decode: interpret what the bits mean and read operands from register file
+ Execute: perfrom an ALU operation, or calculate a memory address.
+ Memory access: only for load and store instructions. 
+ Write back: write back result to a register.
(These five steps are an example. Some processor have 20 steps.)

Is it better to have a large amount of steps? As a fundemental idea it makes sense since the operations are smaller and thus leads to a higher clock-frequency. (Not the whole truth though)



## Superscalar processors
Superscalar processors are processors with multiple pipelines.
In superscalar processors we can start multiple instructions at the same clock cycle. (Power8 can start up to 10 instructions/cycle and process more than 200 instructions concurrently IN ONE CORE (it has ten cores))

There are three core pillars to a superscalar processor functioning.
+ Branch prediction: hardware fetches instructions from memory where it guesses the progam will go. _Usually_ they predict the right way. When a mispredicition is detected, all wrong-path instructionms must be makred as such.
+ Reorder buffer: every instrcutions is put in a FIFO queue and they may only update "state" (e.g. memory) if they reach the end of the FIFO and have not been killed.
+ Register renaming: a technique to remove output and anit-dependencies at the hardware level.

These three togethere make it possible to execute instructions speculatively. A speculatively executed instruction can modify a rename register but *not* memory. Ifiit is cancelled, the new reigster value in the rename register is simply not copied to the real register.


### Branch prediction
The processor has tables where previous brnach outcomes are stored.
When fetching an instruction at address A, the processorchecks the tables and decided wheter the next instruction to fetch is at A + 4 or an address stored in the table.
When "looking" at superscalar processor, one can see that it sometimes can start to fetch *and execute* isntructions in called function before the call instruction has executed!!!
Such instructions are executed speculatively and it must be easy for the hardware to cancle them if needed for some reason. (Not in this course, e.g. a pagefault occurs before the call).


### Reorder buffer
The Reorder buffer is a FIFO and controls that all isntrcitons finish in the program order (unless it is ceratin that they cannot "make troubles" a simple add cannot, but a store or conditional branch can).
When this FIFO is full no new instructions can be sent to the various functional units (integer ALU, floating point ALU, etc).
If an instruction is to be canccleed, the the data structure for the rename reigsters must be updated, so that no future instructions gets the value produced from a cancelled instruction.
Some instructions are so called serialized which measn they are slower, e.g. by letting all previous instructions leave the FIFO before starting. Eg extended add (with carry) and move to/from link or condition register can serialized.
### Register renaming
Anti and putput dependecies at the register level are not dependecies.
They exist becaus some isntrctions happend to use the same register number for different purposes.
Instructions with anti and output dependecies do not communicate data between them.
In a true dependence, one instrcutoon really need a value computed by some other instruction, so it must wait until the value has been computed.
Register renaming at the hardware level removes anti and output dependences.

Consider register renaming for the integer regsiters, called the general purpose register (GPR) on the Power.
There are 32 GPRs and e.g. 12 rename registers for these.
There is a data structure (in hardware, of course) which says in which rename register the most recent value of each GPR is.
When an instruction want to _read_ a register, e.g. R3, it checks the data structure to see if the normal R3 is up-to-date, or if the value is a rename reigster and which.
When an instruction want to write to a register, it asks for a new rename register, but if none is available the instruction must wait.
With this scheme we can have 12 instructions in the pipeline which modify integer registers.
Wheter they modify the same register or different integer registers does not matter.
What if an instrctuons want a value from a rename register, but that value is still being computed, i.e. not yet finished?
The a so called tag (or ticket) for that rename register is given to the instruction who want to read the register.
When the rename register is updated, the instrcutons with a tag waiting for that register can proceed.

*Not all registers are renamed.*
Typically on a Power, the integer, floating point, vector, and condition registers are renamed.
On some Power processors earlier than 8, the link register was not renamed.

## Cache Memories (Level 3)
One of the greatest inventions in recent computer history.
There is fundemental trade-off between speed and size of memory. A memory component is either fast and small or big and slow. (Or a compromise inbetween)
Programmers of course want the best of both worlds, both fast and big.
Without cache memories it could take several hundered clock cycles to read data from RAM.

Two observations where made about memory usage.
### First observation
The first observation is that programs usually access memory somewhat regularly, which is called _locality_.

*Temporal locality* (tidslokalitet) means that if a program has accessed a particular location _A_ in memory, it is likely it will access A again soon.

Examples of Temporal locality:
* The instructions in a loop are accesssed next iteration as well.
* The loop index variable is usually accessed frequently.
* The stack space is often accessed again when a new function is called. (since that space is reused.)
* An object is typically accessed for a while and the the progream is done with it.



*Spatial locality* (rumslokalitet) means that if a program has accessed a word at address _A_ in memory, it is likely it will soon access the word at address A+1.

Examples of Spatial locality:
* The instructions are accessed one after the other - until there is a branch.
* Elements of an array are often accessed one after the other.
* Often several variables in an object is accessed and if these are put close together (by the programmer) then there will be spatial locality.

### Exploiting Temporal locality:
What is needed is a small memory on the same chip as the processor.
If we describe our *hardware* in C, then a CPU could look like the following.
```c
typedef struct {
    int reg[32];
    int pc;
    struct {
        bool valid;
        int data;
        int address;
    } cache_array[8];
} cpu_t;
```

We have now a cache which can store eight popular words.
The cache array contains eight pairs of *data* and *address*.
There is also a boolean called valid which tells us whether the data and addresss are valid for that row.
Recall that on paper we can write question makrs but the machine can only write ones and zeroes and cannot see whether they make sesnes so a separate bit must tell wheter they mean anything useful.
Suppose the compiler has decided that a global variable X should be put at the address 293, or 0x125, or 0001 0010 0101.


When the program (or CPU) want to read variable X, it should check whether any of the eight rows has `valid = true` and `addresss = 293`.
If the CPU found one suc row (or, let's call it line), then the CPU can take the data from that line and avoid waiting for the slow memory!
We must call this event something: a *cache hit*.
It can save us 100 clock cycles.

#### Load instruction 
*In hardware all iterations are executed concurrently!!*
The openmp direction is here to amke you alerat on that this is _not_ a sequential loop.

```c
case LD:
    found = false;
    address = source1 + constant;
    #pragma omp parallel for
    for(i = 0 ; i < 8; i++){
        if (cache_array[i].valid &&
            cache_array[i].address == address) {
            data = cache_array[i].data;
            found = true;
            break;
        }

    }
```

#### Cache replacement
If data was found in the cache we use that otherwise we need to read from RAM and write what we found to the cache.
We need to select one line.
If there is one line with `valid = false` then we select that one.
Otherwise, for now, we take a random line (row).
If the row we selected had valid data, we need to copy the old data contents to memory (otherwise, it's lost).
Then we read our data from memory.
The we write our data into the selected row, set the address to our address and set valid to true.

Example C-code:

```c
if (!found) {
    i = select_row();
    if (cache_array[i].valid) // save old data to memory.
        memory[cache[array[i].address] = cache_array[i].data;
   
    // read our data from memory.
    data = memory[address];
    
    // save our data in the cache
    cache_array[i].data = data;
    cache_array[i].address = address;
    cache_array[i].valid = true;
}
```

*The process is similar for a Store*
```c
case ST:
    found = false;
    address = source2 + constant;
    data = source!;
    #pragma omp parallel for
    for (i = 0; i < 8; i++) {
        if (cache_array[i].valid &&
                cache_array[i].address == address){
            cache_array[i].data = data;
            found = true;
            break;
        }
    }

    if (found) 
        break;

    i = select_row();
    if(cache_array[i].valid)
        memory[cache_array[i].address] = cache_array[i].data;
    cache_array[i].data    = data;
    cache_array[i].address = address;
    cache_array[i].valid   = valid;
```
Next time we want to read or write that variable it is likely that it will be found in the cache.

#### The Loop - isn't it slow?
No! Because it doesn't exist!
It only exists in the software model of the hardware.
Recall: *in hardware the loop is run in parallell.*
In our case, there are eight so called *comparators* which compare the address requested with address in its row says *"here!"* if the addreses are equal and the valid bit is true.

### A look at our cache
Our cache does not exploit spatial locality, yet.
Instructions may also be put in the cache.
Hit rate is the fraction of hits in the cache.
Let us test it on the factorial program.

|#rows | reads | read hits | writes | write hits | hit rate (%)|
|------|-------|-----------|--------|------------|-------------|
|8     |77     |21         |11      |0           |23.9         |
|16    |77     |36         |11      |0           |40.9         |
|32    |77     |50         |11      |0           |56.8         |
|64    |77     |50         |11      |0           |56.8         |
|128   |77     |50         |11      |0           |56.8         |

As seen in table:
* All writes always miss - the factorial program writes to anew places on the stack.
* The reads benefit from a larger cache since then what `fac(5)` and `fac(4)` saved on the stack will remain in the cahce when they later readthe saved parameter and return values.
* The 27 read misses are due to instruction which are fetched for the first time.

## Cache associativeity (Level 4)
Our cache is very small, only a half KB. Usually the cache clossets to the process, called the L1 cache is 32KB or 64KB.
Having 128 comparators might be feasible but hundereds of them is too much. That is a problem we must address.
It is much better read and write multiple words from/to memory rather than only one at a time. This we will also address.

In our cache, a word can be put in any row in the cache.
That means every row must be checked to see if the address matches.
Our cache is called a fully-associative cache. Theses are expensive.
If there is a function (in hardware) which maps an address to a particular row, then we only need one comparator, since there is only one row to look in. That is called as *direct-mapped cache.* (kinda like a hash-table?)
In a direct-mapped cache we can use the least significant bits of the address as the function.
Why should we not use the most significant bits as the function instead?
If we use the MSB's the result of the function will have a larger probability of having the same result. (Compare to using a hash-table with the same input)

The purpose is to avoid so many comparators.
In the C code the loop will disappear.
If the number of row is the cache is a power of two we can do as follows _instead of having a loop:_

```c
i = address & (CACHE_ROWS - 1);
if (cache_array[i].valid
    && cache_array[i].address == address)
    data = cache_array[i].data;
    // etc as in LD: above
```

In direct mapped cache, we can be unlucky and having two frequently used utems which are mapped to the same row in the cache which will result in many cache misses when they replace each other.
A compromise is so called *N-way asssociative cache.*
Now we group the cache row into set, where each set has N rows. 
The number of sets, `CACHE_SETS = CACHE_ROWS / N`.
An address is now mapped to a set and within its set, the address can be put in any of the N rows.
N comparators are needed now, and typical values of N is 2, 4, or 8.

How accessing data in an N-way associative cache looks like for our C-computer/cpu:


```c
i = address & (cache_sets - 1);
for (j = 0; j < N; j++) {
    if (cache_array[i][j].valid
            && cache_array[i][j].addresss == address) {
        data = cache_array[i][j].data;
        found = true;
        break;
    }
}
```
In a fully assoicative cache, `CACHE_SETS = 1`
In a direct-mapped cache, N = 1.

### Exploiting Spatial Locality (Level 4)
So far we have only transferred one word between the cache and the memory.
It is more efficitnet if mulitple words, say 8, 16, or 32 words transferred at a time.
The Power8 at LTH transfers 128 bytes at a time.
Assume instead that our cache block size is 8 words.
Then we can eg. fetch eight instructions at a time.
Since we store 8 consecutive words from memory in a cache row, we only need, of course, to know the addres of the first word in the block.

#### Cache Block Number

We can now vierw memory as an array, not of words, but of cache blocks.
When the cache block size is eight words (or 2^3 words) we get the cache block number of a word by dividing the word number by eight.
Alternatively we shift the word number, ie the address, to the right by three, ie, we throw the last three bits of address away.
The number of words in a cache block is called the `BLOCK_SIZE`.
Acctually the `BLOCK_SIZE` is the number of bytes but we simplify the presentation and only consider words.

C-code:

```c
block_num = address / BLOCK_SIZE;
i = block_num & (CACHE_SETS - 1);
for (j = 0 ; j < N ; j++) {
    if (cache_array[i][j].valid 
            && cache_array[i][j].block_num === block_num) {
        k = address & (BLOCK_SIZE - 1);
        data = cache_array[i][j].data[k];
        found = true;
        break;
    }
}
```
### Cache Levels and Matrix Multiplication (Level 3)
Caches are divided into different levels (L1, L2, etc.). The closer they are to the pipeline the closer the lower level it has. (L1 is closer to pipeline.)
The caches are also sometimes (L1 can be, while L2 is not, or none) divided into two different caches, one for instructions and for data. The reason is that data can read/written while isntrcutions are only fetched. Making it possible to optimize for reading and writing for the data cache. It also makes it possible to access both caches concurrently.


## The C Preprocessor (Level 3)
The C preprocessor has several directives.

### Predefined Macros
A macro is an indentifier such that when the preprocessor "sees" this definition it replaces it with what it was defined as. (A text replacement)

Some standard macros are:
+ __FILE__ : Expands to the source file name.
+ __LINE__ : Expands to the current line number.
+ __DATE__ : Expands to the date of translation.
+ __TIME__ : Expands to the time of translation.
+ __STDC__ : Expands to 1 if the implementation is conforming.
+ __STDC_HOSTED__ : Expands to 1 if the implmentation is hosted, and to 0 if it is free-standing. 
+ __STDC_VERSION__ : Expands to 199901L. (For C99)

Some implmentation defined macros:
+ __STDC_IEC_559__ : Expands to 1 if IEC60559/IEEE 754 is supported (except complex arithmetic).
+ __STDC_IEC_559_COMPLEX__ : Expands to 1 if complex arithmetic in IEC 60559/IEE 754 is supported.
+ __STDC_ISO_10646__ : Expands to an integer `yyyymmL` to indicte which values of `wchar_t` are supported.
+ __STDC_IEC_559__ : Expands to 1 if IEC60559/IEEE 754 is supported (except complex arithmetic)
*If a predefined macro is undefined then behaviour is undefined.*


### Defining Macros
+ No whitespace between macro name and left parenthesis in function-like macro.
+ A fencing-like macro not followed by left parenthesis is not expanded.

Ex. 
```c
#define obj (a) a+1
#define bad(a)  a+1
#define good(a) (a+1)

obj(3)       => (a) a+1(3)
bad(3)*10    => 3+1*10
good(3)*10   => (3+1)*10
(good)(3)*10 => (good)(3)*10
```

### Conditional Inclusion
Conditionally include code in source if a preprocessor "variable" is defined.
```c
#define DEBUG

#ifdef DEBUG
    printf("here we go: %s %d\n", __FILE__, __LINE__);
#endif

#ifndef DEBUG
#endif

#if expr1
#elif expr2
#elif expr3
#else
#endif
```

### More directives
```c
#define DEBUG 12
#define DEBUG 13    // invalid: cannot redefine a macro
#undef DEBUG
#define DEBUG 13    // OK. undefined first

#line 9999 "a.c"    // will set __LINE__ and __FILE__

#ifndef __STDC__
#error this will not compile with a pre-ANSI compiler!
#endif

#pragma directive from user to compiler
_Pragma("directive fromuser to compiler") // These two lines are equivalent.
```

### `#` and `##` operators (Level 5)
Operator # must preced a macro parameter and it expands to a string.
```c
#define xstr(a) #a
#define str(b)  xstr(b)
#define c       12

xstr(c)  =>  "c"
str(c)   =>  "12"

#define fatal(expr) { \
    fprintf(stderr, "%s line %d in \"%s\": fatal error %s = %d\n", \
    __FILE__, __LINE__, __func__, #expr, expr); exit(1); }
int x = 2;
fatal(x); => prog-015.c line 15 in "main": fatal error x = 2
```
Operator `##` concatenates the tokens to the left and right.
```c
#define name(id, type) id##type
name(x,int) => xint

#define a  x ## y
#define xy 12
int b = a; // init b to 12;
```


## Writing safe macros (Level 3)
Sometime it is convenient to have a variable number of arguments to a function-like macro, eg. when using printf.
Without `__VA_ARGS__`, the number of arguments must match the number of parameters.

Ex.
```c
#ifdef DEBUG
#define pr(...) fprintf(stderr, __VA__ARGS);
#else
#define pr(...) /* do nothing */
#endif
int x = 1, y = 3;
pr("x = %d, y = %d\n", x, y); => x = 1, y = 3
```

### Macros can improve performance
Since macros are expanded in the called function they eliminate the overhead of calling functions.
Macros can cause problems however:
```c
#define square(a)  a*a
x = 100 / square(10)  => 100 / 10 * 10
```

Use parentheses:
```c
#define square (a)   ((a)*(a))
y  = square(cos(x)) // valid but slow
z  = square(++y)    // wrong
```
Not the `cos` function is called twice
Modifying `y` twice is wrong.

### Macros with statements
Suppose we want to swap the values of two variables using a macro:
```c
#define SWAP(a,b)   tmp=a; a = b; b = tmp;

if(a < b)
    SWAP(a,b);
```
What happens?
How about:
```c
#define SWAP(a,b) {int tmp = a; a = b; b = tmp;}

if(a < b)
    SWAP(a,b);
else
    printf("syntax error!\n");
```
A compound statement cannot be floowed by a semicolon.
Neither of above functions correctly.
+ First one expands to multiple lines which makes the first only perform `tmp=a;`
+ Second one has has an extra `;` followed by a block which is incorrect syntax.
We can instead do as follows:
```c
#define SWAP(a,b) do {int tmp = a; a = b; b = tmp;} while(0) // NOTE missing ; (Not necessary since we end SWAP with ;)
```
This macro will solve both of the previous problems.


## Statements (Level 3)

There are several statements in C.
+ Labeled statements
+ Compund statements
+ Expression and null statements
+ Selection statements
+ Iteration statements
+ Jump statements

#### Labeled statements
Labels i.e. targets of `goto` statements.
Integer constant case statements in a switch.
The default statement which a switch will jump to if no case matches.

#### Compound statement
A compound statement, a block, can conatin a sequence of statements and declarations.
For instance:
```c
int main(void)
{
    int a;
    a = 1;
    int b;
    b = 2;
}
```

Mixing declarations and statements comes from c++ where some objects declared as local variables need this.
In C there is no need to do this, and main reason is simply: "it's ugly".

The following is cleaner:
```c
int main(void)
{
    int a;
    int b;

    a = 1;
    b = 2;
}
```

#### Expression and null statements
Most statements are expression statements, including assignements.
A `null` statement does nothing and consists only of a semicolon.
Null statements are used at end of blocks to avoid syntax errors.
```c
int main(void)
{
    /* ... */
    if (p == NULL)
        goto cleanup;

    /* ... */ 

    cleanup:
        ;
}
```

#### Selection statements (if and switch)
The controlling expression in a switch must be an integer.
If there are initializations in the compound block of a switch they are not executed.
```c
switch (a) {
    int b = 10;
case 1:
    printf("a is a one\n");
    a = b; // invalid. b not defined.
           // falls through to case 2.
case 2: printf("a is two\n");
        break;
default:
    printf("hello from default\n");
}
```

#### Iteration statements
Three loops:
+ for
+ while
+ do-while

A for-loop can have declaration statement:
```c
for (int i = 0; i < N; ++i)
    f(i);
```

This was partly introduced to C due to c++ already had it and partly to a false assumption that optimizing compilers would be helped by having the declaration close to the for-loop. Which is nonsense.

#### New in C11: exact rules for optimizing away loops
Consider the following loop:
```c
int i;
unsigned b = 0;
for (i = 1; i; b += 1)
    ;
abort();
```
Previously there were no rules regarding whether compilers are allowed to optimize away loops which never terminate and do not affect output by themselves.
C11 says compilers may optimize away loops if the do not access atomic or `volatile` objects, perform I/O, or have a constant nonzero termination condition, e.g. while(1) {} must stay.


## Writing portable C code (Level 3)
Portable = source code should be able to compile and run correctly on any computer.

+ Avoid undefined behaviour.
+ Write code with implemenatation-defined or unspecified behaviour only when doing so cannot affect the obeservable behaviour of your program.
+ Avoid platform-specific system calls - stick to the standard C library if possible.
+ Do not exceed minimum compiler limits, eg number of parameters etc. (This is mostly machine-generated C).
+ Appendix J of the C standard has information on portability issues. Most of them are concerned with standard C library.

### Examples of unspecificed behaviour 
+ Wheter string literals share memory.
+ The order in which operands of eg add are evaluated.
+ Wheter `f()` or `g()` is called first in: `fun(f(), g());`
+ Wheter `errno` is a macro or identifier with external linkage.
+ The order in which `#` and `##` are evalutaed during macro expansion.
+ Which of two elements which compare equal is matched by `bsearch`.
+ The order of two elements which compare equal when sorted by `qsort`. 
+ The resulting value at an overflow when converting a floating-point value to an integer.
+ Wheter the conversion of non-integer floating point value to an integer raise the "inexact" exception.
+ The order of side-effects dring initialization, eg it is not specified whether `f()` or `g()` will be called first below.
```c
int main() 
{
    int a[] = {f(), g()};
}
```

### Examples of undefined behaviour
+ A "shall" or "shall not" requirement which appears outside a constraint is violated.
+ A filed in a comment `/* comment.`
+ An identifer is first declared as extern and later as static.
+ An invaliud pointer is used:
```c
int* fun()
{
    int a;
    return &a; // This pointer must not be used.
}
```
+ Conversion to or from an integer which cannot be represented (also for conversion from floating-point to an unsigned).
+ When a program attempts to modify a string literal:
```c
char* s = "hello, world";
s[0] = 'H'; // may crash.
```
+ When an object is modified multiple time between two seqeunce points.
```c
i = ++i + i++;
```
+ `/` or `%` with second operand being zero.

### Examples of Implementation-Defined behaviour
+ The number of bits in a `char`.
+ Whether a `char` is signed or unsigned.
+ How integer numbers are represented: not necessarilty two's complement. (but most of the world assumes that so you should too)
+ Where to serach for `#include <header.h>` files. In UNIX, use the switch `-Idir` to look in the directory `dir`.
+ Endianness. Check on which format the data is stored when reading binary data using `fread`.

## Inline functions (Level 5)
Inline functions is an alternative to using preprocessor macros.
Inlining a function means copying the statements of a function into the calling functions instead of doing the call.
This can be done automatically by good compilers and should *NOT* be done by programmers (in Skeppstedt's opinion).
With C99 the keyword inline was introduced to C which can be used to give the compiler a _hint_ that it might be a good idea to inline a function.
Since good compilers can inline parts of a function automatically - and even copy rarely used parts of a funtction to some other place in memory iti is much much better to let the compiler take care of this.
Use `inline` only if you use a poor compiler.


### Linkage and inline functions
Recall: external linkage means an identifier is accessible from other files.
A funcion with internal linkage, i.e. declared with `static` can always be inlined but function with external linkage have restrictions:
+ An inline function with external linkage may not define modifiable data with static storage duration.
+ An inline function with external linkage may not reference any identifier with internal linkage.

What do these mean and why do we need these restrictions?

First restriction:
```c
extern inline int f(void)
{
    static int x;
    static const int a[] = {1, 2, 3};
    return ++x;
}
```
Restriction: an inline function with external linkage is not allowed to declare modifiable data with static storage duration.
Since copties of `f` inlined in different files will use different instances of `x` is forbidden.
The constant array is OK.

Second restriction:

```c
static in g(void)
{
    return 1;
}

extern inline int f(void)
{
    return g();
}
```
Restriction: an inline function with external linkage is not allowed to access and identifier with internal linkage.
When `f` is inlined in some file, it will use the available function `g` but then different files can have different functions `g`.

#### A warning
The `gcc` compiler supported in `inline` function specifier before it was added to the C standard.
Unfortunately, `gcc` uses slightly non-standard semantics for `inline`.
A simple rule which works both in ISO C and with gcc is to declare inline functions in header files such as:
```c
#ifndef max_h
#define max_h

static inline int max (int a, int b)
{
    return a >= b ? a : b;
}

#endif
```

## The C Library (Level 3 and 5 respecitvly)
There are 24 header files in C99 and 29 in C11.
Here are some of the more important header files.

### <assert.h>
To check that your assumptions hold during execution, you can do as follows:
```c
#include <assert.h>
void insert_first(list_t** list, void* data)
{
    (assert *list != NULL);
    /* ... */
}
```
It is useful uring development and can used for consistency checks.
Compiling `cc -DNDEBUG` will disable the test.
Therefore don't do:
`assert((fp = fopen(name, "r")) != NULL);`

If `NDEBUG` is not defined, the expression is evaluated, and if it nonzero, nothing happens.
If the expression is false, an error message is pringed and the `abort` function is called.
Suppose you want to check that a pointer is 8 bytes:
```c
assert(sizeof(void*) == 8);
```
How can you check that duing compilation?

*DON'T* do this:
```c
#if sizeof(void*) != 8
#error the program assusmes a pointer is 8 bytes.
#endif
```
Why?
The preprocessor does not regonize the reserved word `sizeof`.A

Instead use static assertion.

C11 has a new construct for it called `_Static_assert`, but we can easily deine a macro.
The idea is:
```c
int array[sizeof(void*) == 8 ? 1: -1];
```

If the expression is false, we would declare an array with -1 elements which the compiler must complain about.
To avoid:
+ Actually declaring an array and waste memeory,
+ having to invent a different array name every time
We declare an array typedef (wastes no memory) and uses token concatenation (`##`) to make the line number part of the name.
Like this:
```c
#define PASTE(a,b)  a##b
#define EXPAND(a,b) PASTE(a,b)
#define STATIC_ASSERT(expr) typedef char EXPAND \
        (failed_static_assertion_in_lin, __LINE__) \
        [(expr) ? 1 : -1]
// When compiled on 64 bit machine:
STATIC_ASSERT(sizeof(int) == sizeof(void*)); // => a.c:7: error: size of array 'failed_static_assertion_in_line7' is negative.
```

### `<ctype.h>` (Level 3)
<ctype.h> contains classification functions such as `isdigit`.
The take an int parameter and returna nonzero value to indicate truth.
It is wrong to write:
```c
if (isdigit(c) == 1)
    /* ... */
Since the return value equally well could be 2 if `c` is a digit.
```

### `errno` / Exceptions (Level 3)
There are exceptions in C, but are not like the ones in Java.
Here they describe low-level exceptions that are related to floating-point arithmetic.
`<fenv.h>` defines macros for exceptions:
+ `FE_DIVBYZERO`
+ `FE_INEXACT`
+ `FE_INVALID`
+ `FE_OVERFLOW`
+ `FE_UNDERFLOW`
+ `FE_DOWNWARD`
+ `FE_TONEAREST`
+ `FE_TOWARDZERO`
+ `FE_UPWARD`

The exceptions can be set both by hardware and software.
When a math function detects an invalid input argument it should set the `FE_INVALID` bit in the processor's floating point status register.
There are function for fetching a copy of the floating point status register.
There are functions for fetching a copy of the floating point status register and for testing and cleraing bits, and other ooperations.

C has traditionally stored arror codes in variable called `errno`.
The are three standard errors:
+ `EDOM`
+ `ERANGE`
+ `EILSEQ`

The first two refer to math errors: an argument was not in the domain of the function and the return value could not represent in the range of the return type.
The `EILSEQ` us used with an invalid multibyte character sequence.
Operating sysytems define others such as:
+ `ENONENT` for "No such file or directory".
+ `EPERM` for "Permission denied".

### Using `errno`
We should set `errno` to zero before any call which might fail such as opening or removing a file and some math functions.
For example:
```c
#include <errno.h>
#include <stdio.h>
int main(void)
{
    errno = 0;
    if(remove("/") == -1)
        perror("cannot remove \"/\"");
}
```

`errno` behaves as if it was declared a global variable `int errno;`.
For multithreaded prorams this doesn't work very well - due to data-races.
Each thread gets its own copy of `errno` and this is typically implemented as:
```c
int* __get_errno_for_current_thread(void)
{
    return &current_thread->errno;
}

#define errno(*__get_errno_for_current_thread())
```

Then we can use it as:
```c
errno = 0;
/* .. */
```

With C11 we can instead delcare `errno` using:
__Thread_local int errno;
This way each thread gets its own copy of `errno`.

`errno` is intended for use by system libraries such as the API's for performing system calls and Pthread libraries.
System calls are special function calls provided by the operating system which means Windows has one set of system calls and UNIX,
including MacOS X, Linux, and AIX, have other sets.
To report erros form your own libraries, it is often a good idea to define an enum with different error codes.


#### `<math.h>`
Compile with -lm at the end of the command: `gcc a.c -lm`
Traditionally errno is used but C99 allows math exception to be tested in a different way.
We ned to check which way the library report math erros using `math_errhandling`.
```c
errno = 0;
sqrt(-1);
if (math_errhandling & MATH_ERRNO)
    /* ... */
if (math_errhandling & MATH_ERREXCEPT)
    /* ... */
```

Math erros reported with `errno`:
```
if (math_errhandling & MATH_ERRNO)
    if (errno == EDOM)
        puts("EDOM");
```

Math errors reported as exceptions:
```c
if (math_errhandling & MATH_ERREXCEPT)
    except = fetestexcept(FE_ALL_EXCEPT);
    if (except & FE_INVALID)
        puts("FE_INVALID");
```

### `<inttypes.h> and <stdint.h>` (Level 3)
`<inttypes.h>` declares macros which are string that can be used.
For example:
```c
#include <inttypes.h>
int32_t a;
printf("a = %" PRId32 " \n", a);
```

`<inttypes.h>` includes `<stdint.h>`.
Strictly speaking this also not portable isnce it is implemenatation define whetere there is an int32_t but if there is, this how to print it.
For instance a DSP-processor with 24-bit int may not have `int32_t`.


### `<setjmp.h>` (Level 4)
To jump to a label `L` we use `goto L;`
In C we can also jump fron one function to another.
Consider:
```c
void g(void) { /* ... */ }
void f(void) { g(); }

int main(void) 
{
    /* ... */
    f();
}
```
Usually `g` retruns to `f` which returns to `main`.
If we wish we can return from `g` directly to `main`.
Instead of `return` we use `longjmp`.
`longjmp` has an ever worse reputation than `goto` but can be useful.

#### What is the context of an executing thread?
+ Program counter (PC)
+ Registers
+ To make a jump to a function _f_, that function must already have an allocated stack frame and its program counter and register must have been saved.
+ Thus e.g. `main` cannot jump into the middle of any function - a call to the jumped-to function must already be active ush as the call to _f_ above.
+ There is type jmp_buf in which the PC and registers are saved.
+ A jump preformed by loading all registers and finaly the PC form such `jmp_buf` variable.

Typical usage of `longmjp`:
```c
#include <setjmp.h>
jmp_buf buf;

int main(void) 
{
    switch(setjmp(buf)){
    case 0: /* initialization. */ break;
    case 1: /* from longjmp */ break;
    }

    /* ... */
    g();
}

void g(void)
{
    /* ... */
    if (must_stop())
        longjmp(buf, 1);
}
```
Remarks about long jumps:
+ Almost always non-local jumps are not needed.
+ In a chess program which has found a winning move it can be appropriate to terminate a deep recursive search using `longjmp`.
+ Functions with non-local jumps are **very** annothing to optimizing compilers and often result in slower code.

### `<signal.h>`
A signal is a way of notifying a running program that something has happend (usually something bad).

C standard signals:
| Signal | Example cause           | Default Effect        |
| ------ | ----------------------- | --------------------- |
| SIGABRT| `abort()`               | Terminate the process |
| SIGFPE | implemation defined     | Terminate the process |
| SIGILL | illegal instructuion    | Terminate the process |
| SIGABRT| `abort()`               | Terminate the process |
| SIGINT | CTRL+C                  | Terminate the process |
| SIGSEGV| invalid address         | Terminate the process |
| SIGTERM| kill <pid>              | Terminate the process |

UNIX-specifc singals:
| Signal | Example cause                  | Default Effect        |
| ------ | ------------------------------ | --------------------- |
| SIGSTOP| CTRL+Z                         | Stop the process      |
| SIGSTOP| kill -SIGTOP <pid>             | Stop the process      |
| SIGCONT| kill -SIGCONT <pid>            | Resume the process    |
| SIGBUS | eg non-aligned memory access   | Terminate the process |
| SIGKILL| kill -SIGKILL <pid>            | Terminate the process |
| SIGKILL| kill -9 <pid>                  | Terminate the process |


Common use:
To get informed about a signal, sent from the OS, we must register a so called signal handler.
A signal handler is simply a function that the operating system runs for us.
If we have not regsitered a signal handler before a signal is received our program is usually reminated, i.e. that is the default action.
To register a signal handler `catch_ctrl_c` for SIGINT we can do:
```c
#include <signal.h>
void catch_ctrl_c(int s) { /*... */ }
int main(void)
{
    signal(SIGINT, catch_ctrl_c) ; for(;;);
}
```

The signal function tells the OS which function to call instead of terminating our program.
The function `signal` returns the previously registerd function for a particular signal number.
The declaration of the `signal` is perhaps confusing to read:
```c
void (*signal(int signum, void(*func)(int)))(int);
```
The two parameters to signal are `signum` and `func`.
The `*` before signal is there due to the return value is a pointer (to a function).
Since the same function can be signal handler for different signals, the `int` paramter of the signal handler specifies which signal occurred.

When an event happens which triggers a signal, the OS blocks addtional instances of the same signal to avoid having the signal handler being invoked multiple times for the same signal.
This block is removed when the signal handler returns to OS.
After that, the OS will let program resume execution.
What happens if the singal handler instead of returning makes a `longjmp`?
Ths signal will remain block sine the OS still htinsk the signal handler has not returned.


### `strtol` and `strtok` (`<string.h>`) (Level 3)
To convert a number iun string to an integer the function `strtol` is useful.
It takes three parameters:
+ A pointer to a string: `char* s`
+ An optional pointer to a pointer to a string: `char** end` 
+ The base, 2-36 or zeor and the the base if inferred from the string.

The function sets `*end` to point to the first character after number - unless `end` is a null pointer.
For example:
```c
int a;
char* end;

a = strtol("119", &end, 2);
```
`a` is set to 3 and `end` to point to the 9.


To split a stirng into parts, called tokens, the function `strtok` can be used.
It is used in two phases:
1. First two parameters are provided:
```c
char* s;
char a[] = "a string. hi: there";
char* sep = " :." // NOTE whitespace.

s = strtok(a, sep);
```
    + The first parameter **must be modifiable**.
    + The second parameter contains a set of characters which are used to separate tokens.
2. If the previous parameter is `null`, search continuse in the previously used string.

Example:
```c
char* s;
char a[] = "a string. hi: there";
char* sep = " :." // NOTE whitespace.

s = strtok(a, sep);
while(s != NULL) {
    printf("%s", s);
    s = strtok(NULL, sep);
}
```
The output will be `a string hi there`
The returned string assigned to `s` is null-terminated!
That means strtok modifies the frist non-null parameter which therfore must be modifiable.
Using `char* s = "hello there"`; may result in a read only string!


### Sorting array of `int` using `qsort` (Level 4)
+ An array (aka pointer to the first element)
+ number of elements
+ size of each element
+ a comparison fnction
```c
int compare (const void* ap, const void* bp)
{
    const int* a = ap;
    const int* b = bp;
    // return *a - *b;
    if (*a > *b)
        return 1;
    else if(*a < *b)
        return -1;
    else
        return 0;
}
```

## Buffer overflows (Level 3)
A buffer overflow means array index out-of-boiund errors.
Checking that an array index is within the array bounds is not in C, as it is in Java.
The checking is only usefor programs with bugs.
To avoid such error, the following simple rule is sufficient:
**DON'T TRUST UNTRUSTED DATA.** 
In other words, make a sanity check for all input, and use range checking library functions.
When there is a risk for overflow: check it explicitly.
For C: make the calculation (how depends on the type).
Java does also not report errors on overflow (and connot check it for floting point values).

### An example `sprintf` and `snprintf`
Both function behave as printf bt put their output in a buffer pointed to by the first parameter.
The output is null terminated.
`sprintf` assumes the buffer is sufficiently large.
The second parameter of `snprintf` specifies the buffer size.

### `gets`
There is **very** dangerous function called `gets`.
The fuction `gets` reads the next line of input from `stdin` and copies it to a buffer supplied to `gets`.
No length checking is done. Don't use `gets`. It may even disappear from C.
Instead use `fgets` which takes a buffer, a size, and a `FILE*` as parameters.

### `strcpy` and `strncpy`
`strcpy` copies the stirng pointed to by the second aparameter into memroy pointed to by first parameter upto and including the null byte.
`strncpy` does the same but copies at most _n_ bytes.
**Warning**: strncpy may skip the null byte!
Similar situation for `strcat` which appends a string.
Use `strncat` instead.

### Compiler protection against buffer overflow.
Buffer overflows for stack allocated arrays can often be detected by letting the compiler put "canaries" with special value after such arrays.
If the value of the canary has changed, it ios likely due to a buffer overflow (or some other write throguh an invalid pointer).
This was supported by GCC some years ago.
LLVM/CLANG has suupport for a toll called AddressSanitier which behaves like Valgrind but is better integrated with GDB.


## Writing Correct C Code and then writing Fast and Correct C Code (Level 3)
**After** correctness and maintainability, speed and/or code size are usually very important qualities for C code.
Correctness is the most important, don't optimize anything before you have a correct program.
**Measure first, then improve!**
The reference implemenation should follow the specification for your code in a obvious correct way - almost not matter how slow - within practical constraints of course.


### Making the reference implementation
While the reference implementation almost always should be written in the same language as the final implemnatation, it might be a good idea to use an existing tool or language with available libraries which already (or almost) solve the problem (but not suffciently fast).
Therefore: use whatever tool or langauge you think is easiest to make a first correct ve rsion with.
For instance, C++, Java, Mathmatica, Matlab, Maple, Scala, or something else might be easiest to use.
Of course, if you are extending an existing program you probably need to use the smae language though.
Keep a copy of the reference implemenation for testing. It's invaluable.
Then, if you didn't already use C as implementation language, do that.
Thus, when you have a simple-to-undersatynd and correct reference implementation, you to write a fast version in C.

### Uses of the reference implementation
Testing invlives validating your fast versions against the reference implementation.
It may also include proving there are bugs in any other versions made by otheres - that is, if there are other verions and if your and their fast versions do not produce the same output.
For example, if you want to write a clock-cycle true simulator of a complex superscalar microprocessor, having a simple simulator which does not mode any pipline or cahche memory will be invalualbe to valide the complex mode - or finding the first instruction with the wrong result.

### Writing Correct and fast C Code.
+ Maintain correctness using the reference implementation.
+ Writing fast version what we call **implementation tuning**. Which we define as the following:

**Implementation tuning** is the manual application of code transformation techniques which current state-of-the-art optimizing compilers are **not** capable of doing automatically.

### Algorithm for improving the performance of C/C++ program.
1. If performance is good enough then go on a vacation.
2. Profile your program using different tools.
3. Figure out how you can improve the most time consuming part.
    + Should you use a different optimizing compiler or other optimization flags?
    + Should you use a different algorithm and/or data structure?
    + Can you exploit something in the input to **make the common case faster?**
    + Can you precompute or cache values?
    + Is it possible to use mathematics to simplify the program?
    + Can you use counters to collect statistics about the behaviour of your program - if the profiler do not give suffcient insights?
    + How can you exploit the behaviour you have detected?
4. Implement your ideas and make measurements to verify that your ideas are correct.
5. Valdiate your program on all test cases.
6. Go to 1.

### Profiling tools (Level 3)
+ operf - Samples the program counter and hardware counters.
+ gprof - also samples the program counter and analyses the call graph.
+ gcov  - counts the number of times each line executed

Don't forget `printf("counter X = %llu\n", X);`A
Simple counters can give a lot of insights - it's usually a good idea to use `unsigned long long` for counters - otherwise you might print nonsence, if the counter overflows.
Or better: `typedef unsigned long long count_t`

#### Performance monitor counters (operf)
Special registers in the CPU.
For instance four such registers
They can be programmed to count events
Some of the 960 events that can be counted from POWER8, some are:
+ PM_DATA_FROM_MEM
+ PM_L1_ICACHE_MISS
+ PM_RUN_INST_CMPL
+ PM_TM_TBEGIN
+ PM_CYC (clock cycles)

After a selected number of events have occurred, an exception is triggerd in the CPU.
This changes the CPU state to supervisor mode, savers PC, and jumps to the operating system kernel.
The kernel collects the statistics (event type and PC) and returns to user mode and resumes the program.

#### operf on Linux.
Measure a program such as user:
`operf -e CYCLES:100000:0:0:1 <program_name>`
The frist number specifies how many events to count before triggering an exception.
The next is a mask, the third specifies wheter kernel space should be monitored, and the fourth wheter user space souhld be monitored.
The statistics are saved in the directory `oprofile_data`.

#### intopt comiled with optimization
`opreport -t 0.7 -l` will print all function in which at least 0.7% of the cycles where sampled.

The essential parts of the output are:
`CPU:ppc64 POWER8, speed 3491MHxz (estimated)`
|Counted samples|CYCLES (%)|events (Cycles) symbol name|
|---------------|----------|---------------------------|
|36404          | 87.3207  | pivot                     |
|2544           | 6.1022   | xsimplex                  |
|844            | 2.0245   | select_nonbasic           |
|673            | 1.6143   | xinitial                  |
|368            | 0.8827   | extend                    |

Why is this run without optimization?
This is a trade-off between the quality of insights, and the actual optimized program.

Redoing the same measurement with `-O3` option to `gcc`, we instead get:
|Counted samples|CYCLES (%)|program      | events (Cycles) symbol name|
|---------------|----------|--------     |-------------------         |
|12079          | 86.3279  |intopt       |pivot                       |
|1216           | 8.6907   |intopt       |xinitial                    |
|242            | 1.7296   |intopt       |xsimplex.constprop.0        |
|145            | 1.0363   |libc-2.27.so |_int_malloc                 |
As we can see, xsimplex, has been cloned adn specialized with constant propagation.
The goal is to find the most time-consuming function, which in both cases is `pivot`.

#### `opannotate -s`
To see which source line in `pivot` gets the most samples, we can use
`opannotate -s`
which prints the source code file and the number of samples take for each line.
With optimization, the line number information is no longer accurate and therfore we show the output from the unoptimized run.
Most smaples were taken in the following loop:
```c
for (i = 0; i < m; i++){
    if(i == row)
        continue;
    for(j = 0; j < n; j++)
        if(j != col)  
            a[i][j] = a[i][j] - a[i][col] * a[row][j] / a[row][col]; // 66.8458% 
}
```

### gprof
+ Source code must be compiled with `-pg`
+ Run the program first.
+ Then use `gprof -T <program_name>`
Which procudes the output:

| %  | cumulative seconds | self seconds | calls | self ms/call  | total ms/call | name               |
|--- |--------------------|------------- |--------|------------- |-------------- | --------           |
|88.3| 1.05               | 1.05         | 148711 | 0.01         | 0.01          | pivot              |
|5.9 | 1.12               | 0.07         | 7038   | 0.01         | 0.16          | xsimplex           |
|2.5 | 1.15               | 0.03         | 148796 | 0.00         | 0.000         | select_nonbasic    |

`gprof` also produces a call-graph, i.e. which function that calls which.

### gcov
`gcov` gives output on how many times each source code line is executed.
1. Compile with `-fprofile-arcs` and `-ftest-coverage`.
2. Run the program
3. Then use `gcov simplex.c`
This produces `simplex.c.gcov` which specifies which how many times each line is run.
This is best used with an unoptimized program.

#### Branch statistics
`gcov -b intopt.c` and the same steps as above.
Gives output specifying which branch (e.g. `if` statements) the program took during execution.


## Make the common case fast (Level 3)
The code below tests for the most unlikely condition first!
How can we improve the loop?
```c
int c;
while((c = getchar()) != EOF)
    if(c == '\n')
        X;
    else if (c == ' ')
        Y;
    else 
        Z;
```
Test for the most likely path first!
```c
int c;
for(;;) {
    c = getchar();
    if (c > ' ')
        Z;
    else if (c == ' ')
        Y;
    else if (c == '\n')
        X;
    else if (c == EOF) 
        break;
    else
        Z;
}
```

If we assume Z is so large we don't to duplicate it!
```c
int c;
for(;;) {
    c = getchar();
    if (c > ' ')
L:      Z;
    else if (c == ' ')
        Y;
    else if (c == '\n')
        X;
    else if (c == EOF) 
        break;
    else
        goto L;
}
```
Not very pretty, but might be worth it!

### Cachegrind
Another profiling tool is cachegrind. Which measures the cache hit and miss ratios.
Run it with `valgrind --tool=cachegrind ./a.out`

### Using Simulators 
Profilers do not always provide "perfect" information.
For instance, Cachegrind gives cache miss rates but does not tell you why there were misses.
Some simulators can see which variables map to the same place in the cache and tell you that.
Then you probably can fix that by moving one of the variables.
Simulators are of course much slower than real machines.
However, since they can count clock cycles exactly (or at least instructions) you fothe don't have to run your benchmark for so long.

An example:
Suppose you have a short function and you want to understand exactly what happens in it.
Instead of smapling the PC during 20 seconds or five minutes, you can run the simulator once and it almost directly can tell you the function takes 44 clock cycles to execute.
More importantly, it can visualize what happens in the pipline so you understand exactly why it takes 44 cycles.
Therefore simulators actually can be quicker - but usually they are not.

# Intro to Optimizing Compilers (Level 4)
Motivation for using optimizing compilers:
+ Execution time / energy reduction: possible speedups due to compiler optimization depend on the application and the architecture (e.g. pipline, SIMD, caches, multicore)
+ Increase programmer productivity by knowing
    - What the compiler can optimize faster and better than himself and,
    - compilers' limitations and how to write code that helps them to do better automatic optimization.

### Control-Flow graph
Example C code:
```c
a = u + v;
if (a > b) {
    y = u;
} else {
    a = u - v;
    b = a - 1;
}
y = a * b;
```
#### Basic Blocks and Branches
Basic block : sequence of instruction with no label or branch.
CFG: directed graph with basic blocks as nodes and branches as edges.

Two special nodes are added:
+ The first node *s* - start.
+ The last node *e* - exit.

### Definition of Dominance
Consider a CFG _G(V, E, s, e)_ and two vertices _u, v ϵ V_.
If every path from _s_ to _v_ includes _u_ then _u_ **dominates** _v_, written _u >> v_.
In a CFG _s_ dominates every other nodes, and _e_ dominates none.

The set _dom(w)_ is a total order. I.e. we can compare two nodes.
In other words: if _u, v ϵ dom(w)_. then either _u << v_ or _v >> u_.
We can order all vertices in _dom(w)_ to find the "closest" dominator of _w_.
First _let S ← dom(w) - {w}_.
Consider any two vertices in _S_.
Remove from _S_ the one which dominates the other. Repeat.
The only remaingin vertex in _S_ is the **immediate dominator of _w_**.
We write the immediate dominator _w_ as _idom(w)_.
Every vertex, except _s_, has a unique immediate dominator.
We can draw the immediate dominators in a tree called the **dominator tree.**

#### The Dominator Tree
The dominator tree is the most important data structure in an optimzizing compiler.
| _w_ | _idom(w)_ |
| --- | --------- |
| 0   |   -       |
| 1   |   0       |
| 2   |   1       |
| 3   |   1       |
| 4   |   3       |
| 5   |   1       |
| 6   |   2       |
| 7   |   6       |


### The Lengauer-Tarjan Algorithm
The LT algorithm is the standard algorithm for computing the dominator tree.
The LT algorimth calculates the immeidate dominators in a clever way and is based on insights from depth first search.


### Loop analysis using Dominance
With the help of dominance we can find loops (**natural loops**).
Loops can be found by exploiting cycle arcs.
In a **natural loop**, one vertex called the _header_ dominates all vertices in the loop.
Suppose there is a cycle arc _(v, u)_ such as (3,1) above.
Then if _u >> v_ we know that _u_ is a natural loop header.
We can search backwards from _v_ and include everything we find to the loop, stopping at _u_.
Due to _u >> v_ we cannot go wrong and miss _u_.


## Static Single Assignment For Form: SSA Form (Level 4)
A variable is only assigned to by one unique instruction.
That instruction dominates all the uses of the assigned value.
We introduce a new variable name at each assignment. 
SSA Form is the key to elegant and efficient scalar optimization algorithms.
** But what to do when paths from different assignments join???**

If we came from a node _x_ we let a2 ← a0 and if we came from node _y_ a2 ← a1. This operation is called the ̉_phi-function_.
We insert the _phi-function_ where the paths from two different assignments of the same variable join. With the _phi-function_, each definition dominates its uses.


### Copy Propagation
Consider the two following programs, first has been converted to SSA Form.
```c
x0 = a0 + b0;
if (...) {
    ...;
}
y0 = x0; /* COPY */
if (...) {
    ...;
}
c0 = y0 + 1; /* USE */
```

```c
x0 = a0 + b0;
if (...) {
    ...;
}
if (...) {
    ...;
}
c0 = x0 + 1; 
```
+ With SSA Form we can know that it is correct to replace `y0` with `x0`.
+ The values of x0 and y0 do not change after definition (in a static sense).
+ That is to say since `x` and `y` has not changed its index it is safe to remove the copy statement.


### Constant Propagation with Iterative Dataflow Analysis
```c
a = 1;
b = 2;
if (a < b)
    c = 3;
else 
    c = 4;
put(c);
```
Each variable can be either
+ Unkown 
+ Constant
+ Non-constant
Iterative dataflow analysis is performed to determine whether a variable is constant and in that case which constant.
All branches (i.e. paths in a function) are assumed to be executable.
Since `c` cannot be both 3 and 4 it's assumed to be non-constant.


### Constant Propagation with Conditional Branches
```c
a = 1;
b = 2;
if (a < b)
    c1 = 3;
else 
    c2 = 4
c3 = phi(c1, c2);
put(c3);
```
+ Based on SSA Form.
+ Recall Kildall's algorithm assumed every branch was executable.
    - This algorithm assumes nothing is executable except the start vertex.
+ The function is interpreted and the constant expressions are propagated.
+ The interpretation processed until no new knowledge about constants can be found.

#### Key idea with _phi-functions_
+ Thanks to SSA Form, one statement and variable is analyzed at a time.
+ At a _phi-function_, if any operand is non-constant the result is non-constant, and if any two constants have different values the result is non-constant.
+ However, operands corresponing to branches which we don't think will be executed can be ignored for the moment.
+ While interpreting the program we may later realize that the branch in fact might be executed and then the _phi-function_ might be executed and then the _phi-function_ will be revaluated. 
+ We can ignore c2 and let c3 be 3.

#### Value numbering
The name is due to each expression, e.g. _ti ← a + b_, is given a number, essentially a hash-table index.
In subsequent occurrences _tj ← a + b_ it is checked whether the statement can be change to _tj ← ti_.
This is a very old optimization technique with one version that is performed during translation to SSA Form and other versions when the code already is on SSA Form.
There are obviously older versions used before SSA Form but we will not look at them.

Value numbering is part of a category called **redundany elimation**.
An expression _a + b_ is **redundant** if it is evaluated multiple times with identical values for the operands.
Elimination redundant expressions is a very important optmization goal.
There are differnt approaches to redundany elimination, including:
1. Hash-Based Value Numbering
2. Global Value Numbering
3. Common Subexpression Elimination 
4. Code Motion out of Loops 
5. Partial Redundany Elimination. 
We will look at 1, 2, and 5.

#### The Power of Global Value Numbering
Below are two functions `h`
```c
```
