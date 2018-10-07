# parallel-programming

My parallel programming learning code snippets

## Pthreads

POSIX Threads, usually referred to as pthreads, is an execution model that exists independently from a language, as well as a parallel execution model. It allows a program to control multiple different flows of work that overlap in time. Each flow of work is referred to as a thread, and creation and control over these flows is achieved by making calls to the POSIX Threads API.Most pthreads functions return 0 on success, and an error number on failure. Note that the pthreads functions do not set ```errno```.  For each of the pthreads functions that can return an error, POSIX.1-2001 specifies that the function can never fail with the error EINTR.

### Files

- helloWorld.c: spawns various pthreads, each of which prints its thread ID
- incVar.c: creates 3 pthreads that takes turn in incrementing a variable, which can only be accessed by one thread at the time (mutual exclusion) until it reaches 40 and then all threads stop
- producer-consumer.c: a number of pthreads are divided into producers (which increments the global variable "money") and consumers (which decrements said variable). The threads then randomly takes turn in producing or consuming the variable (each time incrementing or decrementing the variable if its respectively <20 or >0)
- sumVec.c: the program prepares an array of N numbers from 1 to N+1. It then subdivides the array into T arrays of N/T lenght. The threads then compute the sum of their portion of the array and then returns the sum. All sums are then added togheter to find the sum of all positions of the original array.

## OpenMP

OpenMP (Open Multi-Processing) is an application programming interface (API) that supports multi-platform shared memory multiprocessing programming in C, C++, and Fortran, on most platforms, instruction set architectures and operating systems, including Solaris, AIX, HP-UX, Linux, macOS, and Windows. It consists of a set of compiler directives, library routines, and environment variables that influence run-time behavior.

## OpenMPI

Open MPI (based on Message Passing Interface) is also a programming platform, but instead provides one the ability to parallelize code over a (non-)homogenous distributed system (e.g., a supercomputer).  For instance, it's possible to parallelize an entire program over a network of computers, or nodes, which communicate over the same network.  Since these nodes are essentially computers, they have their own memory layout and their own set of cores (see OpenMP description).  Communication between nodes, when compared to shared memory systems, can be difficult and is usually expensive.
