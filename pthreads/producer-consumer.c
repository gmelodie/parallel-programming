#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NTHREADS 30
#define LOOP 20

int money = 20; // the element to be consumed and produced
pthread_mutex_t mutex;


void *producer(void *arg) {
    for(int i = 0; i < LOOP; i++){
        if(money < 20)
            money++;
        printf("money = %d\n", money);
    }
}

void *consumer(void *arg) {
    for(int i = 0; i < LOOP; i++){
        if(money > 0)
            money--;
        printf("money = %d\n", money);
    }
}

int main() {
    pthread_t consumers[NTHREADS];
    pthread_t producers[NTHREADS];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < NTHREADS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    for(int i = 0; i < NTHREADS; i++) {
        pthread_join(consumers[i], NULL);
        pthread_join(producers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}
