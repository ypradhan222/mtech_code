#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_data = 42; // Local data on each process
    int global_sum = 0;  // Global sum to be computed

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Reduce local_data to the global_sum on rank 0
    if (rank == 0) {
        global_sum = local_data;
        for (int i = 1; i < size; i++) {
            int received_value;
            MPI_Recv(&received_value, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            global_sum += received_value;
        }
    } else {
        MPI_Send(&local_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Print the result on rank 0
    if (rank == 0) {
        printf("Global Sum: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
