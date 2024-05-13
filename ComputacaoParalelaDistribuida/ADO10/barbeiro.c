#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CADEIRAS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_barbeiro = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_cliente = PTHREAD_COND_INITIALIZER;

int clientes_aguardando = 0;
int cabelo_sendo_cortado = 0;

void *barbeiro(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (clientes_aguardando == 0) {
            printf("Barbeiro: Dormindo...\n");
            pthread_cond_wait(&cond_barbeiro, &mutex);
        }
        clientes_aguardando--;
        cabelo_sendo_cortado = 1;
        printf("Barbeiro: Cortando cabelo do cliente %d\n", clientes_aguardando + 1);
        pthread_mutex_unlock(&mutex);

        sleep(3); 

        pthread_mutex_lock(&mutex);
        cabelo_sendo_cortado = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *cliente(void *arg) {
    int id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    if (clientes_aguardando < NUM_CADEIRAS) {
        clientes_aguardando++;
        printf("Cliente %d: Entrou na barbearia.\n", id);
        if (cabelo_sendo_cortado == 0) {
            pthread_cond_signal(&cond_barbeiro);
        }
        pthread_mutex_unlock(&mutex);
    } else {
        printf("Cliente %d: Não há lugar para esperar. Saindo.\n", id);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t barbeiro_thread;
    pthread_t clientes_threads[NUM_CADEIRAS];

    pthread_create(&barbeiro_thread, NULL, barbeiro, NULL);

    int i, ids[NUM_CADEIRAS];
    for (i = 0; i < NUM_CADEIRAS; i++) {
        ids[i] = i + 1;
        pthread_create(&clientes_threads[i], NULL, cliente, &ids[i]);
        sleep(1);
    }

    pthread_join(barbeiro_thread, NULL);
    for (i = 0; i < NUM_CADEIRAS; i++) {
        pthread_join(clientes_threads[i], NULL);
    }

    return 0;
}
