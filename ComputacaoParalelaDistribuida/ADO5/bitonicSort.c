#include <omp.h>
#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bitonicSort(int* a, int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            if (dir == (a[i] > a[i + k])) {
                swap(&a[i], &a[i + k]);
            }
        }
        #pragma omp parallel sections
        {
            #pragma omp section
            bitonicSort(a, low, k, dir);
            #pragma omp section
            bitonicSort(a, low + k, k, dir);
        }
    }
}

void bitonicMerge(int* a, int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        bitonicSort(a, low, k, dir);
        bitonicSort(a, low + k, k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

void sort(int* a, int N, int up) {
    bitonicSort(a, 0, N, up);
    bitonicMerge(a, 0, N, up);
}

int main() {
    int a[] = {3, 7, 4, 8, 6, 2, 1, 5};
    int N = sizeof(a) / sizeof(a[0]);

    int up = 1; // sorting in ascending order

    printf("Array Original: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    
    sort(a, N, up);

    printf("\nArray Ordenado: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}