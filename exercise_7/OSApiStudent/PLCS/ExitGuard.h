#ifndef EXITGUARD_H_
#define EXITGUARD_H_

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>
#include "Car.h"
#include "PLCSMessages.h"

class ExitGuard : public osapi::ThreadFunctor {
public:
    static const int MAX_QUEUE_SIZE = 10;
    ExitGuard() : exitMq(MAX_QUEUE_SIZE){}
    enum ExitIDs{ID_EXIT_DOOR_OPEN_REQUEST};
    osapi::MsgQueue* getMsgQueue();
protected:
    virtual void run();
private:
    void exitHandleOpenRequest(ExitDoorOpenRequest*);
    void exitDoorHandler(unsigned long, osapi::Message*);

    osapi::MsgQueue exitMq;
};

#endif
