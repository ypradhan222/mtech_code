#include <stdio.h>
#include <stdlib.h>  // Include the standard library header for setenv

int main() {
    // Setting the OMP_DYNAMIC environment variable
    // Here, we set it to "1" to enable dynamic thread adjustment.
    setenv("OMP_DYNAMIC", "1", 1);

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
