#define SIZE 1000000
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
int gammaa(int a,int b);
int alpha();
int beta();
int delta();
float epsilon(int u,int v);
int alpha(){
   int x=1;
   for(int i ;i<SIZE;i++)
   x = x+i;
   return x;
}

int beta(){
   int y=1;
   for (int i = 0; i < SIZE; i++)
   {
     y = (y*i)+2; /* code */
   }
   return y;
}
int gammaa(int a,int b){
   return a*b;
}
int delta(){
   int z=2;
   for (int i = 0; i < SIZE; i++)
   {
     z = 2*z*i; /* code */
   }
   return z;
}
float epsilon(int u,int v){
   int h ;
   h = (u*v)/2;
   return h;
}
int main(){
   int x,y,z;
   int v;
   #pragma omp sections private(x,y,z,v)
   {
      #pragma omp section
         x = alpha();
      #pragma omp section
         y = beta(); 
      #pragma omp section
         z - delta();
   }
   v = gammaa(x,y);
   printf("Epsilon:: %6.2f",epsilon(v,z));
   return 0;
}