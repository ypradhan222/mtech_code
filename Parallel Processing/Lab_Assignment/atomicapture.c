#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;
    int account_balance = 1000;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int withdraw_amount = (thread_id + 1) * 100;

        int remaining_balance;
        #pragma omp atomic capture
        remaining_balance = (account_balance -= withdraw_amount);

        printf("Thread %d withdrew $%d. Remaining balance: $%d\n", thread_id, withdraw_amount, remaining_balance);
    }

    printf("Final account balance: $%d\n", account_balance);

    return 0;
}
