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
(See lecture slides for images describing finite automaton _MDLINK(here, http://fileadmin.cs.lth.se/cs/Education/EDAN65/2020/lectures/L02.pdf)
