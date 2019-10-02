#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

static pthread_mutex_t mutEntry = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutExit = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t guardEntry = PTHREAD_COND_INITIALIZER;
static pthread_cond_t guardExit = PTHREAD_COND_INITIALIZER;

static bool carWaitingToEnter,carWaitingToExit;
static bool parkEntryOpen, parkExitOpen;

/* Car thread */
static void* carThread(void* arg){
    int stat = 0; //error integer
    int *id = (int *) arg;

    while(true){

        cout << "Car " << *id << " waiting outside PL" << endl;

        /* Entry */
        //driveUpToEntry();
        stat = pthread_mutex_lock(&mutEntry);
        if(stat != 0){
            cout << "Error locking mutex" << endl;
        }

        carWaitingToEnter = true;

        stat = pthread_cond_broadcast(&guardEntry);
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        while(!parkEntryOpen){
            stat = pthread_cond_wait(&guardEntry, &mutEntry);
            if(stat != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        //driveCarInPLCS();
        cout << "Car " << *id << " has entered PL" << endl;

        carWaitingToEnter = false;

        stat = pthread_cond_broadcast(&guardEntry);
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        pthread_mutex_unlock(&mutEntry);

        /* Car entered PLCS */

        sleep(2); // wait a bit inside PL

        cout << "Car " << *id << " driving up to exit" << endl;

        /* Exit */
        //driveUpToExit();

        pthread_mutex_lock(&mutExit);

        carWaitingToExit = true;
        stat = pthread_cond_broadcast(&guardExit);
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        while(!parkExitOpen){
            stat = pthread_cond_wait(&guardExit, &mutExit);
            if(stat != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        //driveOutOfPLCS();
        cout << "Car " << *id << " has exited PL" << endl;
        carWaitingToExit = false;

        stat = pthread_cond_broadcast(&guardExit);
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        stat = pthread_mutex_unlock(&mutExit);
        if(stat != 0){
            cout << "Error locking mutex" << endl;
        }

        /* Car guardExited PLCS */

        sleep(1); //wait a bit outside parking lot
    }

    return arg;
}

/* Entry guard thread */

static void* entryGuardThread(void* arg){
    int stat = 0;

    while(true){
        stat = pthread_mutex_lock(&mutEntry);
        if(stat != 0){
            cout << "Error locking mutex" << endl;
        }

        while(!carWaitingToEnter){
            stat = pthread_cond_wait(&guardEntry, &mutEntry);
            if(stat != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        //openEntryDoor();
        parkEntryOpen = true;
        stat = pthread_cond_signal(&guardEntry);

        while(carWaitingToEnter){
            stat = pthread_cond_wait(&guardEntry, &mutEntry);
        }

        //closeEntryDoor();
        parkEntryOpen = false;

        stat = pthread_mutex_unlock(&mutEntry);
        if(stat != 0){
            cout << "Error unlocking mutex" << endl;
        }
    }

    return arg;
}

/* Exit guard thread */

static void* exitGuardThread(void* arg){
    int stat = 0;

    while(true){

        stat = pthread_mutex_lock(&mutExit);
        if(stat != 0){
            cout << "Error locking mutex" << endl;
        }

        while(!carWaitingToExit){
            stat = pthread_cond_wait(&guardExit, &mutExit);
        }

        //openExitDoor();
        parkExitOpen = true;
        stat = pthread_cond_signal(&guardExit);
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        while(carWaitingToExit){
            stat = pthread_cond_wait(&guardExit, &mutExit);
            if(stat != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        //closeExitDoor();
        parkExitOpen = false;

        stat = pthread_mutex_unlock(&mutExit);
    }

    return arg;
}

int main(){
    int arraySize = 3;

    int carID[arraySize];
    pthread_t cars[arraySize], entry_gates[arraySize], exit_gates[arraySize];

    for(int i = 0; i < arraySize; i++){
        carID[i] = i;
    }

    int status;

    /* Creating threads */
    for(int i = 0; i < arraySize; i++){
        status = pthread_create(&cars[i], NULL, carThread, &carID[i]);
        if (status != 0){
            cout << "Error creating car thread" << endl;
        }

        status = pthread_create(&entry_gates[i], NULL, entryGuardThread, NULL);
        if (status != 0){
            cout << "Error creating guardEntry gate thread" << endl;
        }

        status = pthread_create(&exit_gates[i], NULL, exitGuardThread, NULL);
        if (status != 0){
            cout << "Error creating guardExit gate thread" << endl;
        }
    }

    /* Joining threads */
    for(int i = 0; i < arraySize; i++){
        status = pthread_join(cars[i], NULL);
        if (status != 0){
            cout << "Error joining car thread" << endl;
        }

        status = pthread_join(entry_gates[i], NULL);
        if (status != 0){
            cout << "Error joining guardEntry gate thread" << endl;
        }

        status = pthread_join(exit_gates[i], NULL);
        if (status != 0){
            cout << "Error joining guardExit gate thread" << endl;
        }
    }

    pthread_exit(NULL);
}
