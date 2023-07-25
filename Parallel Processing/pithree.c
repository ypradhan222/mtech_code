#include<stdio.h>
#define NUM_THREADS 4
#include<omp.h>
int main(){
    double area,pi,x;
    int i,n;
    area =0.0;
    printf("enter the value of n:");
    scanf("%d",&n);
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for private(x) reduction(+ : area)  schedule(static,100) if(n>5000)
    for ( i = 0; i < n; i++)
    {
        int num = omp_get_thread_num();
        x =(i+0.5)/n;
    // #pragma omp critical
        area+=4.0/(1.0+x*x); 
        printf("area of thread(%d):: %f\n",num,area);  /* code */
    }
    #pragma omp critical
    pi = area/n;
    printf("The value :: %f\n",pi);
    
}