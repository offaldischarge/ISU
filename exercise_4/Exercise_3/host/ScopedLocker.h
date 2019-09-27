#pragma once
#include <pthread.h>

class ScopedLocker{
public:
    ScopedLocker(pthread_mutex_t &);
    ~ScopedLocker();
    void lock(pthread_mutex_t *);
    void unlock(pthread_mutex_t *);
private:
    pthread_mutex_t *mtx;
};
