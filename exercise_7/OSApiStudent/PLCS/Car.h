#ifndef CAR_H_
#define CAR_H_

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>
#include "EntryGuard.h"
#include "ExitGuard.h"

struct EntryDoorOpenRequest : public Message{
    MsgQueue* whoIsAskingMq;
};

struct ExitDoorOpenRequest : public Message{
    MsgQueue* whoIsAskingMq;
};

class Car : public osapi::ThreadFunctor {
public:
    static const int MAX_QUEUE_SIZE = 10;
    Car(EntryGuard* entryguard, ExitGuard* exitguard, int) :
    entry(entrygard), exit(exitguad),
    carMq(MAX_QUEUE_SIZE), entry(MAX_QUEUE_SIZE), exit(MAX_QUEUE_SIZE) {}
    enum CarIDs {ID_ENTRY_INDICATOR,
                 ID_ENTRY_DOOR_OPEN_CONFIRM,
                 ID_EXIT_INDICATOR,
                 ID_EXIT_DOOR_OPEN_CONRFIM}
protected:
    virtual void run();
private:
    void carHandler(unsigned long, osapi::Message*);
    void carHandleEntryIndicator();
    void carHandleExitIndicator();
    void carHandleEntryOpenConfirm(EntryDoorOpenConfirm*);
    void carHandleExitOpenConfirm(ExitDoorOpenConfirm*);

    void enterPLCS();
    void exitPLCS();

    osapi::MsgQueue carMq;
    int carId;

    EntryGuard* entry;
    ExitGuard* exit;
};

#endif
