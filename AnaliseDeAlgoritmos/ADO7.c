#include <stdio.h>

#define MAX_MOEDAS 100
#define INFINITO 10000000

int obter_min_moedas(int moedas[], int troco, int tam_moedas) {
    int min_moedas = INFINITO;
    if (troco == 0)
        return 0;
    for (int i = 0; i < tam_moedas; i++) {
        if (troco >= moedas[i]) {
            int cont = 1 + obter_min_moedas(moedas, troco - moedas[i], tam_moedas);
            if (min_moedas > cont)
                min_moedas = cont;
        }
    }
    return min_moedas;
}

int main() {
    int moedas[] = {100, 10, 1};
    int troco = 123;
    int tam_moedas = sizeof(moedas) / sizeof(int);
    printf("Combinacoes possiveis para troco de %d centavos:\n", troco);
    for (int i = 0; i < tam_moedas; i++) {
        int qtd_moedas = troco / moedas[i];
        troco %= moedas[i];
        printf("%d moeda(s) de %d centavos\n", qtd_moedas, moedas[i]);
    }
    return 0;
}
