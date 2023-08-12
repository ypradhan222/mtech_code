#include <stdio.h>
#include <omp.h>
int thread_private_var;
int main() {
    int shared_var = 10; 
    thread_private_var = shared_var;
    #pragma omp parallel  private(shared_var)
    {
        int thread_id = omp_get_thread_num();
        thread_private_var += thread_id;
        printf("Thread %d: shared_var = %d, thread_private_var = %d\n", thread_id, shared_var, thread_private_var);
        #pragma omp single copyprivate(shared_var)
        {
            shared_var = thread_private_var;
        }
    }
    printf("After parallel region: shared_var = %d\n", shared_var);

    return 0;
}

