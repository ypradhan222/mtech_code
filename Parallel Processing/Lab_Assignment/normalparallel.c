#define SIZE 10000
#include<stdio.h>
#include<omp.h>
int main(){
   #pragma omp parallel
   {
      for(int i =0;i<SIZE;i++){
         int id = omp_get_thread_num();
         printf("Hello(%d)",i);
         printf("World!! from thread %d\n",id);
      }
   }
}