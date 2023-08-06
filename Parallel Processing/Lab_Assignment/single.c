#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int a[N], b[N];
    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
        b[i] = 2 * i + 1;
    }

    int dot_product = 0;
    int max_dot_product = 0;

    #pragma omp parallel private(dot_product) shared(max_dot_product)
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            dot_product += a[i] * b[i];
        }

        #pragma omp single copyprivate(max_dot_product)
        {
            if (dot_product > max_dot_product) {
                max_dot_product = dot_product;
            }
        }
    }

    printf("Max Dot Product: %d\n", max_dot_product);

    return 0;
}
#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int a[N], b[N];
    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
        b[i] = 2 * i + 1;
    }

    int dot_product = 0;
    int max_dot_product = 0;

    #pragma omp parallel private(dot_product) shared(max_dot_product)
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            dot_product += a[i] * b[i];
        }

        #pragma omp single copyprivate(max_dot_product)
        {
            if (dot_product > max_dot_product) {
                max_dot_product = dot_product;
            }
        }
    }

    printf("Max Dot Product: %d\n", max_dot_product);

    return 0;
}
