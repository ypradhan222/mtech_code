#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 10

int main() {
    int i;
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int squares[ARRAY_SIZE];

    #pragma omp parallel private(i) // private clause ensures each thread has its own 'i'
    {
        #pragma omp sections
        {
            #pragma omp section
            for (i = 0; i < ARRAY_SIZE / 2; i++) {
                squares[i] = arr[i] * arr[i];
            }

            #pragma omp section
            for (i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++) {
                squares[i] = arr[i] * arr[i];
            }
        }
    }

    printf("Original Array: ");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Squared Array: ");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");

    return 0;
}
