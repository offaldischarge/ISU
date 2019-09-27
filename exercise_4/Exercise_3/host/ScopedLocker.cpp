#include "ScopedLocker.h"

ScopedLocker::ScopedLocker(pthread_mutex_t &mutex){
    mtx = &mutex;
    lock(mtx);
}

ScopedLocker::~ScopedLocker(){
    unlock(mtx);
}

void ScopedLocker::lock(pthread_mutex_t *mutex){
    pthread_mutex_lock(mutex);
}

void ScopedLocker::unlock(pthread_mutex_t *mutex){
    pthread_mutex_unlock(mutex);
}
