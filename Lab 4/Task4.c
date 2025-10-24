 #include <stdio.h>
 #include <pthread.h>
#include <unistd.h>
 void* worker_thread(void* arg) {
 int thread_num = *(int*)arg;
 printf("Thread %d: Starting work...\n", thread_num);
 sleep(1); // Simulate some work
 printf("Thread %d: Work completed!\n", thread_num);
 return NULL;
 }
 int main() {
 pthread_t threads[5];
 int thread_args[5];
 // Create 5 threads
 for (int i = 0; i < 5; i++) {
 thread_args[i] = i + 1;
 printf("Main: Creating thread %d\n", i + 1);
 pthread_create(&threads[i], NULL, worker_thread, &thread_args[i]);
 }
 // Wait for all threads to complete
 for (int i = 0; i < 5; i++) {
 pthread_join(threads[i], NULL);
 printf("Main: Thread %d has finished\n", i + 1);
 }
 printf("All threads completed!\n");
 return 0;
 }