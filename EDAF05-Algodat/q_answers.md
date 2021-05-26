# Explain what O(n), Omega(n), and Theta(n) means.
All are measures of how much an algorithm scales time, memory, comparisons etc with growing input.

These are not exact, because that would not be useful since a program also depends on the programming language, compiler, and hardware.

* O(n)
    - Defines the _upper_ bound of the algorithm, i.e. it can't get worse than that.
    - Also called *Asymptotic complexity*, because of the following definition:
        + O(f(n)) = {g(n) : g(n) <= c * f(n), n > n0} 
        "The function f(n) belongs in the set of functions O, if there exists a function g(n) which is strictly less than some constant c multiplied by f(n), where n is some value in the function, greater than some lower value."
    - This means all functions in the set O(n) belongs in O(n^3) 
* Omega(n)
    - Defines the _lower_ bound of the algorithm, i.e. it can't get better than that.
    - Also an *Asymptotic complexity*, but for the lower bound instead.
        + Omega(f(n)) = {g(n): g(n) * c <= f(n), n > n0}
* Theta(n)
    - When both Omega(n) and O(n) are determined we can find the "exact" time complexity, defined as Theta(n).


# Suppose you gave invented a greedy algorithm that finds an optimal solution to a problem. Explain two approaches to proves its output is really optimal.

There are two common approaches to proving that a greedy algorithm is optimal.
* Proving that the greedy algorithm is always atleast as good as the optimal algorithm,
* Or by transforming the output of the optimal algorithm, without changing its quality, to the output of the greedy algotihm.

These methods are referred to as *staying ahead*, and by an *exchange argument*. In both cases we are not comparing the algorithms, but only their output.

# Explain what is meant by a divide-and-conquer algorithm (söndra-och-härska).

Divide and conquer algorithms are algorithms which split the problem into more easily solved subproblems and then combining the results of the subproblems in (often) linear time to get a result.

# Explain what is meant by dynamic programming (dynamisk programmering)
Dynamic programming is about taking a problem which is expresed as the solution of several smaller subproblems, such as printing the fibonnaci sequence. We cache the intermediate results so that once they have been calculated they can be found in constant time and "bubble up" their results.
In contrast to divide-and-conquer algorithms these problems are dependent on each other, while in divide-and-conquer they are independant.

# Explain what the Master Theorem is about.

The Master Theorem is about finding the complexity of a divide and conquer algorithm. A simplification of The Master Theorem can be applied if and only if the function in its original form is polynomial. ( `f(n) = n^s, s > 0, s is in R)`)
It states the following system of equations:
    * T(1) = 1
    * T(n) = aT(n/b) + n^s
Depending on a, b, and s we get three cases of closed formulas. 
These are the following:

* T(n) = O(n^s), when s > logb(a)
* T(n) = O(n^s * logn), when s = logb(a)
* T(n) = O(n^(logb(a))), when s < logb(a)


# Explain how hollow heaps work. Focus on the simplest version with multiple root nodes.
Hollow heaps are an improvement of the Fibonnaci heap, hollow heaps are both simpler and faster than Fib heaps.
Hollow heaps sport O(1) time for:
    * Insertion
    * Decrease key
And amortized O(logn) time for:
    * Delete
    * Delete_min
Compared to a normal binary-heap a Hollow heap uses a lot more memory (has to keep track of more pointers)

### Basics
* A Hollow heap can have several root-nodes, so a heap is set of trees. 
* Each tree has the heap-proprerty, i.e. key(parent) <= key(child). For a min-heap.
* Each node has a list of children.

* We store key/value pairs and we call each value an "item".
* Node != Item
* A node has a pointer to an item. An item has a pointer to a node, both have the same key.
* An item can jump from one node to another, i.e. a node can lose its item.
    + However each item and node has the same value for key.
* A item also keeps a list of its siblings.

### Link and insert
* A node is either full or empty/hollow.
* When calling decrease key, an item changes it key. However the previous node keeps its key value and become hollow.
    + A new node is created for the item whos key has been changed.

* `link(v, w)`, where v and w are full root-nodes. `link` links the nodes such that one becomes the parent and the other the child. (According to the heap-property)
* `link` reduces the number of root nodes by one, since one of the nodes becomes a child to the other. 

### delete

* If node(item) != min(heap), make node(item) empty.A
* else if node(item) == min(heap), make all the children of the node to new root nodes. Then "clean" the structure . This should be done in amortized O(log(n)).

