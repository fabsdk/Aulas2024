#include <stdio.h>

#define MAX 1000


int saltoDoSapo(int pedras[], int n) {
    int saltos = 0;
    int i = 0;

    while (i < n) {
        if (i + pedras[i] >= n) {
            saltos++;
            break;
        } else {
            int maxAlcance = -1;
            int proximaPedra = i;

            for (int j = i + 1; j <= i + pedras[i]; j++) {
                if (j + pedras[j] > maxAlcance) {
                    maxAlcance = j + pedras[j];
                    proximaPedra = j;
                    printf("proxima pedra: %d\n", proximaPedra);
                }
            }

            i = proximaPedra;
            saltos++;
        }
    }

    return saltos;
}

int main() {
    int n = 6;
    int pedras[] = {2, 3, 1, 4, 2, 1};

    int resultado = saltoDoSapo(pedras, n);
    printf("Numero minimo de saltos: %d\n", resultado);

    return 0;
}
