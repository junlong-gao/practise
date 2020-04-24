## Socket Programming and Networking
### The 5 Layer Model
### TCP Handshaking
https://networkengineering.stackexchange.com/questions/24068/why-do-we-need-a-3-way-handshake-why-not-just-2-way
In the establishment of the connection between client and server, both parties need to
confirm the other end acks its sequence number. This is because TCP is a bi-directional
protocol, which means after init of the connection, both parties should be able to send
data. There needs a point in time when both party knows the other ends has acked its
sequence number.

So, a potential handshaking can be like this:
```
Alice ---> Bob    SYNchronize with my Initial Sequence Number of X
Alice <--- Bob    I received your syn, I ACKnowledge that I am ready for [X+1]
Alice <--- Bob    SYNchronize with my Initial Sequence Number of Y
Alice ---> Bob    I received your syn, I ACKnowledge that I am ready for [Y+1]
```

After these 4 messages, both parties can start sending data, the connection is
now considered established.

Note that this is like 4 way handshake, but in reality TCP headers has 2 bit fields
SYN and ACK, and nothing prevents setting both of them:
```
Bob <--- Alice         SYN
Bob ---> Alice     SYN ACK
Bob <--- Alice     ACK
```
Now after this, both parties can start sending data.

SYN flooding is to send SYN without sending the final ACK, this will leave server with
many open connections and exhaust the resources.

### Principles of Reliable Data Transportation
- Sequence Numbers and Ack
  Ordered delivery
- Pipelines and Flow Control
  Batching, windows size negotiation
  Flow control is for the receiver to avoid overflowing the received buffer size.
  Received buffer size >= Outstanding received data + window size for more data to receive
  So window size <= RecvBuffer - Outstanding Data
- Timers
  Re-transmission control
### Congestion Control
   Congestion control is done by limiting the window size. Congestion control is due
   to the fact that sender and receiver are not only limited by their application logic,
   but also have an impact, and impacted by, the shared underlying links. Switches and
   routes have to serve multiple different TCP connections without these connections
   knowing each other. Large volume of data will resulting queuing delay and halt the
   entire network, and smaller volume of data will result in under utilization.

   > Given this overview of TCP congestion control, we’re now in a position
   > to consider the details of the celebrated TCP congestion-control
   > algorithm, which was first described in [Jacobson 1988] and is
   > standardized in [RFC 5681]. The algorithm has three major components: (1)
   > slow start, (2) congestion avoidance, and (3) fast recovery.

   The key idea behind various algorithms in congestion control is to use
   latency timeout and dup ACK as an indication for the current network
   status.

### TLS and Asymmetric Encryption

