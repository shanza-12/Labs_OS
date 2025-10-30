//Shanza Batool
//23-NTU-CS-1209
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function executed by each thread
void* calculate(void* arg) {
    int num = *(int*)arg;   // ✅ Dereference pointer instead of casting
    printf("Thread: Number = %d\n", num);
    printf("Thread: Square = %d\n", num * num);
    printf("Thread: Cube = %d\n", num * num * num);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int num;

    // Take input from user
    printf("Enter a number: ");
    scanf("%d", &num);

    // ✅ Pass address of num correctly
    if (pthread_create(&thread, NULL, calculate, &num) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Main thread waits for the created thread to finish
    pthread_join(thread, NULL);

    printf("Main thread: Work completed.\n");
    return 0;
}
