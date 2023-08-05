#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
void printArray(int *array,int size){
   for (int i = 0; i < size; i++)
   {
    printf("%4d",array[i]);  /* code */
   }
}
int main(){
   int size,i;
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
   printf("Array1::\n");
   printArray(array1,size);
   printf("\n");
   for (int i = 0; i < size; i++)
   {
    array2[i] = rand()%100+1;  /* code */
   }
   printf("Array2 ::\n");
   printArray(array2,size);
   printf("\n");
   // omp_set_num_threads(4);
    #pragma omp for  ordered nowait
    for (i = 0; i < size; i++)
    {
     array3[i]  = array1[i]+array2[i];/* code */
    }
   //PRinting the resultant array
   printf("Result::\n");
   printArray(array3,size);
   printf("\n");
   }
   else{
      printf("ERROR Size cannot be negative.");
   }
   
   return 0;

}