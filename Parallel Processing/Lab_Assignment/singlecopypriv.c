#include <stdio.h>
#include <omp.h>

int main() {
    int n = 100;
    int array[n];
    int sum = 0;

    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    #pragma omp parallel for reduction(+:sum) // Calculate sum in parallel
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }

    int thread_id, num_threads, private_sum;

    #pragma omp parallel private(thread_id, private_sum) // Start of parallel region
    {
        thread_id = omp_get_thread_num();
        private_sum = 0;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            private_sum += array[i];
        }

        #pragma omp critical
        sum += private_sum;

        #pragma omp single // Only one thread executes the block
        {
            printf("Thread %d calculated the total sum: %d\n", thread_id, sum);
        }
    } // End of parallel region

    return 0;
}
