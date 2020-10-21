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


