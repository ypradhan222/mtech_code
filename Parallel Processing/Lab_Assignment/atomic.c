#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;
    int account_balance = 1000;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int deposit_amount = thread_id * 100;

        #pragma omp atomic
        account_balance += deposit_amount;

        printf("Thread %d deposited $%d. New balance: $%d\n", thread_id, deposit_amount, account_balance);
    }

    printf("Final account balance: $%d\n", account_balance);

    return 0;
}
