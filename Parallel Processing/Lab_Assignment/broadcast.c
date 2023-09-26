#include<stdio.h>
#include<mpi.h>
int main(int argc,char*argv[]){
   MPI_Init( &argc ,& argv);
   int rank,size;
   MPI_Comm_rank( MPI_COMM_WORLD , & rank);
   MPI_Comm_size( MPI_COMM_WORLD , & size);
   int message =0;
   if(rank==0){
      message = 23;
   }
   MPI_Bcast( &message , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
   printf("Rank %d received the message %d\n",rank,message);
   MPI_Finalize();
   return 0;
}