#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    // Set the maximum thread limit
    putenv("OMP_THREAD_LIMIT=4");

    // Parallel region with more threads than the limit
    #pragma omp parallel num_threads(6)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Hello from the parallel region\n", thread_id);
    }

    return 0;
}
