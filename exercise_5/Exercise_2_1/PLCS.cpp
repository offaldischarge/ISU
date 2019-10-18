#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

static pthread_mutex_t mutEntry = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutExit = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t guardEntry = PTHREAD_COND_INITIALIZER;
static pthread_cond_t guardExit = PTHREAD_COND_INITIALIZER;

bool carWaitingToEnter,carWaitingToExit;
bool parkEntryOpen, parkExitOpen;

/* Car thread */
static void* carThread(void* arg){
    int stat = 0; //error integer

    while(true){

        /* Entry */
        //driveUpToEntry();
        stat = pthread_mutex_lock(&mutEntry);
        if(stat != 0){
            cout << "Error locking mutex" << endl;
        }

        cout << "Car waiting outside PL" << endl;

        carWaitingToEnter = true;

        stat = pthread_cond_signal(&guardEntry);
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
        cout << "Car has entered PL" << endl;

        carWaitingToEnter = false;

        stat = pthread_cond_signal(&guardEntry);
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        stat = pthread_mutex_unlock(&mutEntry);
        if(stat != 0){
            cout << "Error unlocking mutex" << endl;
        }

        /* Car entered PLCS */

        sleep(2); // wait a bit inside PL

        /* Exit */
        //driveUpToExit();

        stat = pthread_mutex_lock(&mutExit);
        if(stat != 0){
            cout << "Error locking mutex" << endl;
        }

        cout << "Car driving up to exit" << endl;

        carWaitingToExit = true;

        stat = pthread_cond_signal(&guardExit);
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
        cout << "Car has exited PL" << endl;
        carWaitingToExit = false;

        stat = pthread_cond_signal(&guardExit);
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        stat = pthread_mutex_unlock(&mutExit);
        if(stat != 0){
            cout << "Error unlocking mutex" << endl;
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
        if(stat != 0){
            cout << "Error condition signaling" << endl;
        }

        while(carWaitingToEnter){
            stat = pthread_cond_wait(&guardEntry, &mutEntry);
            if(stat != 0){
                cout << "Error condition waiting" << endl;
            }
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
        if(stat != 0){
            cout << "Error unlocking mutex" << endl;
        }

        cout << endl;
    }

    return arg;
}

int main(){
    pthread_t car, entry_gate, exit_gate;

    int status;

    /* Creating threads */
    status = pthread_create(&car, NULL, carThread, NULL);
    if (status != 0){
        cout << "Error creating car thread" << endl;
    }

    status = pthread_create(&entry_gate, NULL, entryGuardThread, NULL);
    if (status != 0){
        cout << "Error creating guardEntry gate thread" << endl;
    }

    status = pthread_create(&exit_gate, NULL, exitGuardThread, NULL);
    if (status != 0){
        cout << "Error creating guardExit gate thread" << endl;
    }

    /* Joining threads */
    status = pthread_join(car, NULL);
    if (status != 0){
        cout << "Error joining car thread" << endl;
    }

    status = pthread_join(entry_gate, NULL);
    if (status != 0){
        cout << "Error joining guardEntry gate thread" << endl;
    }

    status = pthread_join(exit_gate, NULL);
    if (status != 0){
        cout << "Error joining guardExit gate thread" << endl;
    }

    pthread_exit(NULL);
}
