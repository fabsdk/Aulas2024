#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um objeto
struct Objeto {
    int peso;
    int valor;
};

// Função de comparação para ordenar os objetos pelo valor específico (valor/peso)
int comparar(const void* a, const void* b) {
    double razao_a = ((struct Objeto*)a)->valor / (double)((struct Objeto*)a)->peso;
    double razao_b = ((struct Objeto*)b)->valor / (double)((struct Objeto*)b)->peso;
    if (razao_a > razao_b) return -1;
    else if (razao_a < razao_b) return 1;
    else return 0;
}

// Função para resolver o problema da mochila fracionária
double mochila_fracionaria(struct Objeto objetos[], int n, int capacidade) {
    // Ordena os objetos pelo valor específico (decrescente)
    qsort(objetos, n, sizeof(struct Objeto), comparar);

    double valor_total = 0.0;
    int capacidade_atual = capacidade;

    for (int i = 0; i < n; ++i) {
        if (objetos[i].peso <= capacidade_atual) {
            // Coloca o objeto inteiro na mochila
            valor_total += objetos[i].valor;
            capacidade_atual -= objetos[i].peso;
        } else {
            // Coloca uma fração do objeto na mochila
            valor_total += (capacidade_atual / (double)objetos[i].peso) * objetos[i].valor;
            break; // Mochila está cheia
        }
    }

    return valor_total;
}

int main() {
    int capacidade = 50;
    struct Objeto objetos[] = {
        {40, 840},
        {30, 600},
        {20, 400},
        {10, 100},
        {20, 300}
    };
    int n = sizeof(objetos) / sizeof(objetos[0]);

    double valor_maximo = mochila_fracionaria(objetos, n, capacidade);
    printf("Valor maximo da mochila fracionaria: %.2lf\n", valor_maximo);

    return 0;
}
