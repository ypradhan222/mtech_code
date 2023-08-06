#include<stdio.h>
#include<omp.h>
#include<time.h>

double func(int n){
    return n;
}

int main(){
    int i;
    double zz, res = 0.0;
    int num = omp_get_num_procs();
    omp_set_num_threads(2);
    
    double start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+ : res) private(zz)
    for (i = 0; i < 1000; i++) {
        zz = func(i);
        res = res + zz;
    }
    double end_time = omp_get_wtime();

    double tick = omp_get_wtick();
    
    printf("Number of processors: %d\n", num);
    printf("\n");
    printf("Time for execution: %f seconds\n", end_time - start_time);
    printf("Clock tick interval: %e seconds\n", tick);
    printf("Sum: %f\n", res);
    
    return 0;
}
