#ifndef ENTRYGUARD_H_
#define ENTRYGUARD_H_

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>
#include "Car.h"
#include "PLCSMessages.h"

class EntryGuard : public osapi::ThreadFunctor {

public:
    static const int MAX_QUEUE_SIZE = 10;
    EntryGuard() : entryMq(MAX_QUEUE_SIZE){}
    enum EntryIDs {ID_ENTRY_DOOR_OPEN_REQUEST};
    osapi::MsgQueue* getMsgQueue();
protected:
    virtual void run();
private:
    void entryHandleOpenRequest(EntryDoorOpenRequest*);
    void entryDoorHandler(unsigned long, osapi::Message*);

    osapi::MsgQueue entryMq;
};

#endif
