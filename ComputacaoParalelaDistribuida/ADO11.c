#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 5;
    int *vec = (int *)malloc(n * sizeof(int));
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        vec[i] = i + 1;
    }

    int left = (rank == 0) ? size - 1 : rank - 1;
    int right = (rank + 1) % size;

    int local_sum = 0;
    for (int i = 0; i < n; i++) {
        local_sum += vec[i];
    }

    int recv_sum;
    if (rank == 0) {
        MPI_Send(&local_sum, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_sum, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Recv(&recv_sum, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&local_sum, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    }

    sum = local_sum + recv_sum;
    printf("vetor original:");
    for (int i = 0; i < n; i++) {
        printf(" %d", vec[i]);
    }
    printf("\n");

    if (rank == 0) {
        printf("A soma dos elementos do vetor no anel é: %d\n", sum);
    }

    MPI_Finalize();
    free(vec);
    return 0;
}
