#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void addElements(int **array1,int size){
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
  array1[i][j] = rand()%100+1;
}
}
}

void printMatrix(int **array1,int size){
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
  printf("%8d",array1[i][j]);
}
printf("\n");
}
}
int main(){
int size;
printf("Enter the size::");
scanf("%d",&size);
srand(time(NULL));
int **array1 = (int **)malloc(sizeof(int *) *size);
for (int i = 0; i < size; i++)
{
 array1[i] = (int *)malloc(sizeof(int) *size); /* code */
}

int **array2 = (int **)malloc(sizeof(int*) *size);
for (int i = 0; i < size; i++)
{
 array2[i] = (int *)malloc(sizeof(int) *size); /* code */
}

int **result = (int **)malloc(sizeof(int*) *size);
for (int i = 0; i < size; i++)
{
 result[i] = (int *)malloc(sizeof(int) *size); /* code */
}
//adding elements to the arrays
  addElements(array1,size);
  addElements(array2,size);
  printf("Array 1 :: \n");
  printMatrix(array1,size);
  printf("\n");
  printf("Array 2 :: \n");
  printMatrix(array2,size);
//Multiplying the matrices
clock_t start,end;
double total;
int i,j,k;
start = clock();
for (i = 0; i < size; i++)
{
 for (k = 0; k < size; k++)
 {
  result[i][j]=0;
  for (j = 0; j < size; j++)
  {
    result[i][j] +=  array1[i][k] * array2[k][j];
  }
 }
}
end = clock();
total = ((double)(end-start))/CLOCKS_PER_SEC;
printf("Resultant matrix::\n");
printMatrix(result,size);
printf("Time Taken:: %f\n",total);
for (int i = 0; i < size; i++)
{
 free(array1[i]);
 free(array2[i]); /* code */
}
free(array1);
free(array2);
for (int i = 0; i < size; i++)
{
 free(result[i]); /* code */
}

free(result);

return 0;
}