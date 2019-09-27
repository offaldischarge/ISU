#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void *threadHello(void *arg){
    int *s = (int *) arg;
    for(int i = 0; i < 10; i++){
        printf("Hello #%i from thread %i\n", i, *s);
        sleep(1);
    }
    printf("Thread %i terminates\n", *s);
    return arg;
}

int main(void){
    pthread_t h1, h2;
    int status;

    int thread_no[] = {0, 1}; //Pass a pointer to pthread_create

    printf("Creating threads\n");

    status = pthread_create(&h1, NULL, threadHello, &thread_no[0]);
    if (status != 0){
        printf("Error creating thread 0\n");
    }

    status = pthread_create(&h2, NULL, threadHello, &thread_no[1]);
    if (status != 0){
        printf("Error creating thread 1\n");
    }

    printf("Waiting for threads to finish\n");

    status = pthread_join(h1, NULL);
    if (status != 0){
        printf("Error joining thread 0\n");
    }

    status = pthread_join(h2, NULL);
    if (status != 0){
        printf("Error joining thread 1\n");
    }

    printf("Main: exiting\n");

    pthread_exit(NULL);

    return 0;
}
