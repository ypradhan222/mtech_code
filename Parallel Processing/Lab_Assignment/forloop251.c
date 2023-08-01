#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
int main(){
   int size;
   printf("Enter the size of array::");
   scanf("%d",&size);
   if (size>=0) {
   int *array1 = (int *)malloc(sizeof(int) *size);
   int *array2 = (int *)malloc(sizeof(int) *size);
   int *array3 = (int *)malloc(sizeof(int) *size);

   for (int i = 0; i < size; i++)
   {
     array1[i] = rand()%100+1;  /* code */
   }
   for (int i = 0; i < size; i++)
   {
    array2[i] = rand()%100+1;  /* code */
   }
   omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
     array3[i]  = array1[i]+array2[i];/* code */
    }
   //PRinting the resultant array
   for (int i = 0; i < size; i++)
   {
    printf("%d",array3[i]);  /* code */
   }
   
   }
   else{
      printf("ERROR Size cannot be negative.");
   }
   
   return 0;

}