* Remove all hollow root-nodes and make their children to new root nodes.
* Reduce the number of root-nodes (to one) through links.
* Each node has a "rank" which increase with one when it becomes a parent in a link (almost always the number of its children).
* We call link on root-nodes which have the same rank. 
* The root-nodes are not sorted. (Random order).
    + Traversing through the list of root-nodes to find the ones which have the same rank is not a good idea.
    + Instead we index an array of the ranks of the root-nodes where the array at index _i_  points to the root-nodes with rank _i_. So the array needs to be the size [0..max_rank].  
* When we traverse the linked list we add the rank of the current node to the array and point it to that node.
    + If there is already a node at that rank we call link on the current node and that which the rank-array is pointing to. Reducing the number of root nodes by one, the ranked array now adds the resulting parent node of the link to index _rank(a) + rank(b)_ since the resulting rank of the parent after link is now the combined rank of both. At _rank(i)_ now becomes `null` again.

### Rank

* For a node _u_ the following is true:
    + Either _u_ has _r_ children with ranks, _r - 1, r-2, r-3, ..., 2, 1, 0_.
    + Or if _r_ > 2, and _u_ became hollow, by a call to _decrease_key_, then _u_ has two children with ranks, _r-2, r-1_.

* When calling _decrease_key_ an item moves from _u_ to a new node _v_ and _rank(v)_ becomes _max(0, rank(u)-2)_.
    + Move all children _w_ from _u_ with _rank(w) < rank(v)_. If _rank(u) >= 2_ _u_ keeps their children with _r-1, r-2_ as rank.


# Union-find
Union-find is a data structure which allows to partion a graph in to sets of a graph.
* Allows us to find which set an item in a graph _G_ belongs to.
* Merge two sets.

Each set is represent by a canoncial member, which has edges to nodes which are in each set as a linked-list.
Finding if a node is the member of a set is simply traversing towards the root, which is the canonical member.

Creating a union is a simple as setting the parent of one the sets canonical member as the parent of the other sets canonical member. Creating a tree.

# What can make a naïve version of union-find slow?
If we do the multiple finds where the path to the canonical member is a linked-list we have to |S| operations to find the canonical member. 
#Explain how union-find can be made faster than as in the naïve version.
However if we during a find operation set the parent of each node in the linked-list to point directly to the root/canonical member we can do future finds quicker.  

We can also do union-by-rank or union-by-size which have identical time complexities.

When union-by-rank each set has an initial rank of zero. When the height of the of the set is increased the rank is also increase by one.  

When merging the sets picking the set with higher rank as the new parent allows us build a more shallow tree.

# What does it mean that a directed graph is "strongly connected" (starkt sammankopplad), and how can you use BFS to determine if a graph is strongly connected?

* Strongly Connected
    + In directed graphs, nodes _u_ and _v_ are *mutually* reachable if there is a a path from _u_ to _v_ and a path from _v_ to _u_.
    + A directed graph is strongly connected if every pair of nodes are mutually reachable.

    + Lemma: Let _s_ be any node in _G_. _G_ is strongly connected <=> every node is reachable from _s_ and _s_ is reachable is reachable from any node.
        - Proof: => follows directly from the definition of a strongly connected _G_. <= follows by constructing two paths: 
        - * A path from _u_ to _v_ as _p = (u, ..., s, ...v)_
        - * a path from _v_ to _u_ as _q = (v, ..., s, ...u)_

### Determine strong connectivity
We can determine if directed graph is strongly connected by selecting a node _v_ in _V_. Use _BFS_ on G from _v_ and check if all of _V_ is reached. The reconstruct _G_ into _Greverse_ by reversing all edges. Use BFS again on _Greverse_ from _v_ and check if all of _V_ is reached. If all of V is reached in both searches, _G_ is strongly connected.

# Explain how we can find __strongly connected components__ in a directed graph using __Tarjans Algorithm__ 
A strongly connected component is a set _S_ of vertices such that for every pair _u, v_ in _S_ there is a path _u -> v_. To find these components in a graph, we can use __Tarjan's Algorithm__ which is based on DFS.

Consider the edge _(v, w)_. When _w_ is not yet visited we must visit it by calling _strong_connect(w)_. If _w_ has been visited, we have two amin cases:
    * _w_ is not on the stack, beacuse it has already found its SCC.
    * _w_ is on the stack, beacuse it's wairing to be popped.
        + If _dfn(w) < dfn(v)_ then _v_ must set its lowlink so it does not think it is its own SCC.
        + If _dfn(v) < dfn(w)_ then not more information for _v_ is available. There is another path from _v_ to _w_ due to to which they will belong to the same SCC.

