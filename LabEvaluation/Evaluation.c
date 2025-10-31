//Write a C program that creates 4 threads. Each thread should:
// 1.  Receive a unique number N as an argument (use values: 10, 20, 30, 40)
//2.  Calculate the sum of numbers from 1 to N
//3.  Print the thread number and calculated sum
//4.  Return the sum through thread's return value
//Main thread should:
  //Create all 4 threads and pass arguments Wait for all threads to complete
 //Collect all return values
 //Calculate and print the total of all sums
// Shanza Batool
// 23-NTU-CS-1209

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* calculate_sum(void* arg) {
    int N = *(int*)arg; 
    int* sum = malloc(sizeof(int)); 
    *sum = 0;

    for (int i = 1; i <= N; i++) {
        *sum += i;
    }

   
    pthread_t tid = pthread_self();
    printf("Thread for N=%d (ID:%lu) calculated sum = %d\n", N, tid, *sum);

    pthread_exit(sum); 
}

int main() {
    pthread_t threads[4]; 
    int numbers[4] = {10, 20, 30, 40}; 
    int total_sum = 0;

   
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, calculate_sum, &numbers[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

   
    for (int i = 0; i < 4; i++) {
        int* thread_sum;
        pthread_join(threads[i], (void**)&thread_sum);
        total_sum += *thread_sum;
        free(thread_sum); 
    }

    printf("\nTotal of all thread sums = %d\n", total_sum);
    printf("Main thread: Work completed.\n");

    return 0;
}
