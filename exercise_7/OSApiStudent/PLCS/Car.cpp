#include "Car.h"

void Car::carHandleEntryOpenConfirm(EntryDoorOpenConfirm* confirm){
    if(confirm->result){
        std::cout << "Car " << carID << " has entered PL" << std::endl;
        carMq.send(ID_WAIT_INSIDE_PLCS);
    }
}

void Car::carHandleExitOpenConfirm(ExitDoorOpenConfirm* confirm){
    if(confirm->result){
        std::cout << "Car " << carID << " has exited PL" << std::endl;
        carMq.send(ID_WAIT_OUTSIDE_PLCS);
    }
}

void Car::carHandleEntryIndicator(){
    std::cout << "Car " << carID << " is waiting outside PL" << std::endl;
    EntryDoorOpenRequest* request = new EntryDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    entryGuard->getMsgQueue()->send(EntryGuard::ID_ENTRY_DOOR_OPEN_REQUEST, request); //?
}

void Car::carHandleExitIndicator(){
    std::cout << "Car " << carID << " is driving up to exit" << std::endl;
    ExitDoorOpenRequest* request = new ExitDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    exitGuard->getMsgQueue()->send(ExitGuard::ID_EXIT_DOOR_OPEN_REQUEST, request); //?
}

void Car::carHandler(unsigned long id, osapi::Message* msg){
    switch(id){
        case ID_ENTRY_DOOR_OPEN_CONFIRM:
            carHandleEntryOpenConfirm(static_cast<EntryDoorOpenConfirm*>(msg));
            break;
        case ID_EXIT_DOOR_OPEN_CONFIRM:
            carHandleExitOpenConfirm(static_cast<ExitDoorOpenConfirm*>(msg));
            break;
        case ID_WAIT_INSIDE_PLCS:
            osapi::sleep((rand() % 6000) + 1000); //wait a bit inside parking lot
            carHandleExitIndicator();
            break;
        case ID_WAIT_OUTSIDE_PLCS:
            osapi::sleep((rand() % 6000) + 1000); //wait a bit outside parking lot
            carHandleEntryIndicator();
            break;
    }
}

void Car::run(){
    carMq.send(ID_WAIT_OUTSIDE_PLCS); //Start indicator

    for(;;){    //EVENT LOOP
        unsigned long id;
        osapi::Message* msg = carMq.receive(id); //RECEIVE
        carHandler(id, msg);
        delete msg;
    }
}
