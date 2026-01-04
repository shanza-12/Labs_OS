#include <stdio.h>
#include <pthread.h>

// Thread function to compute factorial
void* factorial(void* arg) {
    int n = (int)arg;
    unsigned long long result = 1;

    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    // Print result directly (no need to return value)
    printf("Factorial of %d = %llu\n", n, result);
    return NULL;
}

int main() {
    pthread_t thread;
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return 0;
    }

    // Create thread
    pthread_create(&thread, NULL, factorial, &num);

    // Wait for thread to finish
    pthread_join(thread, NULL);

    printf("Main thread: Work completed.\n");
    return 0;
}