#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;
    int shared_counter = 0;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();

        #pragma omp critical
        {
            shared_counter += 1;

            // Flush memory to ensure visibility of updates
            #pragma omp flush(shared_counter)
        }

        printf("Thread %d incremented the counter. Current value: %d\n", thread_id, shared_counter);
    }

    printf("Final counter value: %d\n", shared_counter);

    return 0;
}
