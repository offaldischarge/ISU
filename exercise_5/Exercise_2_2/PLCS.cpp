#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

static pthread_mutex_t mtx_enter = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mtx_exit = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t entryGuard = PTHREAD_COND_INITIALIZER;
static pthread_cond_t exitGuard = PTHREAD_COND_INITIALIZER;

static bool carWaitingToEnter,carWaitingToExit = false;
static bool entryGuardOpen, exitGuardOpen = false;

/* Car thread */
static void* carThread(void* arg){
    int status = 0; //error integer
    int *id = (int *) arg;

    srand(time(0)); //Generates seed based on current time

    while(true){
        /* Entry */
        status = pthread_mutex_lock(&mtx_enter);
        if(status != 0){
            cout << "Error locking mutex" << endl;
        }
        cout << "Car " << *id << " waiting outside PL" << endl;

        carWaitingToEnter = true;

        status = pthread_cond_signal(&entryGuard);
        if(status != 0){
            cout << "Error condition signaling" << endl;
        }

        while(!entryGuardOpen){
            status = pthread_cond_wait(&entryGuard, &mtx_enter);
            if(status != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        cout << "Car " << *id << " has entered PL" << endl;

        carWaitingToEnter = false;

        status = pthread_cond_signal(&entryGuard);
        if(status != 0){
            cout << "Error condition signaling" << endl;
        }

        status = pthread_mutex_unlock(&mtx_enter);
        if(status != 0){
            cout << "Error condition signaling" << endl;
        }

        sleep((rand() % 6) + 1); //wait a bit outside parking lot

        /* Exit */
        status = pthread_mutex_lock(&mtx_exit);
        if(status != 0){
            cout << "Error locking mutex" << endl;
        }

        cout << "Car " << *id << " driving up to exit" << endl;

        carWaitingToExit = true;

        status = pthread_cond_signal(&exitGuard);
        if(status != 0){
            cout << "Error condition signaling" << endl;
        }

        while(!exitGuardOpen){
            status = pthread_cond_wait(&exitGuard, &mtx_exit);
            if(status != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        cout << "Car " << *id << " has exited PL" << endl;

        carWaitingToExit = false;

        status = pthread_cond_signal(&exitGuard);
        if(status != 0){
            cout << "Error condition signaling" << endl;
        }

        status = pthread_mutex_unlock(&mtx_exit);
        if(status != 0){
            cout << "Error locking mutex" << endl;
        }

        sleep((rand() % 6) + 1); //wait a bit outside parking lot
    }

    return arg;
}

/* Entry guard thread */
static void* entryGuardThread(void* arg){
    int status = 0;

    while(true){
        status = pthread_mutex_lock(&mtx_enter);
        if(status != 0){
            cout << "Error locking mutex" << endl;
        }

        while(!carWaitingToEnter){
            status = pthread_cond_wait(&entryGuard, &mtx_enter);
            if(status != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        entryGuardOpen = true;

        status = pthread_cond_signal(&entryGuard);
        if(status != 0){
            cout << "Error condition signaling" << endl;
        }

        while(carWaitingToEnter){
            status = pthread_cond_wait(&entryGuard, &mtx_enter);
            if(status != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        entryGuardOpen = false;

        status = pthread_mutex_unlock(&mtx_enter);
        if(status != 0){
            cout << "Error unlocking mutex" << endl;
        }
    }

    return arg;
}

/* Exit guard thread */
static void* exitGuardThread(void* arg){
    int status = 0;

    while(true){

        status = pthread_mutex_lock(&mtx_exit);
        if(status != 0){
            cout << "Error locking mutex" << endl;
        }

        while(!carWaitingToExit){
            status = pthread_cond_wait(&exitGuard, &mtx_exit);
            if(status != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        exitGuardOpen = true;

        status = pthread_cond_signal(&exitGuard);
        if(status != 0){
            cout << "Error condition signaling" << endl;
        }

        while(carWaitingToExit){
            status = pthread_cond_wait(&exitGuard, &mtx_exit);
            if(status != 0){
                cout << "Error condition waiting" << endl;
            }
        }

        exitGuardOpen = false;

        status = pthread_mutex_unlock(&mtx_exit);
        if(status != 0){
            cout << "Error unlocking mutex" << endl;
        }
    }

    return arg;
}

int main(){
    int status;

    int arraySize = 5;

    int carID[arraySize];
    pthread_t cars[arraySize];
    pthread_t entry_gate, exit_gate;

    for(int i = 0; i < arraySize; i++){
        carID[i] = i;
    }

    /* Creating threads */
    for(int i = 0; i < arraySize; i++){
        status = pthread_create(&cars[i], NULL, carThread, &carID[i]);
        if (status != 0){
            cout << "Error creating car thread" << endl;
        }

    }

    status = pthread_create(&entry_gate, NULL, entryGuardThread, NULL);
    if (status != 0){
        cout << "Error creating entryGuard gate thread" << endl;
    }

    status = pthread_create(&exit_gate, NULL, exitGuardThread, NULL);
    if (status != 0){
        cout << "Error creating exitGuard gate thread" << endl;
    }

    /* Joining threads */
    for(int i = 0; i < arraySize; i++){
        status = pthread_join(cars[i], NULL);
        if (status != 0){
            cout << "Error joining car thread" << endl;
        }
    }

    status = pthread_join(entry_gate, NULL);
    if (status != 0){
        cout << "Error joining entryGuard gate thread" << endl;
    }

    status = pthread_join(exit_gate, NULL);
    if (status != 0){
        cout << "Error joining exitGuard gate thread" << endl;
    }

    pthread_exit(NULL);
}
