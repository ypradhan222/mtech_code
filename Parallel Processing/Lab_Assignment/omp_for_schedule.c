#include <stdio.h>
#include <omp.h>

int main() {
    int num_iterations = 20;
    int result[num_iterations];

    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic, 4)
        for (int i = 0; i < num_iterations; i++) {
            int thread_num = omp_get_thread_num();
            result[i] = thread_num;
            printf("Thread %d executing iteration %d\n", thread_num, i);
        }
    }

    printf("Result array:\n");
    for (int i = 0; i < num_iterations; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
