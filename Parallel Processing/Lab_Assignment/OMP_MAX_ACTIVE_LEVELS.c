#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    // Set the maximum number of active nested levels
    putenv("OMP_MAX_ACTIVE_LEVELS=2");

    // Outer parallel region
    #pragma omp parallel num_threads(4)
    {
        int outer_thread_id = omp_get_thread_num();
        printf("Outer Thread %d: Hello from outer parallel region\n", outer_thread_id);

        // Nested parallel region
        #pragma omp parallel num_threads(2)
        {
            int inner_thread_id = omp_get_thread_num();
            printf("Outer Thread %d, Inner Thread %d: Hello from inner parallel region\n", outer_thread_id, inner_thread_id);
        }
    }

    return 0;
}
