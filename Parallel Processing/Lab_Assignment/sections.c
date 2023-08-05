#include<stdio.h>
#include <omp.h>
#define N 1000

int main ()
{

int i;
float a[N], b[N], c[N], d[N];

for (i=0; i < N; i++) {
  a[i] = i * 1.5;
  b[i] = i + 22.35;
  }

#pragma omp parallel 
  {

  #pragma omp sections 
    {

    #pragma omp section
    for (i=0; i < N; i++)
      c[i] = a[i] + b[i];

    #pragma omp section
    for (i=0; i < N; i++)
      d[i] = a[i] * b[i];

    }  

  }  
  float sum =0.0;
  float  product =0.0;
  #pragma omp parallel for reduction(+ : sum) reduction(* :product)
  for (int i = 0; i < N; i++)
  {
   sum += c[i];
   product *= d[i]; /* code */
  }
  printf("Sum of c::%f\n",sum);
  printf("Product of d: %f\n",product);
  
return 0;
}
