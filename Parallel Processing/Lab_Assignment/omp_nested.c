#include <stdio.h>
#include <omp.h>

int main() {
    int outer_threads = 2;
    int inner_threads = 4;

    omp_set_nested(1); // Enable nested parallelism

    #pragma omp parallel num_threads(outer_threads)
    {
        int outer_thread_num = omp_get_thread_num();
        printf("Outer thread %d executing\n", outer_thread_num);

        #pragma omp parallel num_threads(inner_threads)
        {
            int inner_thread_num = omp_get_thread_num();
            printf("Inner thread %d (outer %d) executing\n", inner_thread_num, outer_thread_num);
        }
    }

    return 0;
}
