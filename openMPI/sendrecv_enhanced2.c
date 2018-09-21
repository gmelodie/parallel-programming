#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[]) {
    int npes, myrank;
    int buf;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    buf = myrank;

    MPI_Sendrecv_replace((void *) &buf, 1, MPI_INT, (myrank + 1) % npes, 0, (myrank + npes - 1) % npes, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);



    printf("Hey I'm %d, just received a message from %d\n", myrank, buf);

    MPI_Finalize();
}

