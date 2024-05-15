#include <stdio.h>

long long int mergeCount(int arr[], int temp[], int esq, int meio, int dir) {
    int i, j, k;
    long long int invCount = 0;

    i = esq;
    j = meio;
    k = esq;

    while ((i <= meio - 1) && (j <= dir)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (meio - i);
        }
    }
    while (i <= meio - 1) {
        temp[k++] = arr[i++];
    }
    while (j <= dir) {
        temp[k++] = arr[j++];
    }
    for (i = esq; i <= dir; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

long long int mergeSortCount(int arr[], int temp[], int esq, int dir) {
    long long int invCount = 0;
    int meio;

    if (dir > esq) {
        meio = (esq + dir) / 2;

        invCount += mergeSortCount(arr, temp, esq, meio);

        invCount += mergeSortCount(arr, temp, meio + 1, dir);

        invCount += mergeCount(arr, temp, esq, meio + 1, dir);
    }

    return invCount;
}

int main() {
    int arr[] = {1, 20, 6, 4, 5};
    int tamanho = sizeof(arr) / sizeof(arr[0]);
    int temp[tamanho];
    long long int invCount;

    invCount = mergeSortCount(arr, temp, 0, tamanho - 1);

    printf("Número de inversões: %lld\n", invCount);

    return 0;
}
