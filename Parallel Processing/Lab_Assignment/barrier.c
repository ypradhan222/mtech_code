#include <stdio.h>
#define NUM_THREADS 4
#include <omp.h>
#include<time.h>
int main() {
    double area, pi, x;
    int i, n;
    double time1 = omp_get_wtime();
    area = 0.0;
    printf("enter the value of n:");
    scanf("%d", &n);
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for private(x) reduction(+ : area) schedule(static, 100) if(n > 5000)
    for (i = 0; i < n; i++) {
        int num = omp_get_thread_num();
        x = (i + 0.5) / n;

        area += 4.0 / (1.0 + x * x);

        printf("area of thread(%d):: %f\n", num, area);
    }

    #pragma omp barrier // Synchronize all threads before continuing

    pi = area / n;
    double time2 = omp_get_wtime();
    printf("The value :: %f\n", pi);
    printf("Execution time: %f\n",time2 - time1);
}

