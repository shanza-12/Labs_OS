#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function that each thread will run
void* thread_func(void* arg) {
    int thread_num = (int)arg;  // Get thread number
    printf("Thread %d started.\n", thread_num);

    // Sleep for random time (1–3 seconds)
    int sleep_time = rand() % 3 + 1;
    sleep(sleep_time);

    printf("Thread %d finished after %d seconds.\n", thread_num, sleep_time);
    pthread_exit(NULL);  // End thread
}

int main() {
    pthread_t threads[2];  // Two threads
    int thread_nums[2] = {1, 2};  // Thread numbers

    srand(time(NULL));  // Random number seed

    // Create 2 threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_func, &thread_nums[i]);
    }

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nBoth threads have completed.\n");
    return 0;
}