#define SIZE 1000000
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void main(){
    int *array = (int *)malloc(sizeof(int) *SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = i;   /* code */
    }
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d",array[i]);   /* code */
    }
    
}