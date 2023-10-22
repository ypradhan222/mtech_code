// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stdbool.h>

// #define NUMBER_TABLES 4
// #define BIMODAL_SIZE 1024
// #define BIMODAL_MAX_COUNTER 3
// #define TAGPREDLOG 10
// #define TAGPRED_CTR_BITS 3

// enum states {
//     STRONG_NOT_TAKEN,
//     WEAKLY_NOT_TAKEN,
//     WEAKLY_TAKEN,
//     STRONGLY_TAKEN
// };

// struct Entry {
//     int8_t counter; // 3-bit Counter for prediction (sign provides the prediction)
//     uint32_t tag;
//     uint8_t usefulbits; // 2-bit counter
// };

// struct bimodalTable {
//     int8_t counter; // 2-bit counter
// };

// struct TAGEPredictor {
//     struct bimodalTable bimodaltable[BIMODAL_SIZE];
//     struct Entry tageTables[NUMBER_TABLES][BIMODAL_SIZE];
//     uint32_t tag[NUMBER_TABLES];
//     int32_t indexTagPred[NUMBER_TABLES];
//     int32_t tagComp[2][NUMBER_TABLES];
//     int32_t indexComp[NUMBER_TABLES];
//     int32_t PHR;
//     enum states primePred;
//     enum states altPred;
//     int32_t primeBank;
//     int32_t altBank;
//     struct Entry *tagPred[NUMBER_TABLES];
// };

// void initialization(struct TAGEPredictor* tage) {
//     // Tage tables initialization
//     for (int i = 0; i < NUMBER_TABLES; i++) {
//         for (int j = 0; j < BIMODAL_SIZE; j++) {
//             tage->tageTables[i][j].counter = 0;
//             tage->tageTables[i][j].tag = 0;
//             tage->tageTables[i][j].usefulbits = 0;
//         }
//     }

//     // Bimodal table initialization
//     for (int i = 0; i < BIMODAL_SIZE; i++) {
//         tage->bimodaltable[i].counter = STRONGLY_TAKEN;
//     }
// }

// bool GetBasePrediction(int8_t bimodalCounter) {
//     // Logic for base prediction using the 2-bit counter
//     return bimodalCounter >= (BIMODAL_MAX_COUNTER / 2);
// }

// bool getPrediction(struct TAGEPredictor* predictor, uint32_t branchPC) {
//     bool basePrediction;
//     uint32_t index = (branchPC % BIMODAL_SIZE);
//     int8_t bimodCounter = predictor->bimodaltable[index].counter;
//     basePrediction = GetBasePrediction(bimodCounter);

//     // Calculating the tag
//     for (int i = 0; i < NUMBER_TABLES; i++) {
//         predictor->tag[i] = branchPC ^ predictor->tagComp[0][i] ^ (predictor->tagComp[1][i] << 1);
//         // Masking the tag
//         predictor->tag[i] &= ((1 << ((i < 2) ? 9 : 8)) - 1);
//     }

//     int32_t index_mask = ((1 << TAGPREDLOG) - 1);
//     for (int i = 0; i < NUMBER_TABLES; i++) {
//         predictor->indexTagPred[i] = branchPC ^ (branchPC >> ((i < 2) ? TAGPREDLOG : (TAGPREDLOG - i + 1))) ^
//                                      predictor->indexComp[i] ^ predictor->PHR ^ (predictor->PHR >> TAGPREDLOG);
//         // Mask the index
//         predictor->indexTagPred[i] &= index_mask;
//     }
//     predictor->primePred = STRONG_NOT_TAKEN;
//     predictor->altPred = STRONG_NOT_TAKEN;
//     predictor->primeBank = NUMBER_TABLES;
//     predictor->altBank = NUMBER_TABLES;

//     // Check if any tag matches
//     for (int iterator = 0; iterator < NUMBER_TABLES; iterator++) {
//         if (predictor->tagPred[iterator][predictor->indexTagPred[iterator]].tag == predictor->tag[iterator]) {
//             predictor->primeBank = iterator;
//             break;
//         }
//     }

