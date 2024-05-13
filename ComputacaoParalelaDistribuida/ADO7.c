#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5 
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0, out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *produtor(void *arg) {
    int i, item;

    for (i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100;

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) 
            pthread_cond_wait(&full, &mutex);

        buffer[in] = item;
        printf("Produzido: %d\n", item);

        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&empty); 
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *consumidor(void *arg) {
    int i, item;

    for (i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) 
            pthread_cond_wait(&empty, &mutex);

        item = buffer[out]; 
        printf("Consumido: %d\n", item);

        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t produtor_thread, consumidor_thread;

    pthread_create(&produtor_thread, NULL, produtor, NULL);
    pthread_create(&consumidor_thread, NULL, consumidor, NULL);

    pthread_join(produtor_thread, NULL);
    pthread_join(consumidor_thread, NULL);

    return 0;
}
