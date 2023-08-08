#include <stdio.h>
#include <omp.h>

int main() {
    int n = 10;
    int factorial = 1;

    #pragma omp parallel for reduction(*:factorial)
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < omp_get_num_threads(); i++) {
            printf("Thread %d is performing additional work.\n", omp_get_thread_num());
        }

        #pragma omp single
        {
            printf("The factorial of %d is: %d\n", n, factorial);
        }
    }

    return 0;
}
