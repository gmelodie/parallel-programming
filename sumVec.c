#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10e+4
#define T 100

typedef struct {
    int *vec;
    int index;
} vec_slice;

void *sum(void *arg) {
    vec_slice *slice = (vec_slice *) arg;
    int sum = 0;

    for (int i = slice->index; i < slice->index + N/T; i++)
        sum += slice->vec[i];


    printf("Sum = %d\n", sum);

    return (void *) sum;
}


int main() {
    int *vec = malloc(sizeof(int)*N);
    int i, total_sum = 0;
    void *aux;
    pthread_t threads[T];

    for(i = 0; i < N; i++) {
        //vec[i] = rand()%N;
        vec[i] = i+1;
        printf("i = %d\n", i);
    }

    for(i = 0; i < T; i++) {
        vec_slice *slice = malloc(sizeof(vec_slice));
        slice->vec = vec;
        slice->index = i*N/T;

        pthread_create(&threads[i], NULL, sum, (void*) slice);
    }

    for(i = 0; i < T; i++) {
        pthread_join(threads[i], &aux);
        total_sum += (int) aux;
    }

    printf("%d\n", total_sum);

    free(vec);
    return 0;
}
