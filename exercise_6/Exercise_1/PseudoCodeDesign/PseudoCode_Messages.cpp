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
    deque<Message*> msgQueue;

    struct Item : public Message {
        unsigned long id;
        Message *msg;
    };

    mutex mtx;
    cond_t condSend;
    cond_t condReceive;

    unsigned long maxSize;
}

MsgQueue(unsigned long maxSize){ //Constructor
    msgQueue(maxSize); //set size of message queue
}

void send(unsigned long id, Message *msg = NULL){

    mutex_lock(mtx);
    //block if filled to the maximum denoted capacity
    while(deque is full){
        cond_wait(condReceive, mtx);
    }

    Item *sendItem;
    sendItem.id = id;
    *sendItem.msg = *msg;

    msgQueue.push_back(sendItem);

    cond_signal(condSend);

    mutex_unlock(mtx);
}

Message* receive(unsigned long &id){

    mutex_lock(mtx);

    //block if queue is empty
    while(deque is empty){
        cond_wait(condSend, mtx);
    }

    Item *receiveItem = msgQueue.front();
    msgQueue.pop_front();

    id = *receiveItem.id;

    cond_signal(condReceive);

    mutex_unlock(mtx);

    return *receiveItem.msg;
}

~MsgQueue(){}

/*--------------------------------*/
