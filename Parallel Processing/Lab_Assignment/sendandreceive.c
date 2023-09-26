#include<stdio.h>
#include<mpi.h>

int main( int argc, char *argv[])
{
   int rank, size;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   
   if (size<2){
      printf("THis requires atleast two processes");
      MPI_Finalize();
      return 1;
   }
   if(rank==0){
      int message=42;
      MPI_Send( &message , 1 , MPI_INT , 1 , 0 ,MPI_COMM_WORLD);
      printf("Process 0 sent message %d\n",message);
   }
   else if(rank==1){
      int receivedmessage;
      MPI_Recv( &receivedmessage , 1 ,MPI_INT ,0 , 0 , MPI_COMM_WORLD ,MPI_STATUS_IGNORE);
      printf("Process 1 receivd message %d\n",receivedmessage);
   }
   
   MPI_Finalize();
   
   return 0;
}