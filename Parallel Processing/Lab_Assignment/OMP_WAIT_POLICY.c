#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    // Set the wait policy for OpenMP threads
    putenv("OMP_WAIT_POLICY=ACTIVE");

    // Parallel region with two threads
    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Starting parallel region\n", thread_id);

        // Synchronization point (barrier)
        #pragma omp barrier

        printf("Thread %d: Reached the barrier\n", thread_id);
    }

    return 0;
}
