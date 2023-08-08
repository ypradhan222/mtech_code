#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 10

int main() {
    int i, sum = 0;
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    #pragma omp parallel firstprivate(i) 
    {
        #pragma omp sections
        {
            #pragma omp section
            for (i = 0; i < ARRAY_SIZE / 2; i++) {
                sum += arr[i];
            }

            #pragma omp section
            for (i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++) {
                sum += arr[i];
            }
        }
    }

    printf("Original Array: ");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Sum of Array Elements: %d\n", sum);

    return 0;
}
