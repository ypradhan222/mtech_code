/*
Implementation of Game of life using openmp 
Reg.N0 -23366

*Here the '*' cells represent the dead cells
and 1 represent the alive cells. 
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<stdbool.h>
#include<time.h>
#include<unistd.h>
void printMatrix(char **array1,int size){
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
  printf("%2c",array1[i][j]);
}
 printf("\n");
}
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
   if(x>0 && matrix[x-1][y] == '1')
      alive+=1;
  
   // Test right
   if(x < size-1 && matrix[x+1][y] == '1')
      alive+=1;
  
   // Test above
   if(y>0 && matrix[x][y-1]=='1')
      alive+=1;
  
   //Test bottom 
   if (y<size-1 && matrix[x][y+1] == '1')
      alive+=1; 

   //Test top left
   if (x>0 && y>0 && matrix[x-1][y-1]=='1')
      alive+=1;
   
   //Test top right
   if(x<size-1 && y>0 && matrix[x+1][y-1]=='1')
      alive+=1;
   
   //Test bottom left
   if(x>0 && y<size-1 && matrix[x-1][y+1]=='1')
      alive+=1;

   //Test bottom right
   if (x<size-1 && y<size-1 && matrix[x+1][y+1]=='1')
      alive+=1;

   //Rules of the game now
   if (matrix[x][y] == '1' && (alive==2 || alive ==3))
      return true;    //If two or three neighbors are alive then survives
   
   if (matrix[x][y] == '1' && alive < 2)
      return false;    //Fewer than 2 neighbors dies by underpopulation
   
   if (matrix[x][y] == '1' && alive > 3)
      return false;    //More than 3 neighbor dies by overpopulation
   
   if(matrix[x][y] == '*' && alive == 3)
      return true;    //Dead cell with three live neighbors becomes a live cell

   return false;
}

int main(){
   int size;
   printf("Enter size of grid::");
   scanf("%d",&size);
   
   char **matrix1 = (char**)malloc(sizeof(char*) *size);
   for (int i = 0; i < size; i++)
   {
     matrix1[i] = (char *)malloc(sizeof(char) *size); /* code */
   }


   char **matrix2 = (char**)malloc(sizeof(char*) *size);
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
         matrix1[i][j] = '1' ; /* code */
      else
         matrix1[i][j] = '*';
    
    }  
   }
   
   //Now we check for alive points in the grid
   int generate = 0;
   while(generate < 30){
      for (int i = 0; i < size; i++)
      {
       for (int j = 0; j < size; j++)
       {
         if (isAlive(matrix1,i,j,size))
            matrix2[i][j] = '1';
         else
            matrix2[i][j] = '*';
       }
      }
      char **temp = matrix1;
      matrix1 = matrix2;
      matrix2 = temp;
      
      printMatrix(matrix1,size);
      printf("\n");
      usleep(500000);
      generate+=1;

   }
   freeingMatrix(matrix1,size);
   freeingMatrix(matrix2,size);
   
   
   return 0;
}