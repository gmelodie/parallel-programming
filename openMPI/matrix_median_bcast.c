#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define MASTER 0


void ordena_colunas(int *, int, int);
float calcula_mediana(int *, int);
void quicksort(int *, int, int, int);
int partition (int *, int, int, int);
void matrix_print(int **, int, int);
int **matrix_create(int, int);


int **matrix_create(int nrows, int ncols) {
    int **matrix = malloc(sizeof(int *) * ncols);
    for(int i = 0; i < ncols; i++)
        matrix[i] = malloc(sizeof(int) * nrows);

    return matrix;
}

void matrix_print(int **matrix, int nrows, int ncols) {
    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void quicksort(int *arr, int low, int high, int ncols) {
    int pi;
    if (low < high)  {
        pi = partition(arr, low, high, ncols);

        quicksort(arr, low, pi - 1, ncols);
        quicksort(arr, pi + 1, high, ncols);
    }
}

int partition (int *arr, int low, int high, int ncols) {
    int i, j, swap, pivot;
    pivot = arr[high*ncols];

    i = (low - 1);

    for (j = low; j <= high - 1; j++) {
        if (arr[j*ncols] <= pivot) {
            i++;

            swap = arr[i*ncols];
	    arr[i*ncols] = arr[j*ncols];
	    arr[j*ncols] = swap;
        }
    }

    swap = arr[(i + 1)*ncols];
    arr[(i + 1)*ncols] = arr[high*ncols];
    arr[high*ncols] = swap;

    return (i + 1);

}



void ordena_colunas(int *matrix, int nrows, int ncols) {
  int j;
  for (j = 0; j < ncols; j++) {
      quicksort(&matrix[j], 0, nrows-1, ncols);
  }
}


float calcula_mediana(int *vec, int nelem) {
    float median = 0;

    median = vec[nelem/2];
    if(nelem % 2 == 0)  {
        median += vec[nelem/2 - 1];
        median *= 0.5;
    }

    return median;
}



int main(int argc, char *argv[]) {
    int nrows, ncols, rank, nslaves, chunksize, normal_chunksize, last_chunksize;
    int *matrix = NULL, **columns;
    float *medians = NULL;
    int i, j;
    FILE *arquivo_entrada,*arquivo_saida;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nslaves);
    nslaves--; // comm size minus master


    if(rank == MASTER) {

        if(!(arquivo_entrada=fopen("entrada.txt","r"))) {
          printf("Erro ao abrir entrada.txt como leitura! Saindo! \n");
          return(-1);
        }

        if(!(arquivo_saida=fopen("saida.txt","w+"))) {
          printf("Erro ao abrir/criar saida.txt como escrita. Saindo! \n");
          return(-1);
        }

        fscanf(arquivo_entrada, "%d %d", &nrows, &ncols);

        matrix = (int *) malloc ( nrows * ncols * sizeof(int));

        medians = (float *) malloc (ncols * sizeof (float) );

        for(i = 0; i < nrows; i++)
          for(j = 0; j < ncols; j++)
          fscanf(arquivo_entrada, "%d", &matrix[i*ncols+j]);

        ordena_colunas(matrix, nrows, ncols);

        // form columns
        columns = matrix_create(ncols, nrows);

        for(i = 0; i < ncols; i++)
            for(j = 0; j < nrows; j++)
                columns[i][j] = matrix[nrows*j + i];

        matrix_print(columns, ncols, nrows);


        MPI_Request requests[nslaves];

        // send msg to slaves
        chunksize = ncols / nslaves;
        normal_chunksize = ncols / nslaves;
        last_chunksize = chunksize + ncols % nslaves;
        MPI_Bcast(&chunksize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Send(&last_chunksize, 1, MPI_INT, nslaves, 0, MPI_COMM_WORLD);
        MPI_Bcast(&nrows, 1, MPI_INT, 0, MPI_COMM_WORLD);

        for(i = 1; i <= nslaves; i++) {

            if(i == nslaves)
                chunksize = last_chunksize;


            // send load
            for(j = 0; j < chunksize; j++)
                MPI_Send(columns[j + normal_chunksize * (i - 1)], nrows, MPI_INT, i, 0, MPI_COMM_WORLD);

            // Irecv ans
            MPI_Irecv(&medians[(i - 1) * normal_chunksize], chunksize, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &requests[i-1]);
        }

        // wait for responses
        for(i = 0; i < nslaves; i++)
            MPI_Wait(&requests[i], MPI_STATUS_IGNORE);

        for(j = 0; j < ncols; j++)
            fprintf(arquivo_saida,"%.1f, ",medians[j]);
        fprintf(arquivo_saida, "\n");
    }


    // I'M A SLAVE
    else {
        // recv chunksize
        MPI_Bcast(&chunksize, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

        // recv last_chunksize if I'm last slave, and overwrite chunksize
        if(rank == nslaves)
            MPI_Recv(&chunksize, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // recv nrows
        MPI_Bcast(&nrows, 1, MPI_INT, 0, MPI_COMM_WORLD);

        float ans[chunksize];
        int cols[chunksize][nrows];

        // recv columns
        for(j = 0; j < chunksize; j++)
            MPI_Recv(&cols[j], nrows, MPI_INT, MASTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(i = 0; i < chunksize; i++)
            ans[i] = calcula_mediana(cols[i], nrows);

        // send ans to master
        MPI_Send(ans, chunksize, MPI_FLOAT, MASTER, 0, MPI_COMM_WORLD);
    }

    // FREE AND TERMINATE
    if(rank == MASTER) {
        fclose(arquivo_entrada);
        fclose(arquivo_saida);
        free(medians);
        free(matrix);
        for(i = 0; i < ncols; i++)
            free(columns[i]);
        free(columns);
    }

    MPI_Finalize();
    return(0);
}

