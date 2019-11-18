#include "Car.h"

virtual void Car::run(){
    enterPLCS();

    for(;;){    //EVENT LOOP
        unsigned long id;
        Message* msg = carMq.receive(id); //RECEIVE
        carHandler(id, msg);
        delete msg;
    }
}

void Car::carHandler(unsigned long id, osapi::Message* msg){
    switch(id){
        case ID_ENTRY_INDICATOR:
            carHandleEntryIndicator();
            break;
		case ID_EXIT_INDICATOR:
            carHandleExitIndicator();
            break;
        case ID_ENTRY_DOOR_OPEN_CONFIRM:
            carHandleEntryOpenConfirm(static_cast<EntryDoorOpenConfirm*>(msg));
			sleep((rand() % 6) + 1); //wait a bit inside parking lot
			exitPLCS(); //SEND EXIT INDICATOR
            break;
        case ID_EXIT_DOOR_OPEN_CONFIRM:
            carHandleExitOpenConfirm(static_cast<ExitDoorOpenConfirm*>(msg));
			sleep((rand() % 6) + 1); //wait a bit outside parking lot
			enterPLCS(); //SEND ENTRY INDICATOR AGAIN
            break;
    }
}

void Car::carHandleEntryIndicator(){
    std::cout << "Car " << *carID << " is waiting outside PL" << std::endl;
    EntryDoorOpenRequest* request = new EntryDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    entry->getMsgQueue->send(ID_ENTRY_DOOR_OPEN_REQUEST, request); //?
}

void Car::carHandleExitIndicator(){
    std::cout << "Car " << *carID << " is driving up to exit" << std::endl;
    ExitDoorOpenRequest* request = new ExitDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    exit->getMsgQueue->send(ID_EXIT_DOOR_OPEN_REQUEST, request); //?
}

void Car::carHandleEntryOpenConfirm(EntryDoorOpenConfirm* confirm){
    if(confirm->result){
        std::cout << "Car " << *carId << " has entered PL" << std::endl;
    }
}

void Car::carHandleExitOpenConfirm(ExitDoorOpenConfirm* confirm){
    if(confirm->result){
        std::cout << "Car " << *carId << " has exited PL" << std::endl;
    }
}

void Car::enterPLCS(){
    carMq.send(ID_ENTRY_INDICATOR); //SEND ENTRY INDICATOR
}

void Car::exitPLCS(){
    carMq.send(ID_EXIT_INDICATOR); //SEND EXIT INDICATOR
}
