#include <stdio.h>
#include <stdlib.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int mediana(int a, int b, int c) {
    if (a < b) {
        if (b < c)
            return b;
        else if (a < c)
            return c;
        else
            return a;
    } else {
        if (a < c)
            return a;
        else if (b < c)
            return c;
        else
            return b;
    }
}

int medianaDasMedianas(int arr[], int left, int right) {
    int n = right - left + 1; // Tamanho do array
    int i;

    for (i = 0; i < n / 5; i++) {
        int inicio = left + i * 5;
        int fim = inicio + 4;
        if (fim > right)
            fim = right;
        
        int tamanhoGrupo = fim - inicio + 1;
        int j;

        for (j = 0; j < tamanhoGrupo - 1; j++) {
            for (int k = inicio; k < fim - j; k++) {
                if (arr[k] > arr[k + 1]) {
                    trocar(&arr[k], &arr[k + 1]);
                }
            }
        }

        trocar(&arr[left + i], &arr[inicio + tamanhoGrupo / 2]);
    }

    if (i * 5 < n) {
        int inicio = left + i * 5;
        int fim = inicio + (n % 5) - 1;
        int tamanhoGrupo = fim - inicio + 1;

        for (int j = 0; j < tamanhoGrupo - 1; j++) {
            for (int k = inicio; k < fim - j; k++) {
                if (arr[k] > arr[k + 1]) {
                    trocar(&arr[k], &arr[k + 1]);
                }
            }
        }

        trocar(&arr[left + i], &arr[inicio + tamanhoGrupo / 2]);
    }

    return left + (n / 10);
}

int particionar(int arr[], int left, int right) {
    int pivotIndex = medianaDasMedianas(arr, left, right);
    int pivotValue = arr[pivotIndex];

    trocar(&arr[pivotIndex], &arr[right]);

    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivotValue) {
            trocar(&arr[i], &arr[j]);
            i++;
        }
    }

    trocar(&arr[i], &arr[right]);
    return i;
}

int kthMenor(int arr[], int left, int right, int k) {
    if (k > 0 && k <= right - left + 1) {
        // Particiona o array em relação ao pivô
        int posicaoPivo = particionar(arr, left, right);

        if (posicaoPivo - left == k - 1) {
            return arr[posicaoPivo];
        } else if (posicaoPivo - left > k - 1) {
            return kthMenor(arr, left, posicaoPivo - 1, k);
        } else {
            return kthMenor(arr, posicaoPivo + 1, right, k - posicaoPivo + left - 1);
        }
    }
    return -1;
}

int main() {
    int arr[] = { 12, 3, 5, 7, 19 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3; 

    int resultado = kthMenor(arr, 0, n - 1, k);
    if (resultado != -1) {
        printf("O %d-esimo menor elemento: %d\n", k, resultado);
    } else {
        printf("Valor de k inválido.\n");
    }

    return 0;
}
