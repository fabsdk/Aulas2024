#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_LEITORES 3
#define NUM_ESCRITORES 2

sem_t mutex, db, leitores;
int num_leitores = 0;

void *leitor(void *arg) {
    int id = *(int *)arg;
    while (1) {
        sem_wait(&leitores);
        sem_wait(&mutex);
        num_leitores++;
        if (num_leitores == 1) {
            sem_wait(&db);
        }
        sem_post(&mutex);
        sem_post(&leitores);

        printf("Leitor %d está lendo.\n", id);

        sem_wait(&mutex);
        num_leitores--;
        if (num_leitores == 0) {
            sem_post(&db);
        }
        sem_post(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

void *escritor(void *arg) {
    int id = *(int *)arg;
    while (1) {
        sem_wait(&db);
        printf("Escritor %d está escrevendo.\n", id);
        sem_post(&db);

        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads_leitores[NUM_LEITORES], threads_escritores[NUM_ESCRITORES];
    int ids_leitores[NUM_LEITORES], ids_escritores[NUM_ESCRITORES];
    int i;

    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);
    sem_init(&leitores, 0, 1);
    
    for (i = 0; i < NUM_LEITORES; i++) {
        ids_leitores[i] = i + 1;
        pthread_create(&threads_leitores[i], NULL, leitor, &ids_leitores[i]);
    }

    for (i = 0; i < NUM_ESCRITORES; i++) {
        ids_escritores[i] = i + 1;
        pthread_create(&threads_escritores[i], NULL, escritor, &ids_escritores[i]);
    }

    for (i = 0; i < NUM_LEITORES; i++) {
        pthread_join(threads_leitores[i], NULL);
    }
    for (i = 0; i < NUM_ESCRITORES; i++) {
        pthread_join(threads_escritores[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&db);
    sem_destroy(&leitores);

    return 0;
}
