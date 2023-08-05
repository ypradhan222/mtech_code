#define SIZE 4
#include<stdio.h>
#include<omp.h>
int main(){
   int condition = 0;
   printf("------------FOR FALSE CONDITION---------\n");
   #pragma omp parallel if(condition)
   {  
      for(int i =0;i<SIZE;i++){
         int id = omp_get_thread_num();
         printf("Hello(%d)",i);
         printf("World!! from thread %d\n",id);
      }
   }
   condition = 1;
   printf("\n");
   printf("------------FOR TRUE CONDITION---------\n");
   #pragma omp parallel if(condition) num_threads(4)
   {  
      for(int i =0;i<SIZE;i++){
         int id = omp_get_thread_num();
         printf("Hello(%d)",i);
         printf("World!! from thread %d\n",id);
      }
   }
   return 0;
}