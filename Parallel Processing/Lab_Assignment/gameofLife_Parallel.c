/*
Implementation of Game of life using openmp 
Reg.N0 -23366
Name - Yogen Pradhan
*Here the '@' cells represent the dead cells
and 1 represent the alive cells. 

The board size here is a square which user will put as
size.
Rules:
1.Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2.Any live cell with two or three live neighbours lives on to the next generation.
3.Any live cell with more than three live neighbours dies, as if by overpopulation.
4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<stdbool.h>
#include<time.h>
#include<unistd.h>
void printMatrix(char **array1,int size){
//  printf("\033[2J\033[1;1H");
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
//    if(array1[i][j] == '@'){
//   printf("\033[42m  \033[0m");   
//    }
//    else
//       printf("\033[30m  \033[0m");//Used ANSI escape code for better formatting
//                                     //30 for black background for dead cells
 printf("%2c",array1[i][j]);
}
}
 printf("\n");
}

void freeingMatrix(char **matrix,int size){
   for (int i = 0; i < size; i++)
   {
    free(matrix[i]);  /* code */
   }
   free(matrix);  
}

// Testing the cells are alive or not 
bool isAlive(char **matrix,int x,int y,int size){
   int alive = 0;
   // test left
   if(x>0 && matrix[x-1][y] == '@')
      alive+=1;
  
   // Test right
   if(x < size-1 && matrix[x+1][y] == '@')
      alive+=1;
  
   // Test above
   if(y>0 && matrix[x][y-1]=='@')
      alive+=1;
  
   //Test bottom 
   if (y<size-1 && matrix[x][y+1] == '@')
      alive+=1; 

   //Test top left
   if (x>0 && y>0 && matrix[x-1][y-1]=='@')
      alive+=1;
   
   //Test top right
   if(x<size-1 && y>0 && matrix[x+1][y-1]=='@')
      alive+=1;
   
   //Test bottom left
   if(x>0 && y<size-1 && matrix[x-1][y+1]=='@')
      alive+=1;

   //Test bottom right
   if (x<size-1 && y<size-1 && matrix[x+1][y+1]=='@')
      alive+=1;

   //Rules of the game now
   if (matrix[x][y] == '@' && (alive==2 || alive ==3))
      return true;    //If two or three neighbors are alive then survives
   
   if (matrix[x][y] == '@' && alive < 2)
      return false;    //Fewer than 2 neighbors dies by underpopulation
   
   if (matrix[x][y] == '@' && alive > 3)
      return false;    //More than 3 neighbor dies by overpopulation
   
   if(matrix[x][y] == '@' && alive == 3)
      return true;    //Dead cell with three live neighbors becomes a live cell

   return false;
}

int main(){
   int size;
   printf("Enter size of grid::");
   scanf("%d",&size);
   
   char **matrix1 = (char**)malloc(sizeof(char*) *size);
   if(matrix1==NULL){
      perror("Memory allocation failed.");
      return EXIT_FAILURE;
   }
   for (int i = 0; i < size; i++)
   {
     matrix1[i] = (char *)malloc(sizeof(char) *size); /* code */
   }
   

   char **matrix2 = (char**)malloc(sizeof(char*) *size);
   if(matrix1==NULL){
      perror("Memory allocation failed.");
      freeingMatrix(matrix1,size);
      return EXIT_FAILURE;
   }
   
   for (int i = 0; i < size; i++)
   {
     matrix2[i] = (char *)malloc(sizeof(char) *size); /* code */
   }
   
   srand(time(NULL));
   for (int i = 0; i < size; i++)
   {
    for (int j = 0; j < size; j++)
    {
      if(rand() % 2 == 0)
         matrix1[i][j] = '@' ; /* code */
      else
         matrix1[i][j] = '*';
    
    }  
   }
   omp_set_num_threads(1);
   double start,end;
   //Now we check for alive points in the grid
   int generate = 0;  //For generating the grid
   start = omp_get_wtime();
   while(generate < 1000){   
      #pragma omp parallel for schedule(dynamic,8)
      for (int i = 0; i < size; i++)
      {
       for (int j = 0; j < size; j++)
       { 
         // int id = omp_get_thread_num();
         // printf("Thread %d is working on i = %d ,j =%d\n",id,i,j);
         if (isAlive(matrix1,i,j,size))
            matrix2[i][j] = '@';
         else
            matrix2[i][j] = '*';
       }
      }
      #pragma omp parallel sections
      {
         #pragma omp section
         {
            //Swapping the grids pointers
         char **temp = matrix1;
         matrix1 = matrix2;
         matrix2 = temp;
         }
      }
      system("clear");
      printMatrix(matrix1,size);
      printf("\n");
   
      usleep(100000);
      generate+=1;

   }
   end = omp_get_wtime();
   printf("Execution time for  iteration is %f secs\n",(end-start));
   freeingMatrix(matrix1,size);
   freeingMatrix(matrix2,size);
   
   return 0;
}