# What is a bipartite graph, and how can you determine if a graph is bipartite.
A bipartite graph is bipartite if it can be colored with two colors such that every edge connects two nodes with different colors.
If there exists an __odd cycle__ in a graph the graph is not bipartite.

Determining if a graph is bipartite we use the BFS levels to see if there are edges between nodes in the same level, if there are edges between any nodes in the same level then the graph is __not__ bipartite.

# Explain how __Djikstras Algorithm__ works and why it is correct.

Djikstras Algorithm is an algorithm which can find the shortest path in a weighted graph, were the shortest path means that the sum of the weights along the found path is the minimum in the graph.

### Djikstras algorithm works in the following way:
Given a __directed__ graph _G(V, E)_, a weight function _(u, v) -> w_, where _w((u,v)) >= 0_, and a node _s in V_. The algorithm computes the shortest path from _s_ to every other node. Dijktras algorithm computes the two outputs:
    * The shortest path distance from _s_ to _v_.
    * for each node _v in {V} - s_, the predcessor of v in the computed shortest path from _s to v_.
__NOTE!__ There can exist several different paths to a node and that one of one these are computed. 
Djikstras uses two sets of nodes:
    * a set _Q_ which are the nodes we yet have found the shortest path to.
    * a set _S_ which we have already found the shortest path to.
We only add an edge when it is to the node which is closest to the start vertex. To pint the shortest path from _s_ to a node _v_, simply print _v_ and follow _pred(v)_, towards _s_. 

Djikstras algorithm uses a priority queue as Q, where it extracts the minimum from the queue which is the value of d(v).
Here is psudoe code for Djikstras

```
Dijkstra(G, s)
    for all u in (V - {s}), d(u) = INFINITY 
    d(s) = 0
    R = {}
    while R not equal to V:
        pick u not in R with smallest d(u)
        R = R union with {u}
        for all vertices v adjacent to u
            if d(v) > d(u) + w(u, v)
                d(v) = d(u) + w(u, v)
```
### Proof correctness for Djikstras:
Proof by induction:
    + Base case |S| = 1 which is true since S = {s} and d(s) = 0. 
    + Assume the theorem is true for |S| >= 1.
    + Let v the next node addded to S, and pred(v) = u. d(v) = d(u) + w(e), where e = (u, v)
    + Assume in contradiction there exists a shorter path from s to v. containing the edge (x,y) with x in S, and y not in S, followed by a subpath y to v.
        - Since the path via y to v is shorter than the path from u to v, d(y) < d(v)
        - but is is not since is chosen and not y.
        - this contradiction means no shorter apth to v exists. 

# Explain what can happen if there are negative edges.
If there are negative edges in a graph used in Djikstras algorithm, a shortest path cannot be found. This is due tothe greedy nature of the algorithm. Assume we have graph:
```
G = {
    V : {A, B, C},
    E : {(A, C, 2), (A, B, 5), (B, C, -10)}
};
```
When calling djikstras with starting node A. It will automatically assume the shortest path to is 2, and added to the finished nodes. It cannot see the step to B which then reduces the total cost A->C to 5  + -10  = -5 < 2.


# Explain how the Bellman-Ford algorithm works and why it is correct 
The alternative when using negaive weights is to use the Bellman-Ford algorithm. 
Bellman-Ford algorithm is dynamic programming algorithm.

Bellman-Ford builds and table M[n][n] where n is the number of nodes in the graph.
The problem is to find the shortest path from _s_ to _p_.

In the matrix M the first index is the edge used to reach the node of the second index.
We build M using the Bellman-Ford algorithm in O(n^3) or O(|V| * |E|) time in a dense graph or , and uses O(n^2) space.

```c
int M[n][n]

int** make_table(graph G, node s, node t)
{
    n = G.num_vertices;
    
    M[0][t] = 0;
    for (node v : G)
        if (v != t)
            M[0][v] = INFINITY;
    int i = 1;

    while ( i < n - 1) {
        for (node v : G) {
            M[i][v] = min(M[i - 1][v], M[i - 1][w] + c(v, w)) /* w is a neighbor to v */
        } 
        i++;
    }
    
}
```  
_i_ represents the number of edges we traveled to get to v so M[2][v] is the cost of getting from _t_ to _v_ using 2 edges. 
### Proof of correctness for Bellman-Ford 
TODO!

