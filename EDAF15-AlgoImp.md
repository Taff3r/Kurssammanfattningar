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

## Cache Memories
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

