#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Define the total number of elements and the data array
    int total_elements = 12;
    int* data = NULL;

    if (rank == 0) {
        // Only the root process initializes the data
        data = (int*)malloc(total_elements * sizeof(int));
        for (int i = 0; i < total_elements; i++) {
            data[i] = i + 1;  // Initialize data with values 1 to 12
        }
    }

    // Define the local array to store the received data portion
    int local_elements = total_elements / size;
    int* local_data = (int*)malloc(local_elements * sizeof(int));

    // Scatter the data from the root process to all processes
    MPI_Scatter(data, local_elements, MPI_INT, local_data, local_elements, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the local sum of the received data portion
    int local_sum = 0;
    for (int i = 0; i < local_elements; i++) {
        local_sum += local_data[i];
    }

    // Reduce the local sums to compute the global sum
    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global Sum: %d\n", global_sum);
    }

    // Clean up
    free(local_data);
    if (rank == 0) {
        free(data);
    }

    MPI_Finalize();

    return 0;
}
