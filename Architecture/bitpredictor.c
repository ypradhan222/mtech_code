#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define NUM_BRANCHES 100
bool binary_array[NUM_BRANCHES];  //Branch history table -true indicates
                                  //branch is predicted taken and false otherwise
bool predict_branch(int index_branch){
   return binary_array[index_branch];
}
int main(){
   for (int i = 0; i < NUM_BRANCHES; i++)
   {
      binary_array[i] = False;  /* code */
   }
   

   return 0;
}