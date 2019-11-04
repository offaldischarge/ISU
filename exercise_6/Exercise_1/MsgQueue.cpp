#include "MsgQueue.h"

MsgQueue::MsgQueue(unsigned long maxSize) : msgQueue(maxSize){
    maxSize = maxSize;
}

MsgQueue::~MsgQueue(){}

void MsgQueue::send(unsigned long id, Message* msg){
    pthread_mutex_lock(&mtx);

    while(msgQueue.size() == maxSize){
        pthread_cond_wait(&condReceive, &mtx);
    }

    item->id = id;
    *item->msg = *msg;

    msgQueue.push_back(item);

    pthread_cond_signal(&condSend);

    pthread_mutex_unlock(&mtx);
}

Message* MsgQueue::receive(unsigned long &id){
    pthread_mutex_lock(&mtx);

    while(msgQueue.empty()){
        pthread_cond_wait(&condReceive, &mtx);
    }

    item = (Item*) msgQueue.front(); //Downcasting
    msgQueue.pop_front();

    id = item->id;

    pthread_cond_signal(&condReceive);

    pthread_mutex_unlock(&mtx);

    return item->msg;
}

int main(){

}
