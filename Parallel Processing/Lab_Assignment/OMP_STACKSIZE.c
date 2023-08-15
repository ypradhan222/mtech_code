#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    // Set the stack size for OpenMP threads (in kilobytes)
    putenv("OMP_STACKSIZE=512k");

    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Hello from the parallel region\n", thread_id);
    }

    return 0;
}