# Explain what a Minimum Spanning Tree (MST) (Minimalt Uppspännande Träd) is and how it can be found using Prim's and Kruskal's Algorithm.
A MST is a tree that connects a node to all other nodes with minmal cost for the edges in a undirected connected graph.
### Prims Algorithm
Using Prims algorithm, which is similar to Djikstras algorithm we can find the MST by usinga priority queue which chas the keys which are the current cost of getting to that node.
* We start by adding setting a root node, e.g. the first node in our graph.
* We also have some way of knowing which of nodes are currently in the queue, e.g. an array of booleans.
* We set the weight of all nodes to infinity, with the exception of the root node which has a weight of zero.
* Add all the nodes to the queue.
* Get the node with the currently smallest cost, _u_
* For all neighbors to _u_:
    + If the neighbor is in the queue
        - If the cost of getting to _u_ is lower than the weight((u, neighbor))
            + Update the cost of the node to be weight((u, neighbor))
            + Update the priority queue so that the new cost of v is represented.

This works because of safe edges. (See later)

### Kruskals Algorithm
Kruskals Algorithm always selects the edge with minimal weight which does not create a cycle.
It starts by creating a forest of nodes, which eventually becomes a spanning tree.

To detect these cycles union-find data structre is used.
* When two sets are to be merged => Check if u and v are already in the same set using _find_.
    + If they are in the same set the merge can be ignored, since it would create a cycle.
    + O/w merge the sets.

Since the edges selected are sorted/extracted by their weight the smallest path will always be chosen, and redundant edges will not be used since they would create a cycle.
 
# What is a "safe edge" (säker kant) for minimum spanning trees?
Both Prims and Kruskals algorithms are dependant on the concept of safe edges.
### Definition
Let S be a proper subset of V, and not be the empty set. A partition (S, V-S) is a _cut_. An edge (u,v) crosses the cut if u is in S and v is in V - S. Let also A be the current selected edges in the MST, A does not necessarily create a connected graph (yet). An edge (u, v) is __safe__ if A union {(u,v)} is also the subset of the edges in some MST. But how do we know that an edge is safe?

### Proof 
Assume T is a minimum spanning tree of a graph. We either have (u,v) in T (the MST is complete) or (u,v) not in T,
Safely assume u is in S, and v is in V-S, then there is a path p in T which connects u and v, T union {(u,v)} which creates a cycle with p. There is an edge (x,y) in t which also crosses the cut and by assumption (x,y) is not in A. Since T is a MST it has only one path from u to v. Removeing (x,y) from T partitions V and adding (u,v) creates a new spanning tree U. Since (u,v) has minimum weight, w(U) <= w(T), and since T is a MST w(U) = w(T). Since A union {(u, v)} is a proper subset of U, (u,v) is safe for A.

# What is Network Flow (nätverksflöde) about? Give an example of where it can be used.

Network Flow is about selecting edges in a (directed) graph from a start node, _s_ to a sink node _t_ such as much flow is able to be sent from the start to sink node. Each edge has a capacity _c_ and that is most amount that can be sent along any edge.

A common use cases is transportation planning, e.g. a railway. We wish to find the maximum amount of people/cargo that can be sent from one place to another, without exceeding the capacity of any edge giving us the maximum flow.

There are several constraints on the nodes, the most important is the flow-conservation constraint, which says that the flow coming out of a node cannot be less or more than the flow coming into it. 

# Explain the Ford-Fulkerson algorithm and why it is correct. What is the time complexity, and why?

At first glance the Ford Fulkersson algorithm seems pretty simple:
1. Start with flow f(e) = 0 for every edge e in Edges.
2. Look for a simple path _p_ from _s_ to _t_ such that on every edge in p we can increase the flow in the direction from _u_ to _v_.
3. If we could not find the path, we have reached maximum flow and we are done.
4. Let each edge on p have a value sigma, which the means room for improvment sigma = f - c
5. Let delta be the minimum of all sigmas on _p_.
6. Increase the flow on _p_ with delta.
7. GOTO 2. 

The path can be found in some way, e.g. using BFS with the extra requirement that all edges should have a positive sigma.

However in the algorithm it is not clear how we can reduce the flow on an edge, this where the residual graph comes in handy. 