//     for (int iterator = predictor->primeBank + 1; iterator < NUMBER_TABLES; iterator++) {
//         if (predictor->tagPred[iterator][predictor->indexTagPred[iterator]].tag == predictor->tag[iterator]) {
//             predictor->altBank = iterator;
//             break;
//         }
//     }

//     if (predictor->primeBank < NUMBER_TABLES) {
//         if (predictor->altBank == NUMBER_TABLES) {
//             predictor->altPred = basePrediction;
//         } else {
//             if (predictor->tagPred[predictor->altBank][predictor->indexTagPred[predictor->altBank]].counter >= (1 << (TAGPRED_CTR_BITS - 1)))
//                 predictor->altPred = true; // TAKEN
//             else
//                 predictor->altPred = false; // NOT_TAKEN
//         }
//         if ((predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]].counter != 3) ||
//             (predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]].counter != 4) ||
//             (predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]].usefulbits != 0)) {
//             if (predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]].counter >= (1 << (TAGPRED_CTR_BITS - 1)))
//                 predictor->primePred = true; // TAKEN
//             else
//                 predictor->primePred = false; // NOT_TAKEN
//             return predictor->primePred;
//         } else {
//             return predictor->altPred;
//         }
//     } else {
//         predictor->altPred = basePrediction;
//         return predictor->altPred;
//     }
//    //  return basePrediction; // Return base prediction for now
// }

// int main(int argc, char* argv[]) {
//     struct TAGEPredictor predictor;
//     uint32_t PC = 0x12345678;
//     initialization(&predictor); // Initialize the predictor
//     bool prediction = getPrediction(&predictor, PC);
//     if (prediction) {
//         printf("Predicted: Taken\n");
//     } else {
//         printf("Predicted: Not Taken\n");
//     }

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define NUMBER_TABLES 4
#define BIMODAL_SIZE 1024
#define BIMODAL_MAX_COUNTER 3
#define TAGPREDLOG 10
#define TAGPRED_CTR_BITS 3
#define STRONGLY_NOT_TAKEN 0
#define WEAKLY_NOT_TAKEN 1
#define WEAKLY_TAKEN 2
#define STRONGLY_TAKEN 3

struct Entry {
    int8_t counter; // 3-bit Counter for prediction (sign provides the prediction)
    uint32_t tag;
    uint8_t usefulbits; // 2-bit counter
};

struct bimodalTable {
    int8_t counter; // 2-bit counter
};

enum states {
    NOT_TAKEN,
    TAKEN
};

struct TAGEPredictor {
    struct bimodalTable bimodaltable[BIMODAL_SIZE];
    struct Entry tageTables[NUMBER_TABLES][BIMODAL_SIZE];
    uint32_t tag[NUMBER_TABLES];
    int32_t indexTagPred[NUMBER_TABLES];
    int32_t tagComp[2][NUMBER_TABLES];
    int32_t indexComp[NUMBER_TABLES];
    int32_t PHR;
    enum states primePred;
    enum states altPred;
    int32_t primeBank;
    int32_t altBank;
    struct Entry* tagPred[NUMBER_TABLES][BIMODAL_SIZE]; // Array of pointers to Entry structures
};

void initialization(struct TAGEPredictor* tage) {
    // Tage tables initialization
    for (int i = 0; i < NUMBER_TABLES; i++) {
        for (int j = 0; j < BIMODAL_SIZE; j++) {
            tage->tageTables[i][j].counter = 0;
            tage->tageTables[i][j].tag = 0;
            tage->tageTables[i][j].usefulbits = 0;
        }
    }

    // Bimodal table initialization
    for (int i = 0; i < BIMODAL_SIZE; i++) {
        tage->bimodaltable[i].counter = STRONGLY_TAKEN;
    }

    // Initialize the tagPred array
    for (int i = 0; i < NUMBER_TABLES; i++) {
        for (int j = 0; j < BIMODAL_SIZE; j++) {
            tage->tagPred[i][j] = &tage->tageTables[i][j];
        }
    }
}

