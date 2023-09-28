#include <stdio.h>
#include <stdlib.h>
#include<FreeImage.h>

void readFile(const char *filename){
    FILE *file = fopen(filename,"r");
    if(file==NULL){
        perror("Error opening the file");
        return NULL;
    }
}