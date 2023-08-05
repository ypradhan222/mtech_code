#include<stdio.h>
#include<omp.h>
int main(){
   int a = 0;

   #pragma omp parallel default(shared) //using default(shared)
   {
      int id = omp_get_thread_num();
      a +=id;
      printf("Thread: %d - Shared Variable- %d\n",id,a);
   }
   //using default(none)
   #pragma omp parallel default(none) private(a)
   {
      int id = omp_get_thread_num();
      a = id;
      printf("Thread: %d - Variable- %d\n",id,a);  
   }
   return 0;
}