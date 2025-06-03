#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define global variables
int balance = 10000;
pthread_mutex_t mutex1;
int total_deposits = 0;
int total_withdrawn = 0;

void *deposit(void *arg) {
    int thread_num = *((int*)arg);

    while (1) {
        pthread_mutex_lock(&mutex1);

        if (total_deposits >= 600 || total_withdrawn >= 40000) {
            pthread_mutex_unlock(&mutex1);
            break;
        }

        balance += 50;
        total_deposits++;

        printf("Thread %d: Deposit. Depositable amount: $%d. Current Balance: $%d.\n", thread_num, 30000 - (total_deposits * 50), balance);

        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(NULL);
}

void *withdraw(void *arg) {
    int thread_num = *((int*)arg);

    while (1) {
        pthread_mutex_lock(&mutex1);

        if (balance >= 50 && total_withdrawn < 40000) {
            balance -= 50;
            total_withdrawn += 50;

            printf("Thread %d: Withdrawal. Amount Withdrawn: $%d. Current Balance: $%d\n", thread_num, total_withdrawn, balance);

            pthread_mutex_unlock(&mutex1);
        } else {
            pthread_mutex_unlock(&mutex1);
            break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_mutex_init(&mutex1, NULL);

    pthread_t deposit_threads[2];
    pthread_t withdraw_threads[2];
    int deposit_thread_nums[2] = {1, 2};
    int withdraw_thread_nums[2] = {3, 4};

    for (int i = 0; i < 2; i++) {
        pthread_create(&deposit_threads[i], NULL, deposit, (void*)(&deposit_thread_nums[i]));
    }

    for (int i = 0; i < 2; i++) {
        pthread_create(&withdraw_threads[i], NULL, withdraw, (void*)(&withdraw_thread_nums[i]));
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(deposit_threads[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(withdraw_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex1);

    printf("Final Balance: $%d\n", balance);




    return 0;
}
