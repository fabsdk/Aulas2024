#include <stdio.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int arr[], int inicio, int fim) {
    int pivo = arr[fim];
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++) {
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[fim]);
    return i + 1;
}

int kthSmallest(int arr[], int inicio, int fim, int k) {
    if (k > 0 && k <= fim - inicio + 1) {
        int indice_pivo = particionar(arr, inicio, fim);

        if (indice_pivo - inicio == k - 1)
            return arr[indice_pivo];
        if (indice_pivo - inicio > k - 1)
            return kthSmallest(arr, inicio, indice_pivo - 1, k);
        return kthSmallest(arr, indice_pivo + 1, fim, k - indice_pivo + inicio - 1);
    }
    return -1;
}

int main() {
    int arr[] = {12, 3, 5, 7, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int resultado = kthSmallest(arr, 0, n - 1, k);
    if (resultado != -1)
        printf("O %d-esimo menor elemento: %d\n", k, resultado);
    else
        printf("O valor de k é invalido para este array.\n");

    return 0;
}
