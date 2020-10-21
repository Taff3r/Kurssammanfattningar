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


