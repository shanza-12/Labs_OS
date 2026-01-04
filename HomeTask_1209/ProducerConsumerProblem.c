#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 3

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;   // counts empty slots
sem_t full;    // counts filled slots
pthread_mutex_t mutex;

// Producer function
void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        sem_wait(&empty);          // wait for empty space
        pthread_mutex_lock(&mutex);

        buffer[in] = id * 10 + i;
        printf("Producer %d produced %d\n", id, buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);           // signal item available

        sleep(1);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        sem_wait(&full);           // wait for item
        pthread_mutex_lock(&mutex);

        printf("Consumer %d consumed %d\n", id, buffer[out]);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);          // signal space available

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p1, c1;
    int id = 1;

    // Initialize
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&p1, NULL, producer, &id);
    pthread_create(&c1, NULL, consumer, &id);

    // Wait
    pthread_join(p1, NULL);
    pthread_join(c1, NULL);

    // Destroy
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