### Residual Graph 
The residual graph _Gf_ is an new graph which is used in the FF algorithm. _Gf_ has the same nodes as _G_ but with additional edges along side the edges in _G_. These additional edges are called the _residual edges_ and exists to be able to undo previous augmentations. When an edge (u,v) is augmented and its flow updated, the residual edge (v,u)'s capacity is set to the negative flow, this means that these edges are still valid paths to take in the next iteration of the algorithm since sigma = f - c, and if c is negative sigma = f - -c = f + c which means that the room for improvement is still positive and can be used as an edge in the next iteration.


### Time complexity
The time complexity of finding the maximum flow is dependant on the method used to find the augmenting paths _p_.
If DFS is used the algorithm runs in O(Ef), where E is the number of edges and f is the maximum flow in the graph.
Since DFS is somewhat random (depends on the order of edges in the input), and in the worst case can pick the edge with the lowest value all iterations but the last, will take a very long time to find the maximum flow.

If a BFS method is used instead, in which case the algorithm is instead called Edmond-Karp, the run-time complexity is instead bounded by the number of edges and nodes in the graph, and becomes O(|V||E|^2), since the path can be found in O(|E|) time assuming |V| <= |E|/2 and BFS has a runtime of O(|V| + |E|) = O(|E|/2 + |E|) = O(|E|).
And augmenting the paths takes an additonal |V| time since the path can be at most |V| long. Once a path has been selected atleast one edge gets _saturated_ and can not be increase further. So that the next time the path is selected the path cannot be shorter (since BFS finds the minimum number of jumps) than last time, which means at most |E| additional iterations can run.

# Explain Goldberg-Tarjan (preflow-push) algorithm and why it is correct
TODO

# Explain why the Gale-Shapley finds a stable matching (stabil matchning)?
Gale-Shapley is an algorithm for finding stable matchings, e.g. the stable marrige problem.

Lets say we have a number of men which each have a preference list containing the women they would like most to marry.
The same goes for the women.
A stable matching is a match so that neither partner would prefer another partner who also would prefer to swap to that partner.

Gale-Shapely finds these matching using the following algorithm:

0. Add each man to FIFO queue
1. While the queue is not empty
2. Pick out the man at the front of the queue
3. Let the man propose to the woman he most prefers and has not yet proposed to
4. If the woman is single make them a pair
5. else if the woman prefers that man over their current man
    + Dump her current man and become a pair with the man who proposed
    + Add the dumped man to the queue
6. else the man goes back in the queue.
7. goto 1.

When the queue is empty the algorithm terminates, and all men and women should be matched. 

In Gale-Shapley men get worse and worse matchings while women get better and better, however women doesnt get much say in the matter (atleast in the begining).

The algorithm is correct since each woman gets to "upgrade", while the men get to "downgrade", and if they would end up without a matching the number of men and women would not be equal. If a man doesn't get his preferd partner it means either:
a) He hasn't proposed to her (not possible)
b) His prefered partner prefers someone else

If a woman doesn't get her prefered partner it means either:
a) He hasn't proposed to her (he prefers another and hasn't been dumped)
b) She hasn't dumped her current match (not possible)


# Explain the time complexity of Gale-Shapley
Men can propose at most n times and can therefor be put back in the queue at most n - 1 times.
Women can look up their prefered partner in constant time by inverting their preferce list. 

# What is sequence alignment and how can it be done?
Sequence alignment we are interested in comparing two strings to see how similar they are based on some score.
When two strings/sequences are not identical one of two things can happen:
1. A symbol is missing from either string
2. or at a certain point the charcters have different symbols.

A way to perform sequence alignment is to use a dynamic programming aproach using some scoring system between the characters and a penalty for inserting a _indel_ (insertion or deletion).

Using the dynamic approach we can use the recurrence:
* OPT(i, 0) = i * indel value (pad the remaining sequence of i)
* OPT(0, j) = j * indel value (pad the remaining sequence of j)
* OPT(i, j) = matching value(stra[i], strb[j]) + OPT(i - 1, j - 1) (use the matching value and move on)
* OPT(i, j) = indel value + OPT(i, j - 1) (use the indel value for i and move on)
* OPT(i, j) = indel value + OPT(i - 1, j) (use the indel value for j and move on)

Each value i, j in OPT represents the maximum value in a memoized function since each value is the maximum of the three possible paths to take.  

Finding the optimal alignment is then done by backtracking the matrix, by taking the shortest path from n,m to 0,0.
# What does it mean that a problem is NP-Complete?
A problem is NP-complete if they are __most likely__ hard to solve, where most likely hard to solve means there is no known way of calculating the solution or answering the problem formulation with a yes or no question, in polynomial time.

