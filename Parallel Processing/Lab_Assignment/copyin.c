#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 10; 
    #pragma omp parallel shared(shared_var)
    {
        int thread_private_var; 
        #pragma omp  copyin(shared_var)
        thread_private_var = shared_var;
        int thread_id = omp_get_thread_num();
        thread_private_var += thread_id;
        printf("Thread %d: shared_var = %d, thread_private_var = %d\n", thread_id, shared_var, thread_private_var);
    }
    return 0;
}
