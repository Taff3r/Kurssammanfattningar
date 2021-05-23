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

