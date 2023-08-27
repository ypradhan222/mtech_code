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
  omp_set_num_threads(16);
  if (n==1){
    printf("1 \n");
  }
  else{
//   Marking every number as prime number first
  #pragma omp parallel for
  for (int i = 0; i <= n; i++)
  {
  number[i] = true;  /* code */
  }
//   Unmarking the elements which are even and its multiples
// also the other prime's multiples.
   int i;
//   #pragma omp parallel for 
  for (  i = 2; i*i <= n; i++)
  {
  if (number[i]==true)
  { 
   #pragma omp parallel for
   for (int j = i*i; j <= n; j+=i)
  {
    number[j] = false; /* code */
  }   
   }    
  }
  double time1 = omp_get_wtime();
  int count=0;
  int output_index = 0;
  #pragma omp parallel for reduction(+ : count)
  for (int i = 2; i <= n; i++)
  {
  if(number[i]==true){
      #pragma omp critical
      output[output_index] = i;
      output_index++;
      count++;
  }  /* code */
  }
  double time2 = omp_get_wtime();
  for (int i = 0; i <count; i++)
  {
  printf("%8d",output[i]);  /* code */
  }
  printf("\n");  
  printf("Execution Time :: %f\n",time2 -time1);
  }
  return 0;
}