#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;
    int n = 10;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        
        #pragma omp for ordered
        for (int i = 0; i < n; i++) {
            #pragma omp ordered
            printf("Thread %d is processing iteration %d.\n", thread_id, i);
        }
    }

    return 0;
}
#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        
        #pragma omp for ordered
        {
            printf("Thread %d is entering the ordered block.\n", thread_id);
            // Some work that should be executed in order
            printf("Thread %d is exiting the ordered block.\n", thread_id);
        }
        
        // Other work that is not ordered
        printf("Thread %d is performing other work.\n", thread_id);
    }

    return 0;
}
