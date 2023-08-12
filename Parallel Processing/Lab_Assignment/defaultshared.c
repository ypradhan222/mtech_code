#include <stdio.h>
#include <omp.h>

int main() {
    const int N = 1000000;
    int arr[N];
    int sum = 0;

    // Initialize the array
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }

    #pragma omp parallel for default(shared) reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }

    printf("Sum: %d\n", sum);

    return 0;
}
