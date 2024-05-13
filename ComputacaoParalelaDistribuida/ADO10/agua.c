#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_H_ATOMS 5
#define NUM_O_ATOMS 3

sem_t h_sem, o_sem;

void *h_atom(void *arg) {
    int *id = (int *)arg;
    printf("Átomo de H%d aguardando reação...\n", *id);
    sem_wait(&h_sem); 
    sem_wait(&o_sem); 
    printf("Dois átomos de H%d e um de O prontos para reagir, produzindo água.\n", *id);
    sem_post(&o_sem); 
    sem_post(&h_sem);
    pthread_exit(NULL);
}

void *o_atom(void *arg) {
    int *id = (int *)arg;
    printf("Átomo de O%d aguardando reação...\n", *id);
    sem_wait(&o_sem); 
    printf("Dois átomos de H e um de O%d prontos para reagir, produzindo água.\n", *id);
    sem_post(&o_sem);
    sem_post(&h_sem); 
    sem_post(&h_sem); 
    pthread_exit(NULL);
}

int main() {
    pthread_t h_threads[NUM_H_ATOMS], o_threads[NUM_O_ATOMS];
    int h_ids[NUM_H_ATOMS], o_ids[NUM_O_ATOMS];
    
    sem_init(&h_sem, 0, 2);
    sem_init(&o_sem, 0, 1); 

    for (int i = 0; i < NUM_H_ATOMS; i++) {
        h_ids[i] = i + 1;
        pthread_create(&h_threads[i], NULL, h_atom, &h_ids[i]);
    }

    for (int i = 0; i < NUM_O_ATOMS; i++) {
        o_ids[i] = i + 1;
        pthread_create(&o_threads[i], NULL, o_atom, &o_ids[i]);
    }

    for (int i = 0; i < NUM_H_ATOMS; i++) {
        pthread_join(h_threads[i], NULL);
    }

    for (int i = 0; i < NUM_O_ATOMS; i++) {
        pthread_join(o_threads[i], NULL);
    }

    sem_destroy(&h_sem);
    sem_destroy(&o_sem);

    return 0;
}
