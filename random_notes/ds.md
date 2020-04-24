## Consistency Levels
### Linearizabile, Sequential, Read-after-Write, Monotonic View, Eventual
This paper gives a very good overview and rigor treatment of
various week consistency levels.
https://arxiv.org/pdf/1512.00168.pdf

- Sequential:
Multiple threads' history can be merged into a single history which respects
program order and is a valid execution history when it is running on a single
thread.
This is sequential:
```
  write(3)       read()->3
|----------|   |------------|

    write(4)                 read()->4
  |-----------------|     |-----------|
```
As a realization:
```
W3 R3 W4 R4
```

This is also sequential:
```
  write(4)          read()->4
|----------|     |------------|

    write(3)           read()->3
  |-----------|      |-----------|
```
As a realization:
```
W3 R3 W4 R4
```

- Linearizabile:
The problem about sequential consistency is that it is not composable and
does not respect real-time ordering.

## Transaction and ACID
### Atomicity, Consistency, Isolation and Durability
### Isolation Levels, Weak Isolation
    - Serializable
      no anomalies
    - Repeatable Read
      avoid dirty read and non-repeatable read, but can get phantoms
    - Read Committed
      avoid dirty read
    - Read Uncommitted
    Weak Isolation is treated in http://pmg.csail.mit.edu/papers/adya-phd.pdf
    and also discussed in the context of ANSI SQL isolation level:
    https://www.microsoft.com/en-us/research/wp-content/uploads/2016/02/tr-95-51.pdf

### Snapshot Isolation
This is alternative to repeatable read. It avoids phantoms, but
can result in write skews. This is because it uses MVCC for reads
and only lock on writes. If there is no write conflicts, txn can
still commit.


## Two-Phase Commit and Their Friends

## Consensus Protocols
### Replicated State Machine and Replicated Log
### The Raft Protocol
### Lease Read and Consistency
### The Paxos Protocol


## The CAP Theorem
### Consistency, Availability and Network Partition Tolerance


## Consistent Hashing
Use hash to distributed key onto different server nodes, but has the risk
of re-hashing when servers come and go. Also it is not flexible to consider
different server nodes with different capacity.

For each key and server name, hash them onto a ring.
For each key, follow on the ring and go counterclock wise to find the server
node hash. If the hash value ranges from [0, M), this is effectively
identifying M with 0.

From the implementation perspective, each server node has a sorted table of
virtual node -> begin hash. Given hash h, walk the list from the beginning to
find the smallest `begin hash` >= h. If there is no such `begin hash`, use
the largest begin hash. This can be done using binary search.

### Virtual Nodes
Using server node directly has the following problem: it is oblivious to the
heterogeneity of the nodes, and since the number of server nodes are
relatively small and limited by physical machine numbers, this can be easier
to result in skewed distribution of the keys, defeating the purpose of
sharding.

For better load balancing, instead of using real nodes, use virtual nodes:
for each server node, assigning it a collection of virtual nodes, and have a
mapping from virtual node -> server node.

Problem: using virtual nodes greatly increased the size of the table. This
can impact look up performence.

### Chord Algorithm
Using finger table (WIP)

### Range based sharding and Hash based sharding
cf. https://tikv.org/deep-dive/scalability/data-sharding/
- Sharding by hash.
Map key to node using its hash
pro: good balance, uniform distribution for large number of nodes and good hash.
con: cannot do range query efficiently.

- Sharing by Key Ranges.
Map key to a node using the range it belongs to
pro: good range query
con: can result in hot spots for sequential operations.

## On Distributed Logs and Ordering of Events
