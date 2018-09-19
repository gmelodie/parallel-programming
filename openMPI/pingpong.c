
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>


int main(int argc, char *argv[]) {
    int npes, myrank;
    char recv_buf[10], send_buf[10];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if(npes != 2) {
        printf("Error: must have exactly 2 players, got %d\n", npes);
        MPI_Finalize();
    }


    if(myrank == 0)
        strcpy(send_buf, "pong");
    else
        strcpy(send_buf, "ping");


    for(int i = 0; i < 5; i++) {
        MPI_Send((void *) send_buf, 10, MPI_CHAR, (myrank + 1) % npes, 0, MPI_COMM_WORLD);
        MPI_Recv((void *) recv_buf, 10, MPI_CHAR, (myrank + npes - 1) % npes, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%s\n", recv_buf);
    }


    MPI_Finalize();
}

