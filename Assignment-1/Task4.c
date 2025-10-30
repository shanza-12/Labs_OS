// Shanza Batool
// 23-NTU-CS-1209

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function to compute factorial
void* factorial(void* arg) {
    int n = *(int*)arg;   //dereference the pointer
    unsigned long long* result = malloc(sizeof(unsigned long long)); // allocate memory for result

    if (result == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    *result = 1;

    for (int i = 1; i <= n; i++) {
        *result *= i;
    }

    pthread_exit(result);  // Return result pointer
}

int main() {
    pthread_t thread;
    int num;
    unsigned long long* fact_result;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return 1;
    }

    // Create thread and pass the number
    if (pthread_create(&thread, NULL, factorial, &num) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish and receive result
    pthread_join(thread, (void**)&fact_result);

    printf("Factorial of %d = %llu\n", num, *fact_result);

    // Free the allocated memory
    free(fact_result);

    printf("Main thread: Work completed.\n");
    return 0;
}
