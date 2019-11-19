#ifndef CAR_H_
#define CAR_H_

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Message.hpp>
#include <osapi/Utility.hpp>
#include <iostream>
#include "EntryGuard.h"
#include "ExitGuard.h"
#include "PLCSMessages.h" //Common Message header file

// forward declaration
class EntryGuard;
class ExitGuard;

class Car : public osapi::ThreadFunctor {

public:
    static const int MAX_QUEUE_SIZE = 10;

    osapi::MsgQueue* getMsgQueue();

    Car(EntryGuard* entry, ExitGuard* exit, int id) :
    entryGuard(entry), exitGuard(exit), carMq(MAX_QUEUE_SIZE), carID(id) {}

    enum CarIDs {ID_ENTRY_DOOR_OPEN_CONFIRM,
                 ID_WAIT_INSIDE_PLCS,
                 ID_EXIT_DOOR_OPEN_CONFIRM,
                 ID_WAIT_OUTSIDE_PLCS};
protected:
    virtual void run();
private:
    void carHandler(unsigned long, osapi::Message*);
    void carHandleEntryIndicator();
    void carHandleExitIndicator();
    void carHandleEntryOpenConfirm(EntryDoorOpenConfirm*);
    void carHandleExitOpenConfirm(ExitDoorOpenConfirm*);

    osapi::MsgQueue carMq;
    int carID;

    EntryGuard* entryGuard;
    ExitGuard* exitGuard;
};

#endif
