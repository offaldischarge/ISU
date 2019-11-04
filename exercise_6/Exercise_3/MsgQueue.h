#include "Message.h"
#include <deque>
#include <pthread.h>

class MsgQueue{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg = NULL);
    Message* receive(unsigned long& id);
    ~MsgQueue();
private:
    unsigned long maxQueueSize;
    bool queueSizeSet = false;

    struct Item{
        Item(unsigned long id, Message* msg) : id(id), msg(msg){}
        unsigned long id;
        Message* msg;
    };

    std::deque<Item*> msgQueue;

    pthread_cond_t condSend = PTHREAD_COND_INITIALIZER;
    pthread_cond_t condReceive = PTHREAD_COND_INITIALIZER;
    pthread_cond_t setQueueSize = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
};
