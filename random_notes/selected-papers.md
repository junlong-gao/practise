- GFS and BigTable
- Large-scale Incremental Processing (TiKV transaction model)
- Dynamo
- Spanner
- PolarFS
- Aurora (2 papers)
- In Search of an Understandable Consensus Algorithm (Raft)
- Design Trade offs of Data Access Methods (RUM conjecture)

### A Critique on Dynamo vs. Spanner.

Almost all storage systems will have to answer the following question:
"For a given piece of data, which node should be responsible for writing
it?"
There are 2 layers to this question: first is due to the fact that there will
be more than one storage node. Dynamo solved this using consistent hashing,
whereas Spanner is taking a range based sharding approach. The second is
because of redundancy: for availability requirements, even for the same piece
of data, it will have to be replicated across nodes. Then the replication
protocol will be determining which of the replica can handle the write. Dynamo uses its home-brew preference-list and sloppy quorum, whereas modern
architectures uses Paxos/Raft like Spanner/TiKV.

Consistency and Reads:
In Dynamo, any node in the preference list for the data can update the data.
In leader based protocol like Raft, only the leader can update the data.
Stale leader's data will be overwritten by the majority. Then, Dynamo will
suffer from write inconsistency which Raft cannot exhbit. However, Dynamo is
designed with this in mind and attach each version of data a version number.
In fact, since the history can branch out, a list of version numbers
(writer->revision number) is used to capture read->write causality. And these
revision numbers are like logical clocks and can be reconsolidated.

For the same reason, Dynamo cannot exhibit linearizable behavior: read will
inevitably see a vector clock, and cannot determine which revision is more
recent. For Spanner, read is linearizable due to its use of TrueTime. This
again involves the write process: when committing a write (a.k.a making it
visible), the coordinator node in Spanner simply waits long enough so that
the real point in time has passed the commit timestamp. Then, read in Spanner
will use a read timestamp and compare it with nodes' replication timestamp and
transaction timestamp. See more discussion in lease read below.

### PolarFS, Shared-Nothing vs. Shared-everything
[WIP]

### Spanner vs Raft Lease Read: Challenges and Solutions for Reading from Replicated State Machines

Raft protocol requires special treatments for implementing read. Note raft
uses leader to serialize write, so one majority of the hard problem like
conflicts/split-brain is not present. It is now just the problems of 1) read
reflects committed write 2) no stale read. This can be summarized as: when
reading the committed state from the leader, the leader must still be the
leader and has all the serialized writes so far.

 When a read is issued, it is forwarded to the Leader, yet the Leader needs
 to communicate (or simply commit a read-only record) a majority of the nodes
 for serving the read. The state machine replicated on each node effectively
 has a version, which is the same as the index of the log that has been
 committed. A read after write will need to read from the state machine whose
 version is higher than the write record in the log. Two anomalies can
 happen: 1. The leader is partitioned and is no longer the leader. It will
 thus cannot communicate with the majority (otherwise it will step down as a
 follower) 2. The follower received read request before receiving the write
 request. This does not mean the communication channel is out-of-order, it is
 just the implementation may have concurrency constructs processing incoming
 packets out of order, or, the follower is heavily partitioned and never saw
 the writes before. In the first case read will fail due to unable to
 replicated to a majority. In the second case it is more complicated, but can
 be mitigated when leader replicates its index for read in the read record,
 and out-of-order in the follower can be detected by comparing the read index
 with its own log. This index, should be taken as the commit index of the
 leader log, called Read-Index. For example, leader noticed that if to serve
 this read, the replicated state machine needs to be in version 5000 or
 higher (for linearizablity, it has to be the commit index of the log, but it
 does not has to be the latest write or the tail of the log: considering a
 write and read request send concurrently to the leader, there is no
 requirement for read index to be at least that write index in this case for
 linearizablity), as it has applied to log 5000, then the read request will
 need to also contain this 5000 log index. If follower receives write at 5000
 and a read at 5000, but processed read request first, it would reject the
 read request to avoid returning inconsistent data, effectively a failed
 replication.

