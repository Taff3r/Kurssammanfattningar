# What is a compiler
A compiler takes some source code and produces assembly code.

* After assembly code has been produced object code is produced which contains global symbols and relocatable addresses.
* Then librara object code is linked with the previously produced object code in the linker.
* From the linker executable code is produced, where global symblos and relocatalbe addresses have been replaced by absolute addresses.
* Finally the executable code is loaded into memory via the loader.

## Inside the compiler
A compiler converts the program in phases, from one representation to another.

The phases and their productions are the following:
* Lexical analysis (Scanning) -> tokens
* Syntactic analysis (Parsing) -> AST (abstract syntax tree)
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
```c 
while (k <= n) {sum = sum + k; k = k + 1;}
```
Will produce the following tokens:
```c
WHILE LPAR ID LEQ ID RPAR LBRA ID EQ ID PLUS ID SEMI ID EQ ID PLUS INT SEMI RBRA
```

The output from the parsing stage is the abstract syntax tree.
### abstract syntax tree
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
Analyze the abstract syntax tree, for example,
+ Which declation corresponds to a variable?
+ What is the type of an expression?
+ Are there compile time errors in the program?

This analysis is aided by adding _attributes_ to the AST. (Properties of AST nodes)

## Intermediate Code Generation
Intermediate code:
Also knowns as intermediate representation (IR)
+ Independent of source language
+ Independent of target language
+ Usually assembly-like
    - simpler, without many instruction variants
    - and with an unlimited number of register (or uses a stack instead)


# Generating the compiler

To build the different phases of the compiler a set of generator is most often used.
+ Regular expressions are used in the scanner generator to produce the tokens.
+ A context-free grammar is used in the parser generator to produce the abstract syntax tree.
+ An attribute grammer is used in the attribute evalutator generator to produced the attributed abstract syntax tree.

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

```java

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
```

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

# Scanning
The scanning produces tokens for the parsing phase.
The scanner needs a specification for the formal language it is trying to parse.
A formal language consists of is a set of string (can be infinite) where:
+ An _alphabet_, which is a set of symbols (nonempty and finite)
+ Strings, which are sequnces of symbols (each string is finite)
We need to specify which strings belong to the language ot not.

In the course this is done through a jFlex specification describing rules for creating tokens.
Each rules has the form:
`regex  {lexical action}`
where the lexical action consist of arbitrary Java code, which is run when a regular expression is matched.

The rules need to be unambigous consider the following rules:
```java
// tokens
"if"         {return new Token("IF"); }
"="          {return new Token("ASSIGN"); }
"<"          {return new Token("LT"); }
"<="         {return new Token("LTEQ"); }
[a-zA-Z]+    {return new Token("ID", yytext()); }
```

Will the tokens from the string `a <= b` produce `ID LTEQ ID` or `ID LT ASSING ID` ?
To resolve these ambiguities we have two addtional rules:
+ **Longest match**: If two rules can used to match a token, the longest match will be chosen.
+ **Rule priority**: If two rules can be used to match the same sequence of characters, the first one take priority.

## Implementation of scanners
Regular Expression are equivalent to finite automate (finite-state machines).
The overall approach is:
+ Translate each token regular expression to finite automaton. Label the final state with the token.
+ Merge all the automata.
+ The resulting automaton will in general be _nondeterministic_.
+ Translate the nondeterministic automaton to a _deterministic_ automaton.
+ Implement the determinisitic automaton, either using switch statements or a table.

