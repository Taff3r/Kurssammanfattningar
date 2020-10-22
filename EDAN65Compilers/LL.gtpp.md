# LL Parsing

## Algorithm for constructing an LL(1) parser
Fairly simple. The non-trivial part:
How to select the correct production `p` for `X`, based on the lokahead token.
```
p1: X -> ...
p2: X -> ...
```
Parsing has two fields, `FIRST` and `FOLLOW`. `FIRST` points to the current token, and `FOLLOW` the one that follows.
+ Which tokens can occur in the `FIRST` position?
+ Can one of the productions derive the empty string? I.e. is it "NULLABLE"?
+ If it is "NULLABLE", which tokens can occur in the `FOLLOW` position?


### Steps in constructing an LL(1) parser
1. Write the grammar on canonical form
2. Compute NULLABLE, FIRST, and FOLLOW.
3. Use them to construct a table. It shows what production to select, given the current lookahead token.
4. Conflicts in the table? The grammar is not LL(1).
5. No conflicts? Straightfoward implmentation using table-driven parser or recursive descent.


### Example
Construct the LL(1) table for this grammar:
```
p1: statement -> assignment
p2: statement -> compoundStmt
p3: assignment -> ID "=" expr ";"
p4: compoundStmt -> "{" statements "}"
p5: statements -> statement statements
p6 -> epsilon
```
For each production `p:X -> y`, we are interested in:
+ FIRST(y) - The tokens that occur first in a sentence derived from y.
+ Nullable(y) - is is possible to derive epsilon from y? And if so:
+ FOLLOW(X) - The tokens that can occur immediately after X-sentence.

To construct the table, look at each production p: X -> y.
Compute the token set FIRST(y). Add p to each corresponding entry for X.
Then check if y is Nullable. If so, compute the token set FOLLOW(X), and add p to each corresponding entry for X.
|            | ID  | "="  |  ";" | "{" | "}" |
|------------|-----|------|------|-----|-----|
|statement   |p1   |      |      |p2   |     |
|assignment  |p3   |      |      |     |     |
|compoundStmt|     |      |      |p4   |     |
|statements  |p5   |      |      |p5   |p6   |
