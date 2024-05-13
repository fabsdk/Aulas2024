#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define TEMPO_MAX_PENSANDO 3
#define TEMPO_MAX_COMENDO 2

pthread_mutex_t garfo[NUM_FILOSOFOS];
pthread_t filosofo[NUM_FILOSOFOS];
int estado[NUM_FILOSOFOS];

void *filosofoAcao(void *arg) {
    int id = *((int *)arg);
    int garfoEsquerdo = id;
    int garfoDireito = (id + 1) % NUM_FILOSOFOS;

    while (1) {

        printf("Filósofo %d está pensando.\n", id);
        estado[id] = 0;
        sleep(rand() % TEMPO_MAX_PENSANDO + 1);

        pthread_mutex_lock(&garfo[garfoEsquerdo]);
        printf("Filósofo %d pegou o garfo esquerdo.\n", id);

        pthread_mutex_lock(&garfo[garfoDireito]);
        printf("Filósofo %d pegou o garfo direito e está comendo.\n", id);
        estado[id] = 1;
        sleep(rand() % TEMPO_MAX_COMENDO + 1);

        pthread_mutex_unlock(&garfo[garfoEsquerdo]);
        printf("Filósofo %d soltou o garfo esquerdo.\n", id);
        pthread_mutex_unlock(&garfo[garfoDireito]);
        printf("Filósofo %d soltou o garfo direito.\n", id);
    }
    return NULL;
}

int main() {
    int i;
    srand(time(NULL));

    for (i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_init(&garfo[i], NULL);
    }

    for (i = 0; i < NUM_FILOSOFOS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&filosofo[i], NULL, filosofoAcao, (void *)id);
    }

    for (i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(filosofo[i], NULL);
    }

    for (i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_destroy(&garfo[i]);
    }

    return 0;
}
