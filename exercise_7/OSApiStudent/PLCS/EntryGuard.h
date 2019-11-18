#ifndef ENTRYGUARD_H_
#define ENTRYGUARD_H_

#include <osapi/ThreadFunctor.hpp>


struct EntryDoorOpenConfirm : public Message{
    bool result;
};

class EntryGuard : public osapi::ThreadFunctor {

public:
    enum EntryIDs {ID_ENTRY_DOOR_OPEN_CONFIRM};
    osapi::MsgQueue getMsgQueue();
protected:
    virtual void run();
private:
    void entryHandleOpenRequest(EntryDoorOpenRequest*);
    void entryDoorHandler(unsigned long, osapi::Message*);

    osapi::MsgQueue entryMq;
};

#endif
