#define EXTRACT_BITS(n,i) ((n&(1<<i))?1:0)
#include<stdio.h>
#include<mpi.h>
int check_circuit(int id,int z){
   int v[16];
   for (int i = 0; i < 16; i++)
      v[i] = EXTRACT_BITS(z,i);
      if((v[0]||v[1]) && (!v[1]||!v[3]) && (v[2]||v[3])&&
      (!v[3]||!v[4])&&(v[4]||!v[5])
      && (v[6] || !v[15]) && v[5]|| v[6]
      && (!v[7] || !v[13]) && (v[8] || v[9])
      && (v[8 || !v[9]]) && (!v[9] || !v[10])
      && (v[9] || v[11]) && ( v[10] || v[11])
      && (v[12] || v[13]) && (v[13] || !v[14])
      && (v[14] || v[15])){

         printf("(%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",id,v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11],v[12],v[13],v[14],v[15]);
         fflush(stdout);
         return 1;
      }
      else 
         return 0;/* code */
   }
   
int main(int argc ,char* argv[]){
   int id,p;
   int solutions,global_solutions;
   // void check_circuit(int,int);
   int check_circuit(int,int);
   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD , &id);
   MPI_Comm_size( MPI_COMM_WORLD,  &p);
   solutions = 0;
   for (int i = id; i < 65536; i+=p)
   {
   //  check_circuit(id,i);  /* code */
   solutions+=check_circuit(id,i);
   }
   MPI_Reduce( &solutions , &global_solutions , 1 , MPI_INT , MPI_SUM , 0 , MPI_COMM_WORLD);
   printf("Process %d is done\n",id);
   fflush(stdout);
   MPI_Finalize();
   if(id == 0)
      printf("There ar %d different solutions\n",global_solutions);
   return 0;
}