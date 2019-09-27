#include <pthread.h>
#include<iostream>
#include <unistd.h>     //sleep function
#include"Vector.hpp"
using namespace std;

Vector shared;

void* writer(void* data){

    int * id = static_cast<int*>(data);

    while(1){
        if(shared.setAndTest(*id)==false){
            cout << "error in thread " << *id << endl;
        }
       usleep(250);
    }
    return nullptr;
}

int main(){

    int noOfThreads = 20;
    pthread_t thr[noOfThreads];     //create array of threads
    int thr_id[noOfThreads];
	int status;

    for(int i=0; i<noOfThreads; i++){
         thr_id[i] = i;
    }

    //create threads
     for(int i=0; i<noOfThreads; i++){
         status = pthread_create(&thr[i], NULL, &writer, &thr_id[i]);
		 if (status != 0){
			printf("Error creating thread\n");
		}
    }

    //join threads
    for(int i=0; i<noOfThreads; i++){
        status = pthread_join(thr[i], nullptr);
		if (status != 0){
			printf("Error joining thread\n");
		}
    }

    pthread_exit(NULL);

    return 0;
}
