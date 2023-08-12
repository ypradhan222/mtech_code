#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

int main() {
    omp_lock_t my_lock;
    omp_nest_lock_t my_nest_lock;

    // Initialize the locks
    omp_init_lock(&my_lock);
    omp_init_nest_lock(&my_nest_lock);

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread_num = omp_get_thread_num();

        if (omp_test_lock(&my_lock) == 1) {
            printf("Thread %d acquired test lock.\n", thread_num);
            printf("Thread %d is in the critical section.\n", thread_num);
            omp_unset_lock(&my_lock);
        } else {
            printf("Thread %d could not acquire test lock.\n", thread_num);
        }

        if (omp_test_nest_lock(&my_nest_lock) == 1) {
            printf("Thread %d acquired test nest lock.\n", thread_num);
            printf("Thread %d is in the nested critical section.\n", thread_num);
            omp_unset_nest_lock(&my_nest_lock);
        } else {
            printf("Thread %d could not acquire test nest lock.\n", thread_num);
        }
    }
    omp_destroy_lock(&my_lock);
    omp_destroy_nest_lock(&my_nest_lock);

    return 0;
}