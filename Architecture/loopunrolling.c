// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>
// #include <ctype.h>

// bool keywords(char buffer[]) {
//     bool flag = false;
//     char keywords[32][10] = {
//         "auto", "break", "case", "char", "const", "continue", "default",
//         "do", "double", "else", "enum", "extern", "float", "for", "goto",
//         "if", "int", "long", "register", "return", "short", "signed",
//         "sizeof", "static", "struct", "switch", "typedef", "union",
//         "unsigned", "void", "volatile", "while"
//     };
//     for (int i = 0; i < 32; ++i) {
//         if (strcmp(keywords[i], buffer) == 0) {
//             flag = true;
//             break;
//         }
//     }
//     return flag;
// }

// int main(int argc, char* argv[]) {
//     char operator[] = " -+/%/=,;()";
//     int j = 0;
//     char ch;
//     FILE* fp;
//     char buffer[15];

//     fp = fopen("input.txt", "r");
//     if (fp == NULL) {
//         perror("Error opening file");
//         exit(0);
//     }

//     while ((ch = fgetc(fp)) != EOF) {
//         for (int i = 0; i < 10; i++) {
//             if (ch == operator[i] && keywords(buffer) == false) {
//                 printf("id ");
//             }
//         }

//         for (int i = 0; i < 10; ++i) {
//             if (ch == operator[i]) {
//                 if (operator[i] == '+')
//                     printf("ADD ");
//                 else if (operator[i] == '-')
//                     printf("SUB ");
//                 else if (operator[i] == '*')
//                     printf("MUL ");
//                 else if (operator[i] == '/')
//                     printf("DIV ");
//                 else if (operator[i] == '%')
//                     printf("MOD ");
//                 else if (operator[i] == '=')
//                     printf("op-equ ");
//                 else if (operator[i] == ';')
//                     printf(";\n");
//                 else if (operator[i] == ',')
//                     printf(", ");
//                 else if (operator[i] == '(')
//                     printf("(\n");
//                 else if (operator[i] == ')')
//                     printf(")\n");
//             }
//         }

//         if (isalnum(ch) || ch == '_') {
//             buffer[j++] = ch;
//         } else if ((ch == ' ' || ch == '\n' || ch == '\t') && (j != 0)) {
//             buffer[j] = '\0';
//             j = 0;

//             if (keywords(buffer)) {
//                 printf("Keyword\n");
//             }
//         }
//     }

//     fclose(fp);
//     return 0;
// }
#include <stdio.h>
#include <string.h>

int main() {
    // Open the input and output files
    FILE *inputFile = fopen("/home/dmacs-5/Documents/mtech_2023/Architecture/input.txt", "r");
    FILE *outputFile = fopen("/home/dmacs-5/Documents/mtech_2023/Architecture/output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // Loop unrolling count
    int unrollFactor = 4;

    char line[256];
    char label[256];

    while (fgets(line, sizeof(line), inputFile)) {
        // Look for loop labels
        if (strstr(line, "Loop:") != NULL) {
            strcpy(label, "Loop");
        } else if (strstr(line, "LOOP:") != NULL) {
            strcpy(label, "LOOP");
        } else {
            // Output non-loop lines as-is
            fputs(line, outputFile);
            continue;
        }

        // Generate unrolled loop code
        for (int i = 0; i < unrollFactor; i++) {
            fprintf(outputFile, "%s%d:\n", label, i);
            while (fgets(line, sizeof(line), inputFile)) {
                // Skip comments and labels
                if (line[0] == ';' || line[0] == '.') {
                    continue;
                }
                if (strstr(line, label) != NULL) {
                    break;
                }
                // Modify loop-specific instructions
                if (strstr(line, "DADDUI R1, R1, #-8") != NULL) {
                    if (i == unrollFactor - 1) {
                        fprintf(outputFile, "DADDUI R1, R1, #-32\n");
                    } else {
                        fprintf(outputFile, "DADDUI R1, R1, #-8\n");
                    }
                } else if (strstr(line, "BNE R1, R2,") != NULL) {
                    if (i == unrollFactor - 1) {
                        fprintf(outputFile, "BNE R1, R2, %s0\n", label);
                    } else {
                        fprintf(outputFile, "BNE R1, R2, %s%d\n", label, i + 1);
                    }
                } else {
                    fputs(line, outputFile);
                }
            }
        }
    }

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