Scanner generators automate this process.
(See lecture slides for images describing finite automaton [here](http://fileadmin.cs.lth.se/cs/Education/EDAN65/2020/lectures/L02.pdf))

### DFA vs NFA
Deterministic Finite Automaton (DFA):
A finite automaton is deterministic if:
+ All outgoin edges from any given state have disjoint chracter sets
+ There are no epsilon edges
Can be implemented efficiently

Non-deterministic Finite Automaton (NFA):
An NFA may have:
+ Two outgoing edges with overlaping character sets
+ Epsilon edges
__Every NFA can be translated to an equivalent DFA.__

### Translating NFA to DFA
Simulate the NFA:
    + Keep track of a _set_ of of current NFA-states
    + Follow epsilon edges to extend the current set (take the _closure_)
Construct the corresponding DFA:
    + Each such _set_ of NFA states ocrresponds to _one_ DFA state
    + If any of the NFA states is final, the DFA state is also final, and is maked with corresponding token.
    + If there is more than on token to choose from, select the token that is defined first (rule priority).

(Minimize the DFA for efficiency)

# Context-free Grammars
Unlike regex which can only have iteration, a Context-Free Grammar (CFG) can also have recursion.
## Elements of a CFG

### Production rules:
`X -> s1 s2 ... sN` where `sK` is a symbol (terminal or non-terminal), n >= 0
**Non-terminal** symbols are symbols which are defined as another production.
**Terminal** symbols are symbols which are defined as tokens.
Example CFG:
```c
Stmt -> WhileStmt
Stmt -> AssignStmt
WhileStmt -> WHILE LPAR Exp RPAR Stmt
AssignStmt -> ID EQ Exp SEMIC
Exp -> ID
Exp -> Exp PLUS Exp
```

### Shorthand
Alternatives:
    `Stmt -> WhileStmt | AssignStmt`
is equivalent to:
    `Stmt -> WhileStmt`
    `Stmt -> AssignStmt`
Repetition:
    `Stmt*`
is equivalent to:
    `StmtList`
    Where:
        `StmtList -> epsilon | Stmt StmtList`


## Parsing
Use the grammar to derive a tree for a program top-down or bottom-up.
In the end we are left with a parse tree.
In a parse tree:
* All input tokens are included as leafs.
* Non-terminals are inner nodes.
* Terminals are leafs.

### EBNF vs Canonical From
There are two main ways for writing CFGs.

**(Extended) Backus-Naur form**:
+ Compact, easy to read and write
+ EBNF has alternatives, repetition, optionals, and parentheses (like REs)
+ Common notation for practical use

**Canonical form**:
+ Core formalism for CFGs
+ Useful for proving properties and explainging algorithms.

# Formal Definition of CFGs
A CFG `G = (N, T, P, S)` where:
+ N - The set of nonterminal symbols
+ T - The set of terminal symbols
+ P - The set of production rules, each with the form:
    * X -> Y1 Y2 ... YN
    Where X in N, n >=0, and Yk in N union T.
+ S - The start symbol (one of the nonterminals). I.e. S in N.

Which gives us the following:
+ The left-hand side X of a rule is a nonterminal.
+ The the right hand side Y1 Y2 ... YN is sequence of nonterminals and terminals.
+ If the rhs for a production is empty, i.e. n = 0, we write X -> epsilon.


### A grammar G deines a language L(G)

G defines a *language* L(G) over the alphabet T.
T* is the set of all possible sequences of T symbols.
L(G) is the subset of T* that can be derived from the start symbol S, by folllowing the production rules P.

## Ambiguities
Can we do another derivation of the same sentence, that gives a different parse tree?
If so A CFG is ambiguous.
(Note! There can be many different derivations that give the same parse tree, this doesn't mean it is ambiguous.)

### How to determine ambiguity
If we find an example of ambiguity, we know the grammer is ambiguous.
There are several algorithms for decididing if a CFG belongs to certain subsets of CFGs, e.g. LL, LR, etc. These grammars are unambiguous.
But in the general case, the problem is **undecidable**: iti is not possible to construct a general algorithm that decides ambiguity for an arbitrary CFG.


# Parsing Algorithms
Two main algorithms, **LL**, and **LR**.
LL:
+ Left-to-right scan
+ Leftmost derivation
+ Builds tree top-down
+ Simple to understand
LR:
+ Left-to-right scan
+ Rightmost derivation
+ Builds tree bottom-up
+ More powerful

**LL(1)**:
Decides to build Assign after seeing the first token of its subtree. The tree is built top down.
**LR(1)**:
Decides to build Assign after seeing the first following its subtree. The tree is built bottom down.

The token in both is called "lookahead" LL(k) and LR(k) use k lookahead tokens.
In practice, k=1 is usally used.

### Recursive-descent parsing
A way of programming an LL(1) parser by recursive method calls.

Assume a BNF grammar with exactly one production rule for each nonterminal.
Each production rule RHS is either:
1. a sequence of token/nonterminal symbols, or
2. a set of nonterminal symbol alternatives

For Each nonterminal, a method is constructed. The method:
1. matches tokens and calls nonterminal methods, or
2. calls one of the nonterminal methods - which one depends on the lookahead token.

If the lookahead token does not match, a parsing error is reported.

Example: recursive descent methods
```
statement -> asssignment | block
assignment -> ID ASSIGN expr SEMICOLON
block -> LBRACE statment* RBRACE
```
```java
class Parser {
    void statement() {
        switch(token) {
            case ID: assignment(); break;
            case LBRACE: block(); break;
            default error("Expecting statement, found: " + token);
        }
    }

    void assignment() {
        accept(ID); accept(ASSIGN); expr(); accept(SEMICOLON);
    }

    void block() {
        accept(LBRACE);
        while(token!=RBRACE) {statement();}
        accept(RBRACE);
    }

    void accept(int t) {
        if (token==t) {
            token = nextToken();
        } else {
            error("Expected" + t + " , but found " + token);
        }
    }

    void error(String str) {...}

    private int nextToken() {...}
    void statement();
    ...
}
```
## Identifying grammars
Is this grammar LL(1)?
```expr -> name params | name```
What would happend in a recursive-descent parser?
Could the grammar be LL(2)? LL(k)?

Its not because of **common prefix**, the expr method would not know which alternative to call.
It could be LL(2)? This depends on the definition of name.

Is this grammar LL(1)?
```expr -> expr "+" term```
This is called left recursion, the expr method call expr recursibely without readinga any token, resultion in an endless recursion.
This grammar cannot be LL(2) or LL(k).

### Dealing with common prefix of limited length:
LL(2) grammar:
```
statement -> assignment | block | callStmt
assignment -> ID ASSIGN expr SEMICOLON
block -> LBRACE statement* RBRACE
callStmt -> ID LPAR expr RPAR SEMICOLON
```
Local lookahead:
```java
void statement(token) {
    case ID:
        if (lookahead(2) == ASSIGN) {
            assignment();
        } else {
            callStmt();
        }
        break;
    case LBRACE: block(); break;
    default: error("Expecting statement, found: " + token);
}
```



# Grammar equivalence, eliminating ambiguities, adapting to LL parsing.
In the set of CFGs:
+ Unambiguous grammars are subset of ambiguous grammars.
+ LR is a subset of unambiguous grammars.
+ LL is a subset of LR.

## Strategies for dealing with ambiguities
First, decide which parse tree is the desired one.
+ Eliminate the ambiguity:
    - Create an equivalent unambiguous grammar.
    - Usually possible, but there exists grammars for which it cannot be done.
    - However, the parse tree will be different from the original desired one.
+ Alternative, some parser generators support disambiguation rules:
    - Use the ambiguous grammar.
    - Add priority and associativity rules to instruct the parser to select the desired parse tree.
    - Works for some ambiguities.
+ Alternatively, use general parser:
    - Constructs all parse trees.
    - Disambiguate after parsing.
    - But general parser are slow (cubic in input length)


### Equivalent grammars
Two grammars, G1 and G2, are equivalnt if they generate the same language.
I.e. a sentence can be derived from one of the grammars, iff it can be derived also from the other grammar:
    `L(G1) = L(G2)`

## Common kinds of ambiguities
* Operators with differeent priorities:
    -  `a + b * c == d`, ...
* Associativity of operators of the same priorities:
    - `a + b - c + d`, ...
* Dangling else:
    ```c
    if (a)
    if (b) c = d;
    else e = f; 
    ```

### Priority
    ```
        Exp -> Exp "+" Exp
        Exp -> Exp "*" Exp
        Exp -> INT
    ```

prio("*") > prio("+") (According to convention)
prio("+") >= prio("*") (Would be unexpected and confusing)

### Associativity
For operators with the same priority, how do several in a sequence associate?
```
Exp -> Exp "+" Exp
Exp -> Exp "-" Exp
Exp -> Exp "**" Exp
Exp -> INT 
```
Left-associative (Usual for most operators)
Right-associative (Usual for the power)

### Non-associativity
For some operators, it does not make sense to have several in a sequence at all. They are non-associative.
```
Exp -> Exp "<" Exp
Exp -> INT 
```
We would like to forbid trees that produce these. I.e. rule out the sentence from the language.

## Disambiguating expression grammars
How can we change the grammar so that only the desired trees can be derived?
Idea: Restrict certain subtrees by introducing new nonterminals.
Priority: Introduce a new nonterminal for each priority level:
    - Term, Factor, Primary, ...
Left associativity:
    - Restrict the right operand so it only can contain expressions of higher priority
Right associativity:
    - Restrict the left operand ...
Non-associativity: Restrict both operands.

### Example of making an ambigous grammar unambiguous
```
Ambgiuous grammar:

Expr -> Expr "+" Expr
Expr -> Expr "*" Expr
Expr -> ID
Expr -> "(" Expr ")" 
```

```
Equiv. unambiguous grammar:
Expr -> Expr "+" Term
Expr -> Term
Term -> Term "*" Factor
Term -> Factor
Factor -> ID
Factor -> "(" Expr ")"
```

Here, we introduce a new nonterminal, Term, that is more resticted than Expr.
That is, from Term, we can not derive any new additions.

For the addition production, we use Term as the right operand, to amke sure no new additions will appear to the right. This gives left-associativity.
For the multiplication production, we use Term, and the even more restriced Factor to make sure no additions can appear as childer (without using parenthses). This gives multiplication higher priority than addition.

### The "dangling else" problem

```
S -> "if" "(" E ")" ["else" S]
S ->  ID "=" E ";"
E -> ID
```
This can give two different parse trees.
### Solutions
+ Rewrite to equivalent unambiguous grammar
    - possible, but results in more complex grammar (several similar rules)
+ Use the ambiguous grammar
    - Use "rule priority", the parser can select the correct rule.
    - works for the dangling else problem, but not for ambiguous grammars in general.
    - not all parser generators support it well.
+ Change the language?
    - e.g. add a keyword "fi" that closes the "if"-statement
    - restrict the "then" part to be a block " { ... }". 
    - only an option if you are desigining the language yourself.

### Rewriting the dangling else
```
Ambgiuous grammar:
S -> "if" E S // Short if
S -> "if" E S "else" S // Long if
S -> "while" E "do" S
S -> ID "=" E ";"
S -> "{" S* "}"
```
Idea: Limit S before "else" so that it cannot end with a short if.

```
Unambiguous grammar:
S -> "if" E S
S -> "if" E LimS "else" S
S -> "while" E "do" S
S -> ID "=" E ";"
S -> "{" S* "}"
LimS -> "if" E LimS "else" LimS
LimS -> "while" E "do" LimS
LimS -> ID "=" E ";"
LimS -> "{" S* "}"
```

Another approach:
Require block before "else"
```
Unambiguous grammar:
S -> "if" E S
S -> "if" E  "{" S*  "}" "else" S
S -> "while" E "do" S
S -> ID "=" E ";"
S -> "{" S* "}"
```


### How to find ambiguities in practive
Try to run a CFG through an LL or LR parser generator
+ If it is accpeted by the parser generator, the grammer is unambiguous.
+ If not, the grammar could be ambiguous, or unambiguousm but outside of the parser generator grammar class.
    - In any case, you to analysze that particular problem. This can be quite tricky, especially for large grammars.


# Adapting grammars to LL parsing
Typically, ned to eliminate Left REcusion and Common Prefixes. (May not be enough.)
The parse tres will be differnt from the original desired ones.
Some work needed to buld the desired ASTs anyway.
EBNF helps: relatively easy to buld the desired AST.


## Eliminating common prefix
Rewrite to an equivalent grammar with the common prefix.
Common prefix - not LL(1)
`Exp -> Name Params | Name` 

Without common prefix - LL(1)
```
Exp -> Name OptParams
OptParams -> Params | epsilon
```

This is called **left factoring**.

