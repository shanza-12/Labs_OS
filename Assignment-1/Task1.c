// Shanza Batool
// 23-NTU-CS-1209
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

//Function executed by each thread
void* thread_func(void* arg){
   int thread_num = *(int*)arg;  //  get the integer value
  //Get thread number(1-5)
    pthread_t tid = pthread_self(); //Get thread id
    printf("Thread %d started.Thread ID: %lu\n",thread_num,tid);

    //Sleep for a random time between 1-3 seconds
    int sleep_time = rand() % 3 + 1;
    sleep(sleep_time);

    printf("Thread %d (ID:%lu) completed after %d seconds.\n",thread_num,tid,sleep_time);
    pthread_exit(NULL);
}
int main(){
    pthread_t threads[5];
    int thread_nums[5];
    srand(time(NULL));   //Random number generator

    //Create 5 threads
    for(int i=0;i < 5;i++){
        thread_nums[i] = i + 1;
        if(pthread_create(&threads[i],NULL,thread_func,&thread_nums[i])!= 0){
            perror("Failed to create thread");
            return 1;
        }
    }
    for(int i=0;i < 5; i++){
        pthread_join(threads[i], NULL);
    }
    printf("\nAll threads have completed execution.\n");
    return 0;
}