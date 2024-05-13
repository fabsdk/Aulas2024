#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define VECTOR_SIZE 6

int main(int argc, char *argv[]) {
    int rank, size;
    int local_vector[VECTOR_SIZE];
    int global_vector[VECTOR_SIZE] = {1, 2, 3, 4, 5, 6};
    int sum_vector[VECTOR_SIZE] = {0};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc = VECTOR_SIZE / size;
    MPI_Scatter(global_vector, elements_per_proc, MPI_INT, local_vector, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    for (int i = 0; i < elements_per_proc; i++) {
        local_sum += local_vector[i];
    }

    MPI_Gather(&local_sum, 1, MPI_INT, sum_vector, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Vetor global:\n");
        for (int i = 0; i < VECTOR_SIZE; i++) {
            printf("%d ", global_vector[i]);
        }
        printf("\nSoma do vetor global: ");
        int total_sum = 0;
        for (int i = 0; i < size; i++) {
            total_sum += sum_vector[i];
        }
        printf("%d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}
