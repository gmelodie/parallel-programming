#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[]) {
    int npes, myrank;
    int recv_buf, send_buf;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    send_buf = myrank;

    MPI_Send((void *) &send_buf, 1, MPI_INT, (myrank+1)%npes, 0, MPI_COMM_WORLD);
    MPI_Recv((void *) &recv_buf, 1, MPI_INT, (myrank+7)%npes, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);



    printf("Hey I'm %d, just received a message from %d\n", myrank, recv_buf);

    MPI_Finalize();
}