bool GetBasePrediction(int8_t bimodalCounter) {
    bool basePrediction;

    if (bimodalCounter > BIMODAL_MAX_COUNTER / 2) {
        basePrediction = true;
    } else {
        basePrediction = false;
    }
    return basePrediction;
}

bool getPrediction(struct TAGEPredictor* predictor, uint32_t branchPC) {
    bool basePrediction;
    uint32_t index = (branchPC % BIMODAL_SIZE);
    int8_t bimodCounter = predictor->bimodaltable[index].counter;
    basePrediction = GetBasePrediction(bimodCounter);

    for (int i = 0; i < NUMBER_TABLES; i++) {
        predictor->tag[i] = branchPC ^ predictor->tagComp[0][i] ^ (predictor->tagComp[1][i] << 1);
        // Masking the tag
        predictor->tag[i] &= ((1 << ((i < 2) ? 9 : 8)) - 1);
    }

    int32_t index_mask = ((1 << TAGPREDLOG) - 1);
    for (int i = 0; i < NUMBER_TABLES; i++) {
        predictor->indexTagPred[i] = branchPC ^ (branchPC >> ((i < 2) ? TAGPREDLOG : (TAGPREDLOG - i + 1))) ^
                                     predictor->indexComp[i] ^ predictor->PHR ^ (predictor->PHR >> TAGPREDLOG);
        // Mask the index
        predictor->indexTagPred[i] &= index_mask;
    }
    predictor->primePred = NOT_TAKEN;
    predictor->altPred = NOT_TAKEN;
    predictor->primeBank = NUMBER_TABLES;
    predictor->altBank = NUMBER_TABLES;
   for (int iterator = 0; iterator < NUMBER_TABLES; iterator++) {
    if (predictor->tagPred[iterator][predictor->indexTagPred[iterator]]->tag == predictor->tag[iterator]) {
        predictor->primeBank = iterator;
        break;
    }
}

for (int iterator = predictor->primeBank + 1; iterator < NUMBER_TABLES; iterator++) {
    if (predictor->tagPred[iterator][predictor->indexTagPred[iterator]]->tag == predictor->tag[iterator]) {
        predictor->altBank = iterator;
        break;
    }
}

if (predictor->primeBank < NUMBER_TABLES) {
    if (predictor->altBank == NUMBER_TABLES) {
        predictor->altPred = basePrediction;
    } else {
        if (predictor->tagPred[predictor->altBank][predictor->indexTagPred[predictor->altBank]]->counter >= (1 << (TAGPRED_CTR_BITS - 1)))
            predictor->altPred = true; // TAKEN
        else
            predictor->altPred = false; // NOT_TAKEN
    }
    if ((predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]]->counter != 3) ||
        (predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]]->counter != 4) ||
        (predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]]->usefulbits != 0)) {
        if (predictor->tagPred[predictor->primeBank][predictor->indexTagPred[predictor->primeBank]]->counter >= (1 << (TAGPRED_CTR_BITS - 1)))
            predictor->primePred = true; // TAKEN
        else
            predictor->primePred = false; // NOT_TAKEN
        return predictor->primePred;
    } else {
        return predictor->altPred;
    }
} else {
    predictor->altPred = basePrediction;
    return predictor->altPred;
}
}

int main(int argc, char* argv[]) {
    struct TAGEPredictor predictor;
    uint32_t PC = 0x12345678;

    // Initialize the predictor
    initialization(&predictor);

    bool prediction = getPrediction(&predictor, PC);
    if (prediction) {
        printf("Predicted: Taken\n");
    } else {
        printf("Predicted: Not Taken\n");
    }

    return 0;
}
