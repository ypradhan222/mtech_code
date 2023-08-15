
#include <stdio.h>
#include <stdlib.h> // Include the header for setenv
#include <omp.h>

int main() {
    // Set OMP_NESTED to true to enable nested parallelism
    omp_set_nested(1);
    
    setenv("OMP_NESTED", "true", 1);
    #pragma omp parallel num_threads(2)
    {
        int outer_thread_id = omp_get_thread_num();
        printf("Outer Thread %d: Hello from outer parallel region\n", outer_thread_id);
        #pragma omp parallel num_threads(2)
        {
            int inner_thread_id = omp_get_thread_num();
            printf("Outer Thread %d, Inner Thread %d: Hello from inner parallel region\n", outer_thread_id, inner_thread_id);
        }
    }

    return 0;
}