# If you want to prove that a new problem is NP-compelete, how would you do it?
First we show that our problem _P_ is in NP, by showing that there exists an verification algorithm in _P_.
If we know another problem, _Q_ that is NPC and we can apply a reduction, i.e. we have some way of mapping the output of _Q_ to our problem _P_ so that their outputs are equivalent, we know that _P_ is also NPC.  

# Explain how the first NP-complete problem was shown to be NP-complete.
Cook proved in 1971 that circuit satisfiability has NP-Complete.
It takes two steps to prove that a problem is NP-Complete
First we need an efficient way to tell if the solution is valid.
 
It is very easy in a circuit since we only need to plug in the input to the circuit and observe the output. 

Second we need to prove that circuit satisfiability is atleast as hard as all other problems in NP. Which is difficult when there are no other problems in NPC.

If we simplify and say that a circuit and a algorithm is equivalent and that from an algortihm a circuit can be compiled. 

From this the follwing (simplified) proof can be constructed:

* Each problem _X_ in NP has an efficient verficiation algorithm, _A_.
* A takes two parameters input _I_ for _X_ and the output from _X_, _S_.
* I.e. A(I, S) => Can deduce if S is a solution for _X_ given _I_.
* Let _I_ have _n_ bits and _S_ have _p(n)_ bits, where _p(n)_ is some polynomial amount of bits.
* Create a circuit that implements A (i.e. the circuit is the program/solution checker) and takes _n + p(n)_ bits of input data.
* Let _I_ be the constant length input, and _p(n)_ be the bits that the circuit SAT solver needs to find.
* We have now constructed an algorithm A that uses circuit satisfiablity (by checking if the solution is valid or not) to determine the solution to any problem _X_.

In short if we can determine the circuit A which can check the solution solve any problem in NP, i.e. given the problem and input, give us the answer yes or no.
Therefor we can determine that if we solve circuit satisifiability we can solve any other problem in NP.
This again works by giving equivalence between circuits and programs.

# Explain how it can be shown that Hamiltonian Cycle is NP-Complete.
A Hamiltonian Cycle is directed graph so that if we start in _s_ can we visit all nodes and still come back to _s_?
A Graph can be reduced to 3SAT problem, which is known to be NP-Complete. Therefor Hamiltonian Cycles are also NP-complete.

# Explain how the Traveling salesman problem is NP-Complete
TSP is the optimization problem of Hamiltonian Cycle, except the edges now weights instead. The question is formulated as: "Can we find a _tour_ (hamiltonian cycle) such that the total cost of the traversing the tour is less than _x_?
We can easily reduce the problem to finding a hamiltonian cycle, by setting the weights of the edges between adjacent nodes to one and two to others, if then we can find a hamiltonian cycle which the distance is equal to |Nodes| we can also solve TSP.
# Explain how it can be shown that graph coloring is NP-complete.
Graph coloring can be reduced to 3SAT.
# Explain what the simplex algorithm can do (but not how it works)

The simplex algorithm can take a maximizing function, with n variables bound by constraints. It uses some clever algebraic manipulation to jump from the next most promising (highest value of the maximizing function) intersection of the constraining function, until it finds the maximum value of the maximizing function. 
The algorithm always terminates since there are a finite amount of intersection, however there does not always exist a solution since the feasible region might be unbounded. 

# Explain what the branch-and-bound algoritm (förgrena-och-begränsa) is and how it can be exploited in integer linear programming

Branch-and-bound is paradigm used to explore possible better solutions by "branching" into tree where the next node takes a variant of its parent solution and tries to improve. This tree might become infintely large, so there must be a way to "bound" the exploration, i.e. if the child node found a worse solution we can stop exploring.

In integer programming we would like to still use the simplex algorithm, but we can't just round the solutions since that would be incorrect. Instead we try to relax the integer constraint on the decisions variables and find a solution which might contain an integer solution. So when we find a solution and some variable _xk_ is not an integer we add a restriction to the new exploratory node that variable must be atleast the floor of that number, or greater than the ceiling, and try to find a solution using that additional constraint. When we find an integer solution we save that in a variable _best_. If we later find a better solution we can remove all other nodes which had worse integer solution. Bounding. We also a fixed amount of nodes that can be constructed, _h_, so that we do not grow our tree to large.
