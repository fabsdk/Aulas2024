#include <stdio.h>

void troco_guloso(int troco, int moedas[], int qtd_moedas) {
    int i, qtd;

    for (i = 0; i < qtd_moedas; i++) {
        if (troco >= moedas[i]) {
            qtd = troco / moedas[i];
            printf("%d moedas de %d centavos\n", qtd, moedas[i]);
            troco -= qtd * moedas[i];
        }
    }
}

int main() {
    int troco = 123; // Valor do troco em centavos
    int moedas[] = {100, 50, 25, 10, 5, 1};
    int qtd_moedas = sizeof(moedas) / sizeof(moedas[0]);

    printf("Troco para: %d centavos\n", troco);
    troco_guloso(troco, moedas, qtd_moedas);

    return 0;
}
