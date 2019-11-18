#ifndef EXITGUARD_H_
#define EXITGUARD_H_

#include <osapi/ThreadFunctor.hpp>

struct ExitDoorOpenConfirm : public Message{
    bool result;
};

class ExitGuard : public osapi::ThreadFunctor {
public:
    enum ExitIDs{ID_EXIT_DOOR_OPEN_REQUEST};
    osapi::MsgQueue getMsgQueue();
protected:
    virtual void run();
private:
    void exitHandleOpenRequest(ExitDoorOpenRequest*);
    void exitDoorHandler(unsigned long, osapi::Message*);

    osapi::MsgQueue exitMq;
};

#endif