## IO
(https://www.oreilly.com/library/view/linux-system-programming/9781449341527/ch04.html)
### Non-blocking IO, AIO
https://medium.com/@copyconstruct/nonblocking-i-o-99948ad7c957
https://github.com/littledan/linux-aio
Here is a great quote:
> Input and output functions involve a device, like a disk or flash drive,
> which works much slower than the CPU. Consequently, the CPU can be doing
> other things while waiting for an operation on the device to complete. There
> are multiple ways to handle this:
>
> In the synchronous I/O model, the application issues a request from a thread.
> The thread blocks until the operation is complete. The operating system
> creates the illusion that issuing the request to the device and receiving the
> result was just like any other operation that would proceed just on the CPU,
> but in reality, it may switch in other threads or processes to make use of
> the CPU resources and to allow other device requests to be issued to the
> device in parallel, originating from the same CPU.
>
> In the asynchronous I/O (AIO) model, the application can submit one or many
> requests from a thread. Submitting a request does not cause the thread to
> block, and instead the thread can proceed to do other computations and submit
> further requests to the device while the original request is in flight. The
> application is expected to process completions and organize logical
> computations itself without depending on threads to organize the use of data.
>
> Asynchronous I/O can be considered “lower level” than synchronous I/O because
> it does not make use of a system-provided concept of threads to organize its
> computation. However, it is often more efficient to use AIO than synchronous
> I/O due the nondeterministic overhead of threads.

The core idea is: IO is 2 orders magnitude slower than instruction
executions. Some form of parallelization and callback is required to maximize
throughput. In the threading model, there is no callback, and threads are the
unit of parallelization, responsible for tracking IO completion. In the AIO
model, the kernel is responsible for tracking IO completion, and explicit
callback handling/polling is required.

aio naturally takes a form of vectored IO (see below). Also, it can setup
eventfds and used in epoll (see below).

### Poll, Select and Epoll
Level Triggered vs Edge Triggered:
In the linux IO model, level-triggered io interfaces are the ones application
"poll"s from the file descriptors. As long as the file descriptor is ready to do
IO, user world can ask for it and choose to perform IO on it. Edge-triggered, in
contrast, will require user to be reactive to events like IO ready, but if user
choose to consume part of the IO, the remaining state in the file descriptor will
not signal the user application.

Poll and Select are "Level-Triggered": given a set of file descriptors, they will
block only when none of them is ready. If any of them is ready to perform IO, they
will not block.

Signal Driven IO is "Edge Triggered", where user get a callback on IO ready, but if
the user consumes part of the IO and return, no new signal will be delivered despite
the fact that IO is still consumable.

Epoll works in both modes. epoll_create creates an epoll object, which will
be tracking user added fds and which of them are ready. User applications use
epoll_ctl to add fds to the watch list, and when they are ready kernel
automatically mark them to be in the ready state. Then, the user application
can use epoll_wait to block until any fd of the list is ready to use. This is
the default level-triggered mode: as long as the fd is ready to use,
epoll_wait will always return immediately without blocking. Epoll also works
by edge-triggered mode when adding a fd with EPOLLET flag. In this case
epoll_wait will block even if some fd is still consumable: as long as there is
no new data arrived at any of the fd since last epoll_wait call.

Popular library built on epoll: libev, libevent
### Scatter/Gather I/O
Vectorized read/write calls (readv/writev)
### Interrupts, DMA and mmap
mmap allows userlevel processes to map a portion of a file to its address space,
either for read (MMAP_PRIVATE) or read-write (MMAP_SHARED). The process can specify
the mmaped region for protection bits: read-only, write, or execute. When mapping as
read, (MMAP_PRIVATE), access is done as copy-on-write, and the underlying file, nor
other processes, can observe the mutation. When mapped as read-write, this becomes an
inter-process communication channel. mmap is a good way to read-write access of a file
in large portions, and is also a form of IPC. Unlike read()/write(), mmap does not incur
syscall copying back and forth, and seeking is pointer manipulation (much easier than lseek()).

## Virtual Memory
### Page Fault, Page Table Walk, MMU
### Stack, Heap and Memory Management
### How does GDB work?
https://eli.thegreenplace.net/2011/01/23/how-debuggers-work-part-1
https://eli.thegreenplace.net/2011/01/27/how-debuggers-work-part-2-breakpoints
https://eli.thegreenplace.net/2011/02/07/how-debuggers-work-part-3-debugging-information

ptrace is used to control a child process for debugging: peek and poke memory,
single stepping instructions. Single step will let kernel to stop the child at
the next instruction so the parent can take control.

traps are used to create breakpoints. A special family of instructions INT *
is used to allow cpu to run a signal handler as soon as the cpu sees this
instruction. This works just like a hardware interrupt. Debugger finds the
instruction in the child process to break, use ptrace to modify the
instruction at that location to be INT 3. When the child reaches that
location, an interrupt is triggered and signal handler will transfer the
control back to the debugger. In reality, of course, the OS will have is
signal handler installed first, and that handler will execute the kernel code
to trigger process rescheduling so the child process is paused, and debugger
process is running.

## Concurrency and Threading
### Threading Model
### Implement Thread Pool
### Synchronization Primitives
### High level Synchronization Problems
### Atomics and Memory Model
### Lockless Linked List (CAS insertion in the end, or in order)
### SkipList and Lockless Associative Data Structure (Redis?)
    http://zhangtielei.com/posts/blog-redis-skiplist.html

## Process, IPC, Signals and Interrupts
### What are Examples of IPC in Linux Kernel?
### How is concurrency actually achieved?
### The scheduling problem
### Compilers, Linkers, and ELF

## The File System
### Inodes and Metadata Organization
### BFF
### The File Abstraction: Unlink, Hardlinks, Open/Close