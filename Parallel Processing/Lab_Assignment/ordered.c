#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
void printMatrix(int **array1,int size){
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
  printf("%4d",array1[i][j]);
}
printf("\n");
}
}
void printDiagonal(int **matrix,int size){
   for (int sum = 0; sum <= 2*(size-1);sum++){
      #pragma omp ordered
      for (int i = 0; i <= sum; i++)
      {
       int j = sum-i;
       if(i<size && j<size)
         printf("%4d",matrix[i][j]);  /* code */
      }
   }
}
int main(){
   int size;
   printf("enter the size ::");
   scanf("%d",&size);
   int **matrix = (int **)malloc(sizeof(int *) *size);
   for (int i = 0; i < size; i++)
   {
    matrix[i] = (int *)malloc(sizeof(int) *size);  /* code */
   }
   
   for (int i = 0; i < size; i++)
   {for (int j = 0; j < size; j++)
   {
    matrix[i][j] = i*size+j;  /* code */
   }   /* code */
   }
   printMatrix(matrix,size);
   printf("Diagonal are::\n");
   #pragma omp parallel
   {
      #pragma omp for ordered
      for (int i = 0; i < size; i++)
      {
       printf("Thread %d",omp_get_thread_num());
       printDiagonal(matrix,size);
       printf("\n");  /* code */
      }
      }
   for (int i = 0; i < size; i++)
   {
    free(matrix[i]);  /* code */
   }
   free(matrix);
   return 0;
}