#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(){
    int size1,size2;
    float time=0;
    printf("Enter the size of array1 :: ");
    scanf("%d",&size1);
    printf("Enter the size of array2 :: ");
    scanf("%d",&size2);
    int array1[size1];
    int array2[size2];
    int array3[size2];
//printf("Enter the elements of array :: ");
clock_t t1 = clock();
//srand(time(0));
for(int i = 0;i<size1;i++){
  //scanf("%d",&array[i]);
    array1[i] = rand()%100+1;
}
for(int i = 0;i<size2;i++){
  //scanf("%d",&array[i]);
    array2[i] = rand()%100+1;
}
printf("Elements of array1 are:: ");
for (int i = 0; i < size1; i++)
{
  printf("%d ",array1[i]);  /* code */
}
printf("\nElements of array2 are:: ");
for (int i = 0; i < size2; i++)
{
  printf("%d ",array2[i]);  /* code */
}
if (size1 == size2)
{
for (int i = 0; i < size2; i++)
{
    array3[i] =  array1[i]+array2[i];   /* code */
}
printf("\nFinal array elements are:: ");
for (int i = 0; i < size2; i++)
{
  printf("%d ",array3[i]);  /* code */
}
}
else {
    printf("\n!!!Sizes of array doesnot match!!!Cant");
}
clock_t t2 =  clock();
time = (float)(t2-t1)/CLOCKS_PER_SEC;
printf("\nTime taken : %f\n",time);
}