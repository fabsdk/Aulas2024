#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_homens = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_mulheres = PTHREAD_COND_INITIALIZER;

int homens_aguardando = 0;
int mulheres_aguardando = 0;
int casais_formados = 0;

void *homem(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        homens_aguardando++;
        if (mulheres_aguardando > 0) {
            homens_aguardando--;
            mulheres_aguardando--;
            casais_formados++;
            printf("Homem e mulher formaram um par e estão dançando! Total de casais formados: %d\n", casais_formados);
            pthread_cond_signal(&cond_mulheres);
            pthread_cond_signal(&cond_homens);
        } else {
            pthread_cond_wait(&cond_homens, &mutex);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1); 
    }
    return NULL;
}

void *mulher(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        mulheres_aguardando++;
        if (homens_aguardando > 0) {
            mulheres_aguardando--;
            homens_aguardando--;
            casais_formados++;
            printf("Mulher e homem formaram um par e estão dançando! Total de casais formados: %d\n", casais_formados);
            pthread_cond_signal(&cond_homens);
            pthread_cond_signal(&cond_mulheres);
        } else {
            pthread_cond_wait(&cond_mulheres, &mutex);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t homens[5], mulheres[5];
    int i;

    for (i = 0; i < 5; i++) {
        pthread_create(&homens[i], NULL, homem, NULL);
        pthread_create(&mulheres[i], NULL, mulher, NULL);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(homens[i], NULL);
        pthread_join(mulheres[i], NULL);
    }

    return 0;
}
