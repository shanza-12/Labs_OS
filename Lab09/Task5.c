#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;    // Binary semaphore
int counter = 1;

// Thread function to increment counter
void* increment_thread(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 5; i++) {
        printf("Increment Thread %d: Waiting...\n", id);
        sem_wait(&mutex); // Acquire
        // Critical Section
        counter++;
        printf("Increment Thread %d: Counter = %d\n", id, counter);
        sleep(1);
        sem_post(&mutex); // Release
        sleep(1);
    }
    return NULL;
}
// Thread function to decrement counter
void* decrement_thread(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        printf("Decrement Thread %d: Waiting...\n", id);
        sem_wait(&mutex); // Acquire
        // Critical Section
        counter--;
        printf("Decrement Thread %d: Counter = %d\n", id, counter);
        sleep(1);
        sem_post(&mutex); // Release
        sleep(1);
    }
    return NULL;
}
int main() {
    sem_init(&mutex, 0, 1);  // Binary semaphore initialized to 1

    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    // Create increment and decrement threads
    pthread_create(&t1, NULL, increment_thread, &id1);
    pthread_create(&t2, NULL, decrement_thread, &id2);
    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Final Counter Value: %d\n", counter);
    sem_destroy(&mutex);
    return 0;
}
