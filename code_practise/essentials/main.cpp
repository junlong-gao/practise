#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;
/*
line seperated array
*/
vector<vector<int>> readArray(int comp = 1) {
   int len;
   vector<vector<int>> ret;
   cin >> len;
   while (len--) {
      ret.emplace_back();
      for (int i = 0; i < comp; ++i) {
         int v;
         cin >> v;
         ret.back().push_back(v);
      }
   }

   return ret;
}

int readInt() {
   int val;
   cin >> val;
   return val;
}

vector<int> concat(const vector<vector<int>> &in) {
   vector<int> ret;
   for (const auto& v : in) {
      for (const auto& e : v) {
         ret.push_back(e);
      }
   }
   return ret;
}

/*
write
*/
void writeArray(const vector<int>& out) {
   for (auto v : out) {
      cout << v << endl;
   }
}

/*
What is the value of studying algorithms? It is fun to solve problems in
their own right, but writing programs inevitably faces 2 challenges:
1. What exactly should the program do? (i.e. Did we code the right thing?)
2. Does the program do what it is supposed to be doing? (i.e. Did we code the
thing right?)

When we say a program is "correct", more often than not we are referring to
2). However, without a full grasp of 1), it is impossible to talk about 2).
You cannot tell whether the program is doing the right thing if you are
unsure about what is right to begin with!

For sequential programs, both 1) and 2) are solved in a rather satisfactory
manner in that there are automation tools to generate program for a given
specification (that is, we do not worry about 2), and there are many tools
for us to do 1) in a natural and easy manner (type systems and axiom based
semantics). Most of the programing tasks does not come in a formal form
regarding 1), and it is up to engineer's task to use the right tool (or,
language) to flush out a formal specification before working on 2).

However, most of us simply have a rough idea about what it should be doing
and immediately start coding. We call it a day after we use test cases to
establish 2). This is nonsense, it is like publishing a mathematical
theorem without giving proof, and only give constructive procedures showing
it is true for some finite set of instances.

Designing algorithm is hard, and it is harder to proving 2). We need all
the help we can get. One such help is to use the systematic methods for
proving 2) as guiding principle in designing the algorithm (that is, even
though you have not yet found an algorithm, think about how you would like
to prove its correctness when you perform some step in the unfinished
algorithm), another one would be using high level declarative constructs as
much as possible (that is, the language you use to describe the program is
as close as the mathematical object you will use to prove 2). Both of them
concerns the semantics of a program, and the first one is based on Hoare
logic while the second one is so-called denotational semantics.

I personally find Hoare's approach is more feasible. Not only because it
allows me to reuse and revisit existing algorithms I learnt, but also allow
me to include complexity analysis. Programing languages that uses
denotational semantics for formally reasoning about the code are usually
based on lambda calculus. They are equally powerful in expressiveness but
less transparent in complexity analysis. Most of my work involves writing
programs which are performance critical: certain resources like cpu time,
memory, network, disk access, etc are expansive and equally important as
correctness.

It is not to say denotational semantics are not useful for me. I am also a big
OCaml fan and interested in type systems. I have a personal project which is
not performance critical (yet) writting in OCaml, which I have considerable
exposure to the tool. For the sake of general algorithm analysis, I will still
use an imperative programming language here.

The imperative language I am using here does not really matter, it is
really just because I am more familiar with C++. In fact I will stick with
Hoare's construct as much as possible and avoid using fancy template
systems or runtime type information. If an algorithm works for intergers, I
will not try to generalize it.

The focus of the algorithm presentation will be Hoare triples:
   {P}S{Q}
For data structures, I would also add:
   Inv => P
   Q => Inv
   -------------------------
   {P} DataStuctureMethod {Q}
When involving recursions, use induction to establish partial correctness. For
termination it is tricker.

By studying how to formally argue these algorithms are correct, hopefully I can
get better in constructing correct algorithms for new problems.

                                      ... for eloquent insistence and practical
                                 demonstration that programs should be composed
                              correctly, not just debugged into correctness ...
                  -- A.M. Turing Award Citation for Edsger Wybe Dijkstra, 1972
*/
/*************************************************/

/*
Fundamentals
- sorting and searching
- priority queue and heapsort
- order statistics
*/

int binarySearch(
   const vector<int> &input,
   const int target) {
   /*
   Pre: input is sorted
   Post: l == r
         /\ max_(0, {k | k \in [0, input.size()) /\ input[k] <= e})
   */
   int l = 0; int r = input.size();

   while (l != r) {
      /*
      Inv: \A e \in input[0, l), e <= target
           /\ \A e \in input[r, input.size), e > target
           /\ l <= r
      */
      const int mid = l + (r - l) / 2;
      if (input[mid] <= target) {
         l = mid + 1;
      } else {
         r = mid;
      }
   }

   /*
   By Inv, l - 1 gives the post condition
   */
   return l - 1;
}

