# parallel-programming
My parallel programming learning code snippets


## Pthreads
pthreads explaination

### Files
- helloWorld.c: spawns various pthreads, each of which prints its thread ID
- incVar.c: creates 3 pthreads that takes turn in incrementing a variable, which can only be accessed by one thread at the time (mutual exclusion) until it reaches 40 and then all threads stop
- producer-consumer.c: a number of pthreads are divided into producers (which increments the global variable "money") and consumers (which decrements said variable). The threads then randomly takes turn in producing or consuming the variable (each time incrementing or decrementing the variable if its respectively <20 or >0)
- sumVec.c: the program prepares an array of N numbers from 1 to N+1. It then subdivides the array into T arrays of N/T lenght. The threads then compute the sum of their portion of the array and then returns the sum. All sums are then added togheter to find the sum of all positions of the original array.

## OpenMP

## OpenMPI
