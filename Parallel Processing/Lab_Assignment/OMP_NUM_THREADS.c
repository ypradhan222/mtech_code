#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    // Setting the OMP_NUM_THREADS environment variable using putenv
    char num_threads_str[] = "OMP_NUM_THREADS=3";
    putenv(num_threads_str);

    int i;
    int sum = 0;

    #pragma omp parallel for
    for (i = 0; i < 100; i++) {
        #pragma omp atomic
        sum += i;
    }

    printf("Sum: %d\n", sum);

    return 0;
}
