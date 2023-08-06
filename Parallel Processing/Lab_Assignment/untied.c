#include <stdio.h>
#include <omp.h>
#include<time.h>
int main() {
    int num_tasks = 10;
   double time1 = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < num_tasks; ++i) {
                #pragma omp task  untied final(i < 5)
                {
                    int thread_num = omp_get_thread_num();
                    printf("Task %d executed by thread %d\n", i, thread_num);
                }
            }
        }
    }
   double time2 = omp_get_wtime();
   printf("Execution :: %f\n",time2-time1);
    return 0;
}
