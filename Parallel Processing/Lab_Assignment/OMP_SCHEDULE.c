#include <stdio.h>
#include <stdlib.h>  // Include the standard library header for setenv
#include<omp.h>
int main() {
    // Setting the OMP_SCHEDULE environment variable
    // Here, we set it to "static,2" which means static scheduling with a chunk size of 2.
    setenv("OMP_SCHEDULE", "static,2", 1);

    int i;
    int sum = 0;

    #pragma omp parallel for num_threads(4)
    for (i = 0; i < 100; i++) {
        #pragma omp atomic
        sum += i;
    }

    printf("Sum: %d\n", sum);

    return 0;
}
