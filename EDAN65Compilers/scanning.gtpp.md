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
_javaCode
// tokens
"if"         {return new Token("IF"); }
"="          {return new Token("ASSIGN"); }
"<"          {return new Token("LT"); }
"<="         {return new Token("LTEQ"); }
[a-zA-Z]+    {return new Token("ID", yytext()); }
_endCode

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
(See lecture slides for images describing finite automaton _MDLINK(here,http://fileadmin.cs.lth.se/cs/Education/EDAN65/2020/lectures/L02.pdf))

### DFA vs NFA
_DFA (DFA):
A finite automaton is deterministic if:
+ All outgoin edges from any given state have disjoint chracter sets
+ There are no epsilon edges
Can be implemented efficiently

_NFA (NFA):
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
