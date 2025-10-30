//Shanza Batool
//23-NTU-CS-1209
#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Thread function to print personalized greeting
void* greet(void* arg) {
    char* name = (char*)arg; // Convert void* argument back to char*
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    return NULL; // Thread must return NULL
}

int main() {
    pthread_t thread;
    char name[50];

    // Get user's name
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    // Remove newline character if present
    name[strcspn(name, "\n")] = '\0';

    // Create thread
    if (pthread_create(&thread, NULL, greet, (void*)name) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Main thread message before joining
    printf("Main thread: Waiting for greeting...\n");

    // Wait for greeting thread to finish
    pthread_join(thread, NULL);

    printf("Main thread: Greeting completed.\n");
    return 0;
}
