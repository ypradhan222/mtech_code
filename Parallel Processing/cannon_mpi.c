#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4 // Matrix dimension (Assuming N is a multiple of the grid size)

void printMatrix(int *matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%8d", matrix[i * size + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int grid_size = 2; // Size of the 2D process grid (2x2 in this example)

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != grid_size * grid_size) {
        if (rank == 0) {
            printf("This program requires %d processes in a %dx%d grid.\n", grid_size * grid_size, grid_size, grid_size);
        }
        MPI_Finalize();
        return 1;
    }

    int local_size = N / grid_size; // Size of local blocks
    int *local_A = (int *)malloc(local_size * local_size * sizeof(int));
    int *local_B = (int *)malloc(local_size * local_size * sizeof(int));
    int *local_C = (int *)calloc(local_size * local_size, sizeof(int)); // Initialize local_C with zeros

    // Scatter matrix A and matrix B among the processes
    MPI_Scatter(local_A, local_size * local_size, MPI_INT, local_A, local_size * local_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(local_B, local_size * local_size, MPI_INT, local_B, local_size * local_size, MPI_INT, 0, MPI_COMM_WORLD);

    int shift = 0;
    for (int stage = 0; stage < grid_size; stage++) {
        // Shift matrices to the left
        int left_rank = (rank / grid_size) * grid_size + (rank + grid_size - 1) % grid_size;
        int right_rank = (rank / grid_size) * grid_size + (rank + 1) % grid_size;

        MPI_Sendrecv_replace(local_A, local_size * local_size, MPI_INT, left_rank, 0, right_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Perform local matrix multiplication
        for (int i = 0; i < local_size; i++) {
            for (int j = 0; j < local_size; j++) {
                for (int k = 0; k < local_size; k++) {
                    local_C[i * local_size + j] += local_A[i * local_size + k] * local_B[k * local_size + j];
                }
            }
        }

        // Shift matrices upwards
        int up_rank = (rank + grid_size - grid_size) % size;
        int down_rank = (rank + grid_size) % size;

        MPI_Sendrecv_replace(local_B, local_size * local_size, MPI_INT, up_rank, 0, down_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Gather the results to process 0
    MPI_Gather(local_C, local_size * local_size, MPI_INT, local_C, local_size * local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // On process 0, print the result
    if (rank == 0) {
        printf("Matrix A:\n");
        printMatrix(local_A, local_size);

        printf("\nMatrix B:\n");
        printMatrix(local_B, local_size);

        printf("\nResultant Matrix C:\n");
        printMatrix(local_C, local_size);
    }

    free(local_A);
    free(local_B);
    free(local_C);

    MPI_Finalize();
    return 0;
}
