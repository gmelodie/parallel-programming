#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NTHREADS 3
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;


void *inc_count(void *arg) {
    int i = (int) arg;

    while(1) {
        // lock
        pthread_mutex_lock(&mutex);
        // increment
        printf("thread %d: %d\n", i, count);
        if(count == 40){
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        count++;
        // unlock
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t threads[NTHREADS];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, inc_count, (void *)i);

    for(int i = 0; i < NTHREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    return 0;
}
