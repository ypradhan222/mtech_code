#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAX_FILENAME_LENGTH 256

int main(int argc, char *argv[]) {
    int rank, size;
    char filename[MAX_FILENAME_LENGTH];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Node 0 collects the image file name from the user
        printf("Enter the image file name: ");
        fflush(stdout);
        fgets(filename, MAX_FILENAME_LENGTH, stdin);
        strtok(filename, "\n"); // Remove the trailing newline character
    }

    // Broadcast the image filename from node 0 to all other nodes
    MPI_Bcast(filename, MAX_FILENAME_LENGTH, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Now, all nodes can access the image filename
    printf("Rank %d: Image file name is: %s\n", rank, filename);

    MPI_Finalize();
    return 0;
}
