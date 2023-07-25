#include <stdio.h>
#include <omp.h>
#include<time.h>
#include <stdlib.h>
#include<unistd.h>
#define MAX_ROWS 100
#define MAX_COLUMNS 100

void addMatrix(int arr[][MAX_COLUMNS], int arr2[][MAX_COLUMNS], int result[][MAX_COLUMNS], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result[i][j] = arr[i][j] + arr2[i][j];
        }
    }
}

int main() {
    int rows, columns;
    printf("Enter the number of rows of the matrix: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &columns);

    // Limiting the array size to a maximum of 100 for rows and columns
    if (rows > MAX_ROWS || columns > MAX_COLUMNS) {
        printf("Rows and columns should be less than or equal to %d.\n", MAX_ROWS);
        return 1;
    }

    int array1[MAX_ROWS][MAX_COLUMNS];
    int array2[MAX_ROWS][MAX_COLUMNS];
    int result[MAX_ROWS][MAX_COLUMNS];
    srand(time(NULL));
    usleep(100000);
    // Entering elements in each matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            array1[i][j] = rand() % 100 + 1;
            array2[i][j] = rand() % 100 + 1;
        }
    }


    addMatrix(array1, array2, result, rows, columns);

    printf("Matrix 1:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%4d ", array1[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix 2:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%4d ", array2[i][j]);
        }
        printf("\n");
    }

    printf("\nResultant Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%4d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

