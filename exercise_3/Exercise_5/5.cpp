#include "Vector.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

static Vector v;

static void *writer(void *arg){
    int *id = (int *) arg;

    while(true){
        if(v.setAndTest(*id) == false){
            cout << "Set and test failed for thread ID: " << *id << endl;
        }
        usleep(250);
    }
}


int main(){
    int arraySize = 20;
    int thread_no[arraySize];
    pthread_t threads[arraySize];

    int status = 0;

    for(int i = 0; i < arraySize; i++){
        thread_no[i] = i;
    }

    for(int i = 0; i < arraySize; i++){
        status = pthread_create(&threads[i], NULL, writer, &thread_no[i]);
        if (status != 0){
            cout << "Error creating thread " << i << endl;
        }
    }

    for(int i = 0; i < arraySize; i++){
        status = pthread_join(threads[i], NULL);
        if (status != 0){
            cout << "Error joining thread " << i << endl;
        }
    }

    printf("Main: exiting\n");

    return 0;
}
