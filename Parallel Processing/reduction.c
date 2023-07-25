#include<stdio.h>
#include<omp.h>
#include<time.h>
double func(int n){
    return n;
}
void main(){
    int i;
    double zz,func(),res =0.0;
    int num = omp_get_num_procs();
    omp_set_num_threads(2);
    //__clock_t time1 = clock();
    double time1 = omp_get_wtime();
    #pragma omp parallel for reduction(+ : res) private(zz)
    for ( i = 0; i < 1000; i++)
    {
      zz= func(i);
      res = res+zz;   /* code */
    }
   // __clock_t time2 = clock();
    double time2 = omp_get_wtime();
    //double execution_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("number: %d\n",num);
    printf("\n");
    printf("TIme for execution:: %f\n",time2 - time1);
    printf("Sum:%f\n",res);
}