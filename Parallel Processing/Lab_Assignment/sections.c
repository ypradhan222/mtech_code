#include<stdio.h>
#include <omp.h>
#define N     1000

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
  for (int i = 0; i < N; i++)
  {
   printf("%f\n",c[i]);/* code */
  }
  for (int i = 0; i < N; i++)
  {
   printf("%f",d[i]);/* code */
  }
  
return 0;
}
