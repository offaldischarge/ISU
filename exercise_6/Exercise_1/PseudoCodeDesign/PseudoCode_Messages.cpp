/*---------------------------------*/

/* Message class */

class Message{
public:
    virtual ~Message();
};

/*--------------------------------*/

/* Message Queue Class */

class MsgQueue{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg = NULL);
    Message* receive(unsigned long& id);
    ~MsgQueue();
private:
    unsigned long maxQueueSize;
    bool queueSizeSet = false;

    deque<Message*> msgQueue;

    struct Item {
        unsigned long id;
        Message *msg;
    };

    mutex mtx;
    cond_t condSend;
    cond_t condReceive;
    cond_t setQueueSize
}

MsgQueue(unsigned long maxSize){ //Constructor
    mutex_lock(mtx);

    maxQueueSize = maxSize;

    queueSizeSet = true;

    broadcast(setQueueSize);

    mutex_unlock(mtx);
}

void send(unsigned long id, Message *msg = NULL){

    mutex_lock(mtx);

    while(queueSizeSet hasn't been set){
        cond_wait(setQueueSize, mtx);
    }

    //block if filled to the maximum denoted capacity
    while(deque is full){
        cond_wait(condSend, mtx);
    }

    Item *sendItem = new Item(id, msg); //sender allocates
    msgQueue.push_back(sendItem);

    cond_signal(condReceive);

    mutex_unlock(mtx);
}

Message* receive(unsigned long &id){

    mutex_lock(mtx);

    while(queueSizeSet hasn't been set){
        cond_wait(setQueueSize, mtx);
    }

    //block if queue is empty
    while(deque is empty){
        cond_wait(condReceive, mtx);
    }

    Item *receiveItem = msgQueue.front();
    msgQueue.pop_front();

    cond_signal(condSend);

    id = receiveItem.id;
    Message *msg = item->msg;
    delete item;        //receiver deletes

    mutex_unlock(mtx);

    return msg;
}

~MsgQueue(){}

/*--------------------------------*/
