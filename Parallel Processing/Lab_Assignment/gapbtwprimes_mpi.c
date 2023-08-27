#include<stdio.h>
#include<mpi.h>
#include<stdbool.h>
bool isprime(int n){
   if(n<=1)
      return false;
   if(n<=3)
      return true;
   if(n%2==0 || n%3==0)
      return false;
   for (int i = 5; i <= n; i+=6)
   {
    if(n%i==0 || n%(i+2)==0)
      return false;  /* code */
   }
   return true;
   
}
int largest_gap(int start,int end){
   int largest_gap = 0;
   int previous_prime = -1;
   for (int i = 0; i <=end; i++)
   {
     if(isprime(i)){
         if(previous_prime!=-1){
            int gap = i - previous_prime;
            if(gap >largest_gap){
               largest_gap = gap;
            }
         }
         previous_prime = i;
     }  /* code */
   }
   return largest_gap;
}
int main(int argc,char *argv[]){
   int rank,size;
   MPI_Init( &argc ,  &argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size( MPI_COMM_WORLD , &size);

   int chunk_size = 1000000/size;
   int start = rank*chunk_size+1;
   int end = (rank+1)*chunk_size;
   int large= largest_gap(start,end);
   int max_gap;
   MPI_Reduce( &large , &max_gap , 1 , MPI_INT , MPI_MAX , 0 , MPI_COMM_WORLD);
   if(rank==0){
      printf("The largest prime gap among all integers less than 1000000 is %d\n",max_gap);
   }
   MPI_Finalize();
   return 0;
}