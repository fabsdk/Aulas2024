#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_size = 4;
    int local_vector[local_size];
    int global_vector[local_size * size];

    for (int i = 0; i < local_size; i++) {
        local_vector[i] = rank * local_size + i;
    }

    int prefix_sum = 0;
    for (int i = 0; i < local_size; i++) {
        prefix_sum += local_vector[i];
        global_vector[rank * local_size + i] = prefix_sum;
    }
    int *recv_buf = (int *)malloc(local_size * sizeof(int));
    MPI_Allgather(local_vector, local_size, MPI_INT, recv_buf, local_size, MPI_INT, MPI_COMM_WORLD);

    printf("Processo %d: Vetor local = [", rank);
    for (int i = 0; i < local_size; i++) {
        printf("%d ", local_vector[i]);
    }
    printf("] -> Soma de Prefixos Local = %d\n", prefix_sum);

    if (rank == 0) {
        printf("Vetor Global (Soma de Prefixos): [");
        for (int i = 0; i < local_size * size; i++) {
            printf("%d ", global_vector[i]);
        }
        printf("]\n");
    }

    MPI_Finalize();
    return 0;
}
