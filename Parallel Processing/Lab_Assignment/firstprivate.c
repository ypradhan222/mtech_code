#include <stdio.h>
#include <omp.h>

int main() {
    const int N = 10;
    int arr[N];
    int sum = 0;
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    int initial_value = 100;  
    #pragma omp parallel for firstprivate(initial_value) reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i] + initial_value;  
    }
    printf("Sum with initial value: %d\n", sum);
    return 0;
}
