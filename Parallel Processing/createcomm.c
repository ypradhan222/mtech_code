#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int dims[2];    // Dimensions of the 2D grid
    int periods[2]; // Grid is not periodic
    int coords[2];  // Coordinates of the current process in the grid

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        printf("This example is designed for 4 processes. Please use 4 processes.\n");
        MPI_Finalize();
        return 1;
    }

    // Determine the dimensions of the 2D grid
    MPI_Dims_create(size, 2, dims);

    // Create a Cartesian communicator
    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart_comm);

    if (cart_comm != MPI_COMM_NULL) {
        // Get the coordinates of the current process in the grid
        MPI_Cart_coords(cart_comm, rank, 2, coords);

        printf("Process %d is at coordinates (%d, %d) in the 2D grid.\n", rank, coords[0], coords[1]);

        MPI_Comm_free(&cart_comm);
    } else {
        printf("Process %d is not part of the 2D grid.\n", rank);
    }

    MPI_Finalize();
    return 0;
}
