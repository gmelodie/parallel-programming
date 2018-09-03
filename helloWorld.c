#include <stdio.h>
#include <pthread.h>


#define NTHREADS 30

void *hello(void *arg) {
    printf("Hello world! I'm thread #%d\n", (int)arg);
}

int main() {
    int i;
    pthread_t threads[NTHREADS];

    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&threads[i], NULL, hello, (void *) i);
    }

    pthread_exit(NULL);
}
