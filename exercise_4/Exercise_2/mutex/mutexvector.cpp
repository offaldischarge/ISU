#include "Vector.hpp"
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

static Vector v;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *writer(void *arg){
    int *id = (int *) arg;
    int stat;

    while(true){
        //Critical section
        stat = pthread_mutex_lock(&mtx);
        if(stat != 0){
            printf("Error locking mutex");
        }

        if(v.setAndTest(*id) == false){
            cout << "Set and test failed for thread ID: " << *id << endl;
        } else {
            cout << "Set and test completed for thread ID: " << *id <<  endl;
        }

        stat = pthread_mutex_unlock(&mtx);
        if(stat != 0){
            printf("Error locking mutex");
        }

        sleep(1);
    }
}


int main(){
    int arraySize = 100;
    int thread_no[arraySize];
    pthread_t threads[arraySize];

    int status = 0;

    //Create array of numbers 0 to 99
    for(int i = 0; i < arraySize; i++){
        thread_no[i] = i;
    }

    //Create threads with their own unique ID, and ID number passed as arg
    for(int i = 0; i < arraySize; i++){
        status = pthread_create(&threads[i], NULL, writer, &thread_no[i]);
        if (status != 0){
            cout << "Error creating thread " << i << endl;
        }
    }

    //Join all threads
    for(int i = 0; i < arraySize; i++){
        status = pthread_join(threads[i], NULL);
        if (status != 0){
            cout << "Error joining thread " << i << endl;
        }
    }

    printf("Main: exiting\n");

    pthread_exit(NULL);

    return 0;
}
