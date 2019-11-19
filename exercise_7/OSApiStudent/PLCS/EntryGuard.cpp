#include "EntryGuard.h"

osapi::MsgQueue* EntryGuard::getMsgQueue(){
    return &entryMq;
}

void EntryGuard::run(){
    for(;;){                                //event loop
        unsigned long id;
        osapi::Message *msg = entryMq.receive(id);
        entryDoorHandler(id, msg);
        delete msg;
    }
}

void EntryGuard::entryHandleOpenRequest(EntryDoorOpenRequest* request){
    EntryDoorOpenConfirm* confirm = new EntryDoorOpenConfirm;
    confirm->result = true;
    request->car->getMsgQueue()->send(Car::ID_ENTRY_DOOR_OPEN_CONFIRM, confirm);
}

void EntryGuard::entryDoorHandler(unsigned long id, osapi::Message* msg){
    switch(id){
        case ID_ENTRY_DOOR_OPEN_REQUEST:
            entryHandleOpenRequest(static_cast<EntryDoorOpenRequest*>(msg));
            break;
    }
}
