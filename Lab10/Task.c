#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;  // Producer index
int out = 0; // Consumer index

sem_t empty; // Counts empty slots
sem_t full;  // Counts full slots
pthread_mutex_t mutex;

void* producer(void* arg) {
    int id = *((int*)arg);  // Safe way to get int from pointer

    for (int i = 0; i < 3; i++) { // Each producer makes 3 items
        int item = id * 100 + i;

        // Wait for empty slot
        sem_wait(&empty);

        // Lock the buffer
        pthread_mutex_lock(&mutex);

        // Add item to buffer
        buffer[in] = item;
        printf("Producer %d produced item %d at position %d\n", id, item, in);

        in = (in + 1) % BUFFER_SIZE;

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);

        // Signal that buffer has a full slot
        sem_post(&full);

        sleep(1); // Simulate production time
    }

    return NULL;
}

void* consumer(void* arg) {
    int id = *((int*)arg);  // Safe way to get int from pointer

    for (int i = 0; i < 3; i++) { // Each consumer consumes 3 items
        // Wait for full slot
        sem_wait(&full);

        // Lock the buffer
        pthread_mutex_lock(&mutex);

        // Consume item from buffer
        int item = buffer[out];
        printf("Consumer %d consumed item %d from position %d\n", id, item, out);

        out = (out + 1) % BUFFER_SIZE;

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);

        // Signal that buffer has an empty slot
        sem_post(&empty);

        sleep(2); // Consumers are slower
    }

    return NULL;
}

int main() {
    pthread_t prod[2], cons[2];
    int ids[2] = {1, 2};

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // All slots empty initially
    sem_init(&full, 0, 0);            // No slots full initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&prod[i], NULL, producer, &ids[i]);
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
 
// Here we have two producer threads and two consumer threads 
// Each producer is making 3 slots of items and we have 2 
//producer so we have total 6 slots of items that is producing 
//the producer 
//then we decrement by sem_wait(&empty) and showing that one 
//slot is taken form the buffer 
 
//then we will secure the critical section by mutex lock and 
//unlock 
//sem_post(&full) Signal that buffer has a full slot 
 
// Each consumer is consuming 3 slots of items and we have 2 
//consumers so we have total 6 slots of items that is consuming 
//the consumer 
//then we decrement by sem_wait(&full) and showing that one 
//item is taken from the buffer 
//then we will secure the critical section by mutex lock and 
//unlock 
//sem_post(&empty) Signal that buffer has a empty slot