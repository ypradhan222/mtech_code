#include<stdio.h>
#include<omp.h>
int main(){
   double area,pi ,x;
   int i,n;
   area = 0.0;
   printf("Enter the value of n::");
   scanf("%d",&n);
   #pragma omp single
   for(i =0 ;i<n;i++){
      x = (i+0.5)/n;
      area += 4.0/(1.0+x*x);
      // printf("area ::%f\n",area);
   }
   pi = area/n;
   printf("Value :: %f\n",pi);
   return 0;
}