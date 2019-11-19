#include "ExitGuard.h"

osapi::MsgQueue* ExitGuard::getMsgQueue(){
    return &exitMq;
}

void ExitGuard::run(){
    for(;;){
        unsigned long id;
        osapi::Message *msg = exitMq.receive(id);
        exitDoorHandler(id, msg);
        delete msg;
    }
}

void ExitGuard::exitHandleOpenRequest(ExitDoorOpenRequest* request){
    ExitDoorOpenConfirm* confirm = new ExitDoorOpenConfirm;
    confirm->result = true;
    request->car->getMsgQueue()->send(Car::ID_EXIT_DOOR_OPEN_CONFIRM, confirm);
}

void ExitGuard::exitDoorHandler(unsigned long id, osapi::Message* msg){
    switch(id){
        case ID_EXIT_DOOR_OPEN_REQUEST:
            exitHandleOpenRequest(static_cast<ExitDoorOpenRequest*>(msg));
            break;
    }
}
