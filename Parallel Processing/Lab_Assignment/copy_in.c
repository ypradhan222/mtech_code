#include<stdio.h>
#include<omp.h>
int var;
int main(){
   #pragma omp threadprivate(var)
   var = 15;
   #pragma omp parallel copyin(var)
   {
      int id = omp_get_thread_num();
      var+=id;
      printf("Thread:%d \n Shared -%d\n",id,var);
   }
   printf("After parallel - Shared:%d\n",var);
   return 0;
}