Now, these are inefficient read implementations. Because this requires an
additional round trip for serving read. Though this can be mitigated by
batching, read perf will still suffer from high latency. Incidentally,
Spanner used Paxoe with a leader-lease based variant for implementing read,
and many popular raft based implementations used leader term-based lease.
Spanner folks will need to build the election protocol on Paxos, yet since
raft already has election protocol specified:
> Read-only operations can be handled without writing anything into the log.
> However, with no additional measures, this would run the risk of returning
> stale data, since the leader responding to the request might have been
> superseded by a newer leader of which it is unaware. Linearizable reads must
> not return stale data, and Raft needs two extra precautions to guarantee this
> without using the log. First, a leader must have the latest information on
> which entries are committed. The Leader Completeness Property guarantees that
> a leader has all committed entries, but at the start of its term, it may not
> know which those are. To find out, it needs to commit an entry from its term.
> Raft handles this by having each leader commit a blank no-op entry into the
> log at the start of its term. Second, a leader must check whether it has been
> deposed before processing a read-only request (its information may be stale
> if a more recent leader has been elected). Raft handles this by having the
> leader exchange heartbeat messages with a majority of the cluster before
> responding to read-only requests. Alternatively, the leader could rely on the
> heartbeat mechanism to provide a form of lease [9], but this would rely on
> timing for safety (it assumes bounded clock skew).

Finally, this paper:
https://www.usenix.org/system/files/conference/hotcloud17/hotcloud17-paper-arora.pdf
gives a good overview on how read in raft protocol can benefit from a combination
of leader based read and majority read. From Dynamo's sloppy quorum to today's
linearizable, we surely had come a long way.

To begin with Raft leader lease-based read, we can start from the mitigation
of follower out-of-order. The key idea is to ensure leader sees a majority
agrees with it. By getting a majority confirming their state is in sync with
itself, it can 1: confirm read at the index is a committed state (read
reflects write), 2: there cannot be a different leader that has committed an
overwritten state at the index (no stale read). Of course there can be a
concurrent write changing the state by that leader that not yet committed,
but any state returned by read after the read index is linearizable. The read
index: the index established when leader takes a read request, ensures
linearlizablity as soon as it is confirmed by a majority of the followers has
in-sync with its tail. This also opens for discussion of snapshot read (read
index is not the commit index of the leader log but some point in time in the
past), but we can address that in the Spanner's solution. This process can be
embedded in the frequent heartbeat messages. First of all, the leader does
not need to manually start a round of RPC for this ReadIndex: as long as it
receives a majority of heartbeat reply after this Read Index is established
(note follower does not need to look at this Read Index, it is only the
leader need to book keep this index to remember it is still leader at that
index), that means it has serialized all the writes before this read (read
reflects write), then it simply waits until a majority of followers has
committed the entry (which automatically happens as the replication process
continues), when it can serve the read (no stale read). This is much better
than manually start a round of RPC for this purpose.

Yet we can do better if we can assume some property of the clocks. Though
raft uses clocks extensively, its safety properties does not assume any clock
drift or clock skew. In reality we can assume bounded clock drift (not skew
though) and no clock jump backwards. Waiting for a reply from heartbeat with
the Read Index is just to confirm the leader is still the leader at up-to
this Read Index. Yet, from the raft protocol, we know the next new leader
(hence new writes) cannot appear until `leader heart beat timeout / max(clock
drift)`. We can assume `max(clock drift)` to be some reasonable number so
that this estimate with high probability is correct. Then we don't need Read
Index in the leader for book keeping if it is up-to-date for a read request.
This interval gives the lower bound of when the next write can happen in a
new, different leader. Second, there is no Read Index and leader does not
need to wait for the apply index to catch up with the tail of the log when
read was issued. In the window `[read request, read request + leader heart
beat timeout / max(clock drift)]`, the leader can serve the committed state
for read.

Note in figure 8 in the extended raft paper, there is a difference between
"replicated on a majority" and "committed", but our discussion is using the
notion of "committed" so this is not relevant in this writing.

Now, back to Spanner, where the paper writes:
> t_{safe}^{Paxos} is simpler: it is the timestamp of the highest-applied
> Paxos > write. Because timestamps increase monotonically and writes are
> applied in order, writes will no longer occur at or below t_{safe}^{Paxos}
> with respect to Paxos.

Spanner has a different read requirements: the system is supposed to support
snapshot read and linearizable reads. So a read will always get a timestamp
assigned. Ignore the transaction part, Spanner has to take a similar approach
in election protocol for its Paxos leader to advance, t_{safe}^{Paxos},
considering if there is no write, there is no way to advance that timestamp.
In many ways, leader based Paxos works the same as Raft by using the leader to
serialize writes. Spanner also keeps a lease in the Paxos leaders, which is
also the lower bound of when the next write can happen in a new leader. In
the Paxos protocol Spanner uses, the leader also talks to a majority of the
nodes to extend its lease and each replica will only vote once during a grant
lease period.