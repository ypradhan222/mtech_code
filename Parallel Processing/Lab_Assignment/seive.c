#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<stdbool.h>

int main(){
   int n;
   printf("Enter the limit(n):");
   scanf("%d",&n);
   bool number[n+1];
   int output[n+1];
for (int i = 0; i <= n; i++)
{
number[i] = true;  /* code */
}
   for (int i = 2; i*i <= n; i++)
   {
    if (number[i]==true)
    {for (int j = i*i; j <= n; j+=i)
    {
      number[j] = false; /* code */
    }   
    }    
   }
   int count=0;
   for (int i = 2; i < n; i++)
   {
    if(number[i]==true){
      output[i] = i;
      count++;
    }  /* code */
   }
   for (int i = 0; i < count; i++)
   {
    printf("%3d",output[i]);  /* code */
   }
   
   
   return 0;
}