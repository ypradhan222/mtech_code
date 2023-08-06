#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main() {
    omp_nest_lock_t my_nest_lock;

    // Initialize the nested lock
    omp_init_nest_lock(&my_nest_lock);

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread_num = omp_get_thread_num();
        int sum = 0;
        // Acquire the nested lock
        omp_set_nest_lock(&my_nest_lock);

        printf("Thread %d entered critical section.\n", thread_num);
        // Simulate some work
        for (int i = 0; i < 1000000; i++) {
         sum+=i;           
        }
        printf("Thread %d exited critical section.\n", thread_num);
         printf("%d\n",sum);
        // Release the nested lock
        omp_unset_nest_lock(&my_nest_lock);
    }

    // Destroy the nested lock
    omp_destroy_nest_lock(&my_nest_lock);

    return 0;
}
