#include <stdio.h>
#include <mpi.h>

void split_sort(int* data, int start, int end) {
    if (end - start < 2) {
        return;
    }

    int mid = (start + end) / 2;
    split_sort(data, start, mid);
    split_sort(data, mid, end);

    int temp[end - start];
    int i = start;
    int j = mid;
    int k = 0;

    while (i < mid && j < end) {
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

    while (i < mid) {
        temp[k++] = data[i++];
    }

    while (j < end) {
        temp[k++] = data[j++];
    }

    for (i = start; i < end; i++) {
        data[i] = temp[i - start];
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[] = {5, 3, 8, 6, 2, 7, 1, 4};
    int n = sizeof(data) / sizeof(data[0]);

    printf("Array Original: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    split_sort(data, 0, n);

    if (rank == 0) {
        printf("Array Ordenado: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
