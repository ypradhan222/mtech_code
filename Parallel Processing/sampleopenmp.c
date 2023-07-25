#include<stdio.h>
#include<time.h>
#include"omp.h"
int main()
{
//{  
    double time=0;
    clock_t t1 = clock();
   #pragma omp parallel 
   {
   for(int i=0;i<10;i++)
   {
    int id= omp_get_thread_num();
    printf("Hello(%d)",id);
    printf("World(%d)\n",id);
    printf("Thread Number : %d\n",id);
  //  }
  clock_t t2 = clock();
  time = (double)(t2-t1)/CLOCKS_PER_SEC;
}
  printf("Time Taken : %f\n",time);
   }   
return 0;
   
}
