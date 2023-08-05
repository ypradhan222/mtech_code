#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>

int second_max(int *array,int left,int right,int *maxi,int *secmax){
   int mid;
   int *max1,*max2;
   if(left == right){
      // max =array[left];
      *maxi = array[left];
      *secmax = -1 ;
   }
   else if (right-left==1){
      *maxi = max(array[left],array[right]);
      *secmax = min(array[left],array[right]);
   }
   else {
      mid = int((left+right)/2);
       *max1 = second_max(array,left,right,max1,max2); 


   }


}
int main(){
   int size;
   printf("Enter the size:");
   scanf("%d",&size);
   srand(time(NULL));
   int *array = (int *)malloc(sizeof(int) *size);
   for(int i =0;i<size;i++){
      array[i] = rand()%100+1;
   }
   for (int i = 0; i < size; i++)
   {
    printf("%3d",array[i]);  /* code */
   }
   
   
   
   
   
   
   return 0;
}