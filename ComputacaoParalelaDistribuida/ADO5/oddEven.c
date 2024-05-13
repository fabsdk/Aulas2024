#include <stdio.h>
#include <omp.h>

void oddEvenSort(int arr[], int n) {
    int phase, i, temp;

    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
            #pragma omp parallel for default(none) shared(arr, n) private(i, temp)
            for (i = 1; i < n; i += 2) {
                if (arr[i - 1] > arr[i]) {
                    temp = arr[i - 1];
                    arr[i - 1] = arr[i];
                    arr[i] = temp;
                }
            }
        } else {
            #pragma omp parallel for default(none) shared(arr, n) private(i, temp)
            for (i = 1; i < n - 1; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int arr[] = {5, 3, 8, 6, 2, 7, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array antes da ordenação:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    oddEvenSort(arr, n);
    
    printf("Array depois da ordenação:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
