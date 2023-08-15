#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
int main() {
    // Set OMP_PROC_BIND to TRUE to enable binding threads to cores
    setenv("OMP_PROC_BIND", "TRUE", 1);

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
