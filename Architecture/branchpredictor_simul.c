#define __STDC_FORMAT_MACROS
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void simulate(FILE* inputFile, FILE* outputFile)
{
  // See the documentation to understand what these variables mean.
  int32_t microOpCount;
  uint64_t instructionAddress;
  int32_t sourceRegister1;
  int32_t sourceRegister2;
  int32_t destinationRegister;
  char conditionRegister;
  char TNnotBranch;
  char loadStore;
  int64_t immediate;
  uint64_t addressForMemoryOp;
  uint64_t fallthroughPC;
  uint64_t targetAddressTakenBranch;
  char macroOperation[12];
  char microOperation[23];
  float clockcycle_ALU = 1;     /*For  Intel Silvermont*/
  int64_t clockcycle_jump = 1;  
  int64_t clock_conditional = 1;
  int64_t loadcc = 3;
  int64_t storecc = 2;
  int64_t faddcc=1;
  int64_t fsubcc =1;
  int64_t fmulcc =1;
  int64_t fdivcc =1;

  int fpadd= 0;
  int fpsub= 0;
  int fpmul= 0;
  int fpdiv= 0;
  int64_t totalMicroops = 0;
  int64_t totalMacroops = 0;
  int64_t ld = 0;
  int64_t conditionbranchcount = 0;
  int64_t numofStores = 0;
  int64_t takenbranch = 0;
  int64_t notTakencount = 0;
  int64_t unconditionalcount = 0;
  int64_t alucounter = 0;
  float average_CPI;
  bool state = true;
  int64_t count_correct=0;
  int64_t count_incorrect=0;
  int count=0;
//   fprintf(outputFile, "Processing trace...\n");
  
  while (true) {
    int result = fscanf(inputFile, 
                        "%" SCNi32
                        "%" SCNx64 
                        "%" SCNi32
                        "%" SCNi32
                        "%" SCNi32
                        " %c"
                        " %c"
                        " %c"
                        "%" SCNi64
                        "%" SCNx64
                        "%" SCNx64
                        "%" SCNx64
                        "%11s"
                        "%22s",
                        &microOpCount,
                        &instructionAddress,
                        &sourceRegister1,
                        &sourceRegister2,
                        &destinationRegister,
                        &conditionRegister,
                        &TNnotBranch,
                        &loadStore,
                        &immediate,
                        &addressForMemoryOp,
                        &fallthroughPC,
                        &targetAddressTakenBranch,
                        macroOperation,
                        microOperation);
                        
    if (result == EOF) {
      break;
    }
   if(TNnotBranch=='T')
      fprintf(outputFile,"1");
      // count+=1;
   if(TNnotBranch=='N')
      fprintf(outputFile,"0");
      // count+=1;
   
    //1 bit predictor
   if(TNnotBranch=='T' && state== true)
      count_correct+=1;
   if(TNnotBranch == 'N' && state == false)
      count_correct+=1;
   if(TNnotBranch == 'N' && state == true)
      state = false;
      count_incorrect+=1;
   if(TNnotBranch == 'T' && state==false)
      state=true;
      count_incorrect+=1;





    //Number of Loads
   if(loadStore == 'L')
    	ld++;

    if(loadStore == 'S')
        numofStores++;

    if (result != 14) {
      fprintf(stderr, "Error parsing trace at line %" PRIi64 "\n", totalMicroops);
      abort();
    }
     
    if ((targetAddressTakenBranch != 0 ) && (conditionRegister == 'R'))
    {if(TNnotBranch == 'T')
      takenbranch++;
    }  

    if(strcmp(microOperation,"ADD")== 0 || strcmp(microOperation,"ADD_IMM")==0 || strcmp(microOperation,"SUB")==0 || strcmp(microOperation,"OR")==0||
    strcmp(microOperation,"SUB_IMM")== 0 || strcmp(microOperation,"AND")==0 || strcmp(microOperation,"XOR")==0 || strcmp(microOperation,"NOT") == 0) {
      alucounter++;
    }
    if (strcmp(microOperation,"SHL")==0 || strcmp(microOperation,"SHL_IMM") == 0 || strcmp(microOperation,"SHR_IMM")==0 || strcmp(microOperation,"AND_IMM")==0)
    {
     alucounter++;
    } 
    if ((targetAddressTakenBranch != 0 ) && (conditionRegister == 'R')){
    if(TNnotBranch == 'N'){
        notTakencount++;
    }
    }
    if ((targetAddressTakenBranch != 0 ) && (conditionRegister == 'R'))
    {
     conditionbranchcount++; 
    }
     
    if ((targetAddressTakenBranch != 0 ) && (conditionRegister == '-'))
    {
      unconditionalcount++;
    }
    // For each micro-op
    totalMicroops++;

    // For each macro-op:
    if (microOpCount == 1) {
      totalMacroops++;
    }
    if(strncmp(microOperation,"FP_ADD",strlen("FP_ADD")==0)){
      fpadd++;
    }
    
    if(strncmp(microOperation,"FP_SUB",strlen("FP_SUB")==0)){
      fpsub++;
    }

    if(strncmp(microOperation,"FP_MUL",strlen("FP_DIV")==0)){
      fpmul++;
    }
    if(strncmp(microOperation,"FP_DIV",strlen("FP_DIV")==0)){
      fpdiv++;
    }
  }
   

  
    average_CPI = ((clockcycle_ALU*alucounter)+(clockcycle_jump*unconditionalcount)+(clock_conditional*conditionbranchcount)+
    (loadcc*ld) + (storecc * numofStores)+(faddcc*fpadd)+(fsubcc*fpsub)+(fmulcc*fpmul)+(fdivcc*fpdiv))/totalMicroops;
    
    double percen_alu = (double)(alucounter*100)/totalMicroops;
    double percen_cond_branch = (double)(conditionbranchcount*100)/totalMicroops;
    double percen_load = (double)(ld*100)/totalMicroops;
    double percen_store = (double)(numofStores*100)/totalMicroops;
    double percen_uncond = (double)(unconditionalcount*100)/totalMicroops;
//   fprintf(outputFile, "Processed %" PRIi64 " trace records.\n", totalMicroops);

//   fprintf(outputFile, "Micro-ops: %" PRIi64 "\n", totalMicroops);
//   fprintf(outputFile, "Macro-ops: %" PRIi64 "\n", totalMacroops);
//   fprintf(outputFile, "Number of loads : %" PRIi64 "\n",ld);
//   fprintf(outputFile, "Stores : %" PRIi64 "\n", numofStores );
//   fprintf(outputFile, "Taken : %" PRIi64"\n" , takenbranch );
//   fprintf(outputFile, "Not Taken : %" PRIi64 "\n" ,notTakencount );
//   fprintf(outputFile, "Condition Branch Count : %" PRIi64 "\n" ,conditionbranchcount );
//   fprintf(outputFile, "Uncondition Branch Count : %" PRIi64 "\n" ,unconditionalcount );
//   fprintf(outputFile, "ALU COUNT : %" PRIi64 "\n" ,alucounter );
//   fprintf(outputFile, "FP ADD Count: %d"  "\n", fpadd);
//   fprintf(outputFile, "FP SUB Count: %d"  "\n", fpsub);
//   fprintf(outputFile, "FP MUL Count: %d" "\n", fpmul);
//   fprintf(outputFile, "FP DIV Count: %d"  "\n", fpdiv);
//   fprintf(outputFile, "**********************************""\n\n");
//   fprintf(outputFile, "1 Bit count:: %ld""\n\n",count_correct);
//   fprintf(outputFile, "Total Count: %d"  "\n", count);
//   fprintf(outputFile,"Miss rate:: %ld""\n\n",count_incorrect/totalMicroops);
//   fprintf(outputFile, "AVERAGE CPI: %f""\n",average_CPI);
//   fprintf(outputFile,"\n");  
//   fprintf(outputFile,"Percentage of ALU :: %f""\n",percen_alu);
//   fprintf(outputFile,"Percentage of Conditional Branch :: %f""\n",percen_cond_branch);
//   fprintf(outputFile,"Percentage of Loads :: %f""\n",percen_load);
//   fprintf(outputFile,"Percentage of Stores :: %f""\n",percen_store);
//   fprintf(outputFile,"Percentage of Unconditional Branch :: %f""\n",percen_uncond);
}

int main(int argc, char *argv[]) 
{
  FILE *inputFile ;
  FILE *outputFile ;
  
  if (argc<2){
   printf("Usage: %s <input_file> [<outpur_file>]\n",argv[0]);
   return 1;
  }

  if (argc >= 2) {
    inputFile = fopen(argv[1], "r");
    assert(inputFile != NULL);
  }
  if (argc >= 3) {
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
  }
  
  simulate(inputFile, outputFile);
  fclose(inputFile);
  if(outputFile!=stdout){
   fclose(outputFile);
  }
  return 0;
}

