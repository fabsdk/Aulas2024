#include <stdio.h>

void selecaoParadas(int paradas[], int n, int distanciaMaxima) {
    int i = 0;
    int paradasSelecionadas = 0;

    while (i < n) {
        int proximaParada = paradas[i];
        printf("Parada %d selecionada.\n", proximaParada);
        paradasSelecionadas++;

        while (i < n && paradas[i] <= proximaParada + distanciaMaxima) {
            i++;
        }
    }

    printf("Total de paradas selecionadas: %d\n", paradasSelecionadas);
}

int main() {
    int paradas[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(paradas) / sizeof(paradas[0]);
    int distanciaMaxima = 30;

    selecaoParadas(paradas, n, distanciaMaxima);

    return 0;
}
