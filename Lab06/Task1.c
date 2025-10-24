#include <stdio.h>
#include <pthread.h>
#include <unistd.h>   // for getpid()

#define NUM_THREADS 4

int varg = 0;                  // global shared variable
pthread_mutex_t lock;          // declare mutex

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    int varl = 0;              // local variable (private to each thread)

    // Lock before modifying global variable
    pthread_mutex_lock(&lock);
    varg++;
    pthread_mutex_unlock(&lock);

    varl++;
    printf("Thread %d is executing. Global value = %d | Local value = %d | Process ID = %d\n",
           thread_id, varg, varl, getpid());

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    // Wait for all threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex after use
    pthread_mutex_destroy(&lock);

    printf("Main is executing. Final global value = %d | Process ID = %d\n", varg, getpid());

    return 0;
}