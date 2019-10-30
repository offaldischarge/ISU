#include "Message.h"
#include <deque>
#include <pthread.h>

using namespace std;

class MsgQueue{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id, Message *msg = NULL);
    Message* receive(unsigned long &id);
    ~MsgQueue();
private:
    unsigned long maxSize;

    deque<Message*> msgQueue;

    struct Item : public Message {
        unsigned long id;
        Message *msg;
    } *item;

    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condSend = PTHREAD_COND_INITIALIZER;
    pthread_cond_t condReceive = PTHREAD_COND_INITIALIZER;
};
