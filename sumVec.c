#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100
#define T 10

void *sum(void *arg) {
    int index = (int)arg;
    printf("Starting from %d\n", index);
}

int main() {
    int *vec = malloc(sizeof(int)*N);
    int i;
    pthread_t threads[T];

    for(i = 0; i < N; i++) {
        vec[i] = rand()%N;
    }


    for(i = 0; i < N; i += N/T) {
        pthread_create(&threads[i], NULL, sum, (void*)i);
    }


    free(vec);
    return 0;
}
