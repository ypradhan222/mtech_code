#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>
int onebitpredictor(FILE *inputFile){
   bool state = true;
   int correct_count=0;
   int incorrect_count =0;
   char c;
   while((c=fgetc(inputFile))!=EOF){
  //  for (int i = 0; i < strlen(A); i++)
  //  {
    if (c == '1' && state == true )   //1 is for Taken and 0 for not taken
      correct_count+=1;
    if(c == '0' && state== false)
      correct_count+=1;
    if(c == '0' && state==true)
      state=false;
      incorrect_count+=1;
    if(c=='1' && state==false)
      state=true;
      incorrect_count+=1 ;  /* code */
  //  }
   }
   return correct_count;
}
int main(int argc,char *argv[]){
   FILE *inputFile ;
  //  char binary_array[]="TTTNTNTNNTTNNN";
  if(argc<2){
    printf("usage:%s <input_file>\n",argv[0]);
    return 1;
  }
   if (argc >= 2) {
    inputFile = fopen(argv[1], "r");
    assert(inputFile != NULL);
  }
   int count_correct,count_incorrect;
   count_correct = onebitpredictor(inputFile);
   fseek(inputFile,0,SEEK_END);
   size_t inputlength = ftell(inputFile);
  //  rewind(inputFile);
   printf("Correct Prediction :: %d\n",count_correct);
   printf("length=%ld\n",inputlength);
   count_incorrect = inputlength - count_correct;
   printf("InCorrect Prediction :: %d\n",count_incorrect);
   float miss_rate = (float)count_incorrect/inputlength;
   printf("Miss Rate:: %f\n",miss_rate);
   fclose(inputFile);
   return 0;
}