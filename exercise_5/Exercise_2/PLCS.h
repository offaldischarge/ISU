#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

class PLCS{
public:
    PLCS(int);
    static void* carThread(void* arg);
    static void* entryGuardThread(void* arg);
    static void* exitGuardThread(void * arg);
private:
    static pthread_mutex_t mutEntry;
    static pthread_mutex_t mutExit;
};
