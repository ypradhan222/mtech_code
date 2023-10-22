#include <stdio.h>

int main() {
    int num1 = 5;
    int num2 = 2;
    int result = 0;
    int counter = 0;
    int loop_count = 10;

    while (counter < loop_count) {
        // Loop unrolling: Perform two iterations in each loop
        for (int i = 0; i < 2; i++) {
            result += num2;
            num2 -= num1;
            result += num2;
            num2 -= num1;
        }

        // Shift register values (swap num1 and num2)
        int temp = num1;
        num1 = num2;
        num2 = temp;

        counter += 2;  // Update the counter for two iterations
    }

    printf("Final result: %d\n", result);
    return 0;
}
