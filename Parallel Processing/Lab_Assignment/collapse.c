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
   #pragma omp parallel
   {
      #pragma omp for collapse(2)
      for (int i = 0; i < size; i++)
      {for (int j = 0; j < size; j++)
      {
       matrix[i][j] *=2;  /* code */
      }    /* code */
      }
      
   }
   printf("After multiplication:\n");
   printMatrix(matrix,size);
   for (int i = 0; i < size; i++)
   {
    free(matrix[i]);  /* code */
   }
   free(matrix);
   return 0;
}