#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void addElements(int **array, int size, int my_rank) {
    srand(time(NULL) + my_rank);  // Use a different seed for each process
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            array[i][j] = rand() % 100 + 1;
        }
    }
}

void printMatrix(int **array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%8d", array[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 2) {
        fprintf(stderr, "This program needs at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    int matrix_size ;
    if (rank == 0) {
        printf("Enter the size of the matrices: ");
        scanf("%d", &matrix_size);
    }

    // Broadcast matrix size to all processes
    MPI_Bcast(&matrix_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int **array1 = (int **)malloc(sizeof(int *) * matrix_size);
    int **array2 = (int **)malloc(sizeof(int *) * matrix_size);
    int **result = (int **)malloc(sizeof(int *) * matrix_size);

    for (int i = 0; i < matrix_size; i++) {
        array1[i] = (int *)malloc(sizeof(int) * matrix_size);
        array2[i] = (int *)malloc(sizeof(int) * matrix_size);
        result[i] = (int *)malloc(sizeof(int) * matrix_size);
    }

    // Distribute matrix data
    addElements(array1, matrix_size, rank);
    addElements(array2, matrix_size, rank);

    // Perform local matrix multiplication
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < matrix_size; k++) {
                result[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }

    // Gather results on the master process
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&result[0][0], matrix_size * matrix_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } else {
        MPI_Send(&result[0][0], matrix_size * matrix_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printf("Matrix 1:\n");
        printMatrix(array1, matrix_size);

        printf("\nMatrix 2:\n");
        printMatrix(array2, matrix_size);

        printf("\nResultant matrix:\n");
        printMatrix(result, matrix_size);
    }

    // Cleanup
    for (int i = 0; i < matrix_size; i++) {
        free(array1[i]);
        free(array2[i]);
        free(result[i]);
    }
    free(array1);
    free(array2);
    free(result);

    MPI_Finalize();
    return 0;
}
