#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ROOT 0

int main(int argc, char *argv[]) {
    int rank, size;
    int data = 42;  // Data to be broadcast

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == ROOT) {
        // If this is the root process, send the data to all other processes
        for (int dest = 0; dest < size; dest++) {
            if (dest != ROOT) {
                MPI_Send(&data, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        // If this is not the root process, receive the data from the root
        MPI_Recv(&data, 1, MPI_INT, ROOT, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // All processes now have the broadcasted data
    printf("Process %d received data: %d\n", rank, data);

    MPI_Finalize();
    return 0;
}
