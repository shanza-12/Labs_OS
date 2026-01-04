#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_CAPACITY 5
#define ITEMS_TO_PRODUCE 3

int sharedBuffer[BUFFER_CAPACITY];
int writeIndex = 0;
int readIndex = 0;

sem_t spacesAvailable;
sem_t itemsAvailable;
pthread_mutex_t bufferMutex;

// Producer function
void* produceItems(void* arg) {
    int producerId = (int)arg;

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        sem_wait(&spacesAvailable);      // Wait for empty slot
        pthread_mutex_lock(&bufferMutex); // Lock buffer

        sharedBuffer[writeIndex] = producerId * 10 + i;
        printf("Producer-%d produced %d\n", producerId, sharedBuffer[writeIndex]);
        writeIndex = (writeIndex + 1) % BUFFER_CAPACITY;

        pthread_mutex_unlock(&bufferMutex); // Unlock buffer
        sem_post(&itemsAvailable);          // Signal item is available

        sleep(1); // Simulate production
    }

    return NULL;
}

// Consumer function
void* consumeItems(void* arg) {
    int consumerId = (int)arg;

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        sem_wait(&itemsAvailable);        // Wait for item
        pthread_mutex_lock(&bufferMutex); // Lock buffer

        printf("Consumer-%d consumed %d\n", consumerId, sharedBuffer[readIndex]);
        readIndex = (readIndex + 1) % BUFFER_CAPACITY;

        pthread_mutex_unlock(&bufferMutex); // Unlock buffer
        sem_post(&spacesAvailable);         // Signal space is available

        sleep(2); // Simulate consumption
    }

    return NULL;
}

int main() {
    pthread_t producers[2], consumers[2];
    int ids[2] = {101, 102};

    // Initialize semaphores and mutex
    sem_init(&spacesAvailable, 0, BUFFER_CAPACITY);
    sem_init(&itemsAvailable, 0, 0);
    pthread_mutex_init(&bufferMutex, NULL);

    // Start producer and consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, produceItems, &ids[i]);
        pthread_create(&consumers[i], NULL, consumeItems, &ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    // Clean up
    sem_destroy(&spacesAvailable);
    sem_destroy(&itemsAvailable);
    pthread_mutex_destroy(&bufferMutex);

    return 0;
}