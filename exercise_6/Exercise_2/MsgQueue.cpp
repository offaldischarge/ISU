#include "MsgQueue.h"

MsgQueue::MsgQueue(unsigned long maxSize) {

    pthread_mutex_lock(&mtx);

    maxQueueSize = maxSize;

    queueSizeSet = true;

    pthread_cond_broadcast(&setQueueSize);

    pthread_mutex_unlock(&mtx);
}

void MsgQueue::send(unsigned long id, Message* msg){

    pthread_mutex_lock(&mtx);

    while(!queueSizeSet){
        pthread_cond_wait(&setQueueSize, &mtx);
    }

    while(msgQueue.size() == maxQueueSize){
        pthread_cond_wait(&condSend, &mtx);
    }

    Item* item = new Item(id, msg);
    msgQueue.push_back(item);

    pthread_cond_signal(&condReceive);

    pthread_mutex_unlock(&mtx);
}

Message* MsgQueue::receive(unsigned long& id){

    pthread_mutex_lock(&mtx);

    while(!queueSizeSet){
        pthread_cond_wait(&setQueueSize, &mtx);
    }

    while(msgQueue.empty()){
        pthread_cond_wait(&condReceive, &mtx);
    }

    Item* item = msgQueue.front();
    msgQueue.pop_front();

    pthread_cond_signal(&condSend);

    id = item->id;
    Message* msg = item->msg;
    delete item;

    pthread_mutex_unlock(&mtx);

    return msg;
}

MsgQueue::~MsgQueue(){}
