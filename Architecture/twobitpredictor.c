
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<string.h>
#include<assert.h>
int twobitpredictor(FILE *inputFile) {
    int correct_count = 0;
    int incorrect_count = 0;
    // The states here are represented using two-bit saturating counters:
    // 00 - Strong not taken
    // 01 - Weakly not taken
    // 10 - Weakly taken
    // 11 - Strongly taken
    int state = 3; // Initialize to Strong  taken (11)
    char c;
    while((c=fgetc(inputFile))!=EOF){
    
   //  for (int i = 0; i < strlen(A); i++) {
      //   switch (state) {
      //       case 0: // Strong not taken (00)
      //       case 1: // Weakly not taken (01)
      //           if (c == '0') {
      //               correct_count += 1; // Correctly predicted as not taken
      //               if (state < 3) {
      //                   state = state + 1; // Move to the next state
      //               }
      //               else{
      //                state = 3;
      //               }
      //           } else {
      //               incorrect_count += 1; // Incorrectly predicted as taken
      //               state = 1; // Move to Weakly not taken (01)
      //           }
      //           break;

      //       case 2: // Weakly taken (10)
      //       case 3: // Strongly taken (11)
      //           if (c == '1') {
      //               correct_count += 1; // Correctly predicted as taken
      //               if (state > 0) {
      //                   state = state - 1; // Move to the previous state
      //               }
      //               else{
      //                state =0;
      //               }
      //           } else {
      //               incorrect_count += 1; // Incorrectly predicted as not taken
      //               state = 2; // Move to Weakly taken (10)
      //           }
      //           break;
      //   }
      // if(c=='1' && state == 3)
      //    correct_count+=1;
      // else if(c == '0' && state==3)
      //          state=2;
      //      else if(c=='0' && state == 2)
      //             state = 0;
      //          else if(c=='1' && state==2)
      //                state = 3;
      //                else if(c=='0' && state == 0)
      //                         correct_count+=1;
      //                      else if(c=='1'&& state == 0 )
      //                               state = 1;
      //                           else if(c=='0' && state == 1)
      //                                  state=0;
      //                                else if(c=='1'&& state == 1 )
      //                                        state = 3;
      //    else if(c == 'T' && state ==10)
      //          state=11;
        if ((c == '1' && state == 3) || (c == '0' && state == 2))
            correct_count += 1;

        if (state == 3 && c == '0')
            state = 2;
        else if (state == 3 && c == '1')
            state = 3;
        else if (state == 2 && c == '0')
            state = 0;
        else if (state == 2 && c == '1')
            state = 3;
        else if (state == 0 && c == '0')
            state = 0;
        else if (state == 0 && c == '1')
            state = 1;
        else if (state == 1 && c == '0')
            state = 0;
        else if (state == 1 && c == '1')
            state = 3;
    }
    return correct_count;
}

int main(int argc, char *argv[]) {
   //  char binary_array[] = "TTTNTNTNNTTNNN";
    int count_correct, count_incorrect;
    FILE *inputFile;
    if(argc<2){
    printf("usage:%s <input_file>\n",argv[0]);
    return 1;
  }
   if (argc >= 2) {
    inputFile = fopen(argv[1], "r");
    assert(inputFile != NULL);
  }
    count_correct = twobitpredictor(inputFile);
    fseek(inputFile,0,SEEK_END);
    size_t inputlength = ftell(inputFile);
    printf("Correct Prediction :: %d\n",count_correct);
   printf("length=%ld\n",inputlength);
   count_incorrect = inputlength - count_correct;
   printf("InCorrect Prediction :: %d\n",count_incorrect);
   float miss_rate = (float)count_incorrect/inputlength;
   float accuracy = (float)count_correct/inputlength;
   printf("Accuracy :: %f\n",accuracy);
   printf("Miss Rate:: %f\n",miss_rate);
   fclose(inputFile);

    return 0;
}
