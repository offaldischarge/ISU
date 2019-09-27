#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static unsigned int shared = 0;

static void *inc(void *arg){
    for(int i = 0; i < 10; i++){
        shared++;
        sleep(1);
    }
}

static void *rd(void *arg){
    for(int i = 0; i < 10; i++){
        printf("Shared value: %u\n", shared);
        sleep(1);
    }
}

int main(void){
    pthread_t incrementer, reader;
    int status;

    printf("Creating threads\n");

    status = pthread_create(&incrementer, NULL, inc, NULL);
    if (status != 0){
        printf("Error creating thread 0\n");
    }

    status = pthread_create(&reader, NULL, rd, NULL);
    if (status != 0){
        printf("Error creating thread 1\n");
    }

    status = pthread_join(incrementer, NULL);
    if (status != 0){
        printf("Error joining thread 0\n");
    }

    status = pthread_join(reader, NULL);
    if (status != 0){
        printf("Error joining thread 1\n");
    }

    printf("Main: exiting\n");

    return 0;
}
