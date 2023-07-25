#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(){
int rows,columns;
int rows2,columns2;
int result[rows][columns];
int array1[rows2][columns2];
int array2[1000][1000];
printf("Enter the number of rows::");
scanf("%d %d",&rows,&columns);
printf("Enter the number of columns::");
scanf("%d %d",&rows2,&columns2);
//adding elements to the arrays
for (int i = 0; i < rows; i++)
{
for (int j = 0; j < columns; j++)
{
    array1[i][j] = rand()%100+1;
}
}
for (int i = 0; i < rows; i++)
{
for (int j = 0; j < columns; j++)
{
  array2[i][j]= rand()%100+1;
}
}
for (int i = 0; i < rows; i++)
{
for (int j = 0; j < columns; j++)
{
  printf("%d\t",array1[i][j]);
}
}

for (int i = 0; i < rows; i++)
{
for (int j = 0; j < columns; j++)
{
    printf("%d\t",array2[i][j]);
}
}
//Multiplying the matrices
for (int i = 0; i < rows; i++)
{
 for (int j = 0; j < columns2; j++)
 {
  result[i][j]=0;
  for (int k = 0; k < columns2; k++)
  {
    result[i][j] =  array1[i][k] * array2[k][j];
  }
 }
}

for (int i = 0; i < rows; i++)
{
for (int j = 0; j < columns; j++)
{
  printf("%d\t",result[i][j]);  /* code */
}
printf("\n");
}
return 0;
}