$INC /home/simont/git/Kurssammanfattningar-och-studietips/EDAN65Compilers/defs.gtpp
$INC /home/simont/git/Kurssammanfattningar-och-studietips/EDAN65Compilers/links.gtpp
# What is a compiler
A compiler takes some source code and produces _ASM code.

* After _ASM code has been produced _OC is produced which contains global symbols and relocatable addresses.
* Then librara _OC is linked with the previously produced _OC in the linker.
* From the linker executable code is produced, where global symblos and relocatalbe addresses have been replaced by absolute addresses.
* Finally the executable code is loaded into memory via the loader.

## Inside the compiler
A compiler converts the program in phases, from one representation to another.

The phases and their productions are the following:
* Lexical analysis (Scanning) -> tokens
* Syntactic analysis (Parsing) -> AST (_AST)
* Semantic analysis -> Attributed AST
* Intermediate code generation -> Intermediate code
* Optimization -> Intermediate code
* Target code generation -> Target code

The compiler is either split into two or three different "-ends".
Front-end:
Independent on the target language (Lexical analysis -> Intermediate code generation)

Back-end:
Independent on source language (Optimization and target code generation phases)

Middle-end:
Independent on both: Optimization phase

## Multiple langauge and target machines
To support _m_ languages and _n_ target machines we would need m * n different compilers, which is very inefficient.
A smarter way is to build a front end for each language (_m_) and a backend for each target machine (_n_), this would require only _m + n_ components.


## Lexical Analysis (Scanning)
The aim of lexical analysis is to produce the tokens and lexemes needed for the parsing stage.
A _token_ is a symbolic name, sometimes with an attribute.
A _lexeme_ is a string corresponding to a token. 
Whitespace are skipped in this stage.

## Syntactic Analysis (Parsing)
From the output of the scanning phases a parse tree is built in parsing phase.
The code 
_cCode 
while (k <= n) {sum = sum + k; k = k + 1;}
_endCode
Will produce the following tokens:
_cCode
WHILE LPAR ID LEQ ID RPAR LBRA ID EQ ID PLUS ID SEMI ID EQ ID PLUS INT SEMI RBRA
_endCode

The output from the parsing stage is the _AST.
### _AST
The abstract syntax tree contains only the essential structure and tokens representing the program.
It is very similar to a parse tree, but
    + Contains only the essential tokens
    + Has a simpler more tantural structure.
It is often represented by a typed object-oriented mode
    + Abstract classes such as (Stmt, Expr, Decl)
    + Concrete classes (WhileStmt, IfStmt, Add, Sub, etc.)

## Designing an AST Model
* What abstract constructs are there in the language
    + OOP: Make the abstract classes
    + FP: MAke them algebraic data types
* What concrete constructs are there?
    + OOP: Make the sublcasses of the abstract classes
    + FP: Make them constructors of the algebraic data types
* What parts do the concrete constructs have?
    + OOP: Add getteers for them, to accesss parts
    + FP: Use pattern matching to access parts


## Semantic Analysis
Analyze the _AST, for example,
+ Which declation corresponds to a variable?
+ What is the type of an expression?
+ Are there compile time errors in the program?

This analysis is aided by adding _attributes_ to the AST. (Properties of AST nodes)

## Intermediate Code Generation
Intermediate code:
Also knowns as _IR (IR)
+ Independent of source language
+ Independent of target language
+ Usually assembly-like
    - simpler, without many instruction variants
    - and with an unlimited number of register (or uses a stack instead)


# Generating the compiler

To build the different phases of the compiler a set of generator is most often used.
+ Regular expressions are used in the scanner generator to produce the tokens.
+ A _CFG is used in the parser generator to produce the _AST.
+ An attribute grammer is used in the attribute evalutator generator to produced the attributed _AST.

## Program errors
Each phase can produces different kinds of errors.
+ Lexical analysis -> lexical errors (text that cannot be recognized as a token)
+ Syntactic analsis -> syntactic errors (tokens in the wrong order)
+ Semantic analysys -> wrong use of names, types, etc.

Theses are called compile time errors and will stop the compilation process.

Other errors are detected first after compilation such as:
+ Runtime errors: null-pointer exception, division by zero, stack overflow, etc.
+ Logic errors: Compute the wrong result. Not caught by the compiler or the machine.

### Example of errors:

_javaCode

/* 1 */
int # square(int x)
{
    return x * x;
}
/* 2 */
int p(int x)
{
    return x * 0;
}
/* 3 */
int double square(int x)
{
    return x * x;
}
/* 4 */
boolean square(int x)
{
    return x * x;
}
/* 5 */
int square(int x)
{
    return 2 * x;
}
_endCode

+ 1 is a lexical error (Cannot interpret symbol #)
+ 2 is syntactic error (double token in the wrong place)
+ 3 is static-semantic error (wrong return type)
+ 4 is a runtime error. (Division by zero)
+ 5 is a logic error (Wrong result)


### Safe vs unsafe languages
Safe languages:
    + All runtime errors are caught by the generated code and/or runtime system are reported in terms of the language.
    + Examples: Java, C#, Smalltalk, Python
Unsafe languages:
    + Runtime errors in the generated code can lead to undefined behaviour. Best case: hardware exception soon after the real error, stopping the program. (segfault) Worst case: the execution continues, computing the wrong result or giving a segfault much later.
    + Examples: C, Assembly.

_SCANNING_
_CFGS_
_PARSERS_
_LL_