/*************************************************/

/*
Foundational Data Structures
- linked list
- stack and queue
- union find
- trees
*/
struct union_find {
   /*
   representation invariant
   1. tree_depth(x) <= rank(x)
   2. p(x) is an ancestor of x (we will need a stronger one for complexity)
   */
   vector<int> rank, p;
   union_find(int count) {
      rank.resize(count, 0);
      for (int i = 0; i < count; ++i) {
         p.push_back(i);
      }
   }

   int find(int x) {
      if (p[x] == x) return x;
      return (p[x] = find(p[x]));
   }

   void link(int x, int y) {
      int px = find(x);
      int py = find(y);

      if (px == py) return;
      if (rank[px] > rank[py]) {
         p[py] = px;
      } else {
         p[px] = py;
         if (rank[px] == rank[py]) {
            rank[px]++;
         }
      }
   }
};

/*************************************************/

/*
Foundational Graph Algorithms
- dfs and bfs
- connected components and topological sorting
- spanning trees
*/

/*
There are at least 2 ways to do topological sorting, bfs based or
dfs based.
*/
vector<int> topological_sorting_bfs(
   const vector<vector<int>>& g) {
   /*
   Pre: g is a loop free directed graph represented via adjcent list.
   Post: an array ret so that (u, v) \in g => idx(u) < idx(v)
   */

  int n = g.size();
  vector<int> in(n, 0);

  for (int v = 0; v < n; ++v) {
     for (auto u : g[v]) {
        in[u]++;
     }
  }

  vector<int> ret;
  deque<int> q;
  vector<bool> visited(n, false);

  for (int v = 0; v < n; ++v) {
     if (in[v] == 0) {
        q.push_back(v);
        visited[v] = true;
     }
  }

  while (q.size()) {
     /*
     Inv:
     (1) \A v \in G.V, visited[v] = (v \in ret \/ v \in q)
     (2) \A u \in (G \ ret).V, in_degree(u) = in[u]
     (3) \A u \in ret, (v, u) \not \in E
     (4) \A u, v \ in ret, (u, v) \in E => idx(ret, u) < idx(ret, v)
     (5) \A u \in G.V \ {ret \union q}, \E v \in q, v ~> u

     (1) holds and maintains. For (2), consider pushing v into ret, then
     in order to adjust the in_degree, we need to remove the affected vertex
     in G \ (ret \union {v}). Finally, (2) => (3) => (4) when pushing v into ret.

     (5) is maintained by arguing that poping v out of the queue is justified
     by pushing immeidate neighbour into the queue, thus (5) holds.
     To see (5) holds initially is to see if u is not reachable, G is divided
     into at least 2 connected components: first containing initial q, second
     being the rest. But since G is loop free, so is the second component, then
     it must have a node with in degree 0, contradiction.

     Note that the "true" invariant is (2). Both (3) and (4) are derived. But
     keeping them in the Inv makes arguing the final post condition easier.

     Now when q is empty, (5) shows G.v = ret, and (4) completes the proof.

     Termination:
     Let V = |q| + sum_{v \in G \ ret} in[v]
     Note that V <= 0 => q.size() == 0, and V is decreasing monotonically by
     the fact that pushing into queue requires decreasing in.
     */
     auto v = q.front(); q.pop_front();
     ret.push_back(v);

     for (auto u : g[v]) {
        if (visited[u]) continue;
        in[u]--;
        if (in[u] == 0) {
           q.push_back(u);
           visited[u] = true;
        }
     }
  }

  return ret;
}
/*************************************************/

/*
Advanced Algorithm Design Techniques
- combinatory search
- dynamic programming
- greedy techniques
*/
/*************************************************/

/*
Advanced Graph Algorithms
- single source shortest path
- dijkstra algorithm
- all pair shortest path
*/
/*************************************************/

/*
Advanced Data Structure and Algorithms
- range queries (binary indexed tree and
  higher dimensions)
- Merkle trees (hash tree)
- kmp and aho-corasick automata
- moore's voting algorithm
*/
/*************************************************/

/*
Selected Topics on Parser Design
- an expression evaluator
- find all atoms in canonical expression
*/
/*************************************************/

/*
Some random driver.
int main() {
  writeArray(topological_sorting_bfs(
     {
        {},
        {0},
        {0},
        {1, 2}
     }
  ));
  return 0;
}
*/