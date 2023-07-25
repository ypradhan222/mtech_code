#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>

bool isPalindrome(int number) {
    // Convert the number to a string for easy digit access
    char strNum[20]; // Assuming the number has at most 20 digits
    sprintf(strNum, "%d", number);

    int len = strlen(strNum);
    int i;
    bool result = true; // Initialize result to true for each thread

    // Compare the digits from the outermost to the center using parallel for
    #pragma omp parallel for private(i) schedule(static) reduction(&&:result)
    for (i = 0; i < len / 2; i++) {
        int j = len - 1 - i; 
        if (strNum[i] != strNum[j]) {
            result = false; 
        }
    }

    return result; 
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (isPalindrome(num)) {
        printf("%d is a palindrome.\n", num);
    } else {
        printf("%d is not a palindrome.\n", num);
    }

    return 0;
}
