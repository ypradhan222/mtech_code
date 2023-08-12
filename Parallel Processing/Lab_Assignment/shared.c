#include <stdio.h>
#include <omp.h>

int main() {
    const int N = 10;
    int arr[N];
    int sum = 0;
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    #pragma omp parallel shared(arr, sum)
    {
        int local_sum = 0; // Private variable for each thread
        #pragma omp for
        for (int i = 0; i < N; i++) {
            local_sum += arr[i];
        }
        #pragma omp critical
        {
            sum += local_sum;
        }
    }
    printf("Sum: %d\n", sum);
    return 0;
}
