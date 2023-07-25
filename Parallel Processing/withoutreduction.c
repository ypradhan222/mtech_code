#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    int sum = 0;
    int private_sum = 0;

    int array[ARRAY_SIZE];

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    #pragma omp parallel private(private_sum)
    {
        private_sum = 0;

        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            private_sum += array[i];
        }

        // Using critical to safely update the shared variable 'sum'
        #pragma omp critical
        {
            sum += private_sum;
        }
    }

    printf("The sum of the array is: %d\n", sum);

    return 0;
}
