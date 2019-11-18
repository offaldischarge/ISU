#include "MsgQueue.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

static int noOfCars = 3;
static int noOfMsg = 10;

MsgQueue entryMq(noOfMsg);
MsgQueue exitMq(noOfMsg);

/* Messages */

struct EntryDoorOpenRequest : public Message{
    MsgQueue* whoIsAskingMq;
};

struct ExitDoorOpenRequest : public Message{
    MsgQueue* whoIsAskingMq;
};

struct EntryDoorOpenConfirm : public Message{
    bool result;
};

struct ExitDoorOpenConfirm : public Message{
    bool result;
};

/* IDs for car, entry and exit */

enum carIDs{
    ID_ENTRY_INDICATOR,
    ID_ENTRY_DOOR_OPEN_CONFIRM,
    ID_WAIT_INSIDE_PLCS,
    ID_EXIT_INDICATOR,
    ID_EXIT_DOOR_OPEN_CONFIRM,
    ID_WAIT_OUTSIDE_PLCS
};

enum entryDoorIDs {ID_ENTRY_DOOR_OPEN_REQUEST};

enum exitDoorIDs {ID_EXIT_DOOR_OPEN_REQUEST};

/* Car thread */

void enterPLCS(MsgQueue& carMq){
    carMq.send(ID_ENTRY_INDICATOR); //SEND ENTRY INDICATOR
}

void exitPLCS(MsgQueue& carMq){
    carMq.send(ID_EXIT_INDICATOR); //SEND EXIT INDICATOR
}

void carHandleEntryIndicator(int* carID, MsgQueue& carMq){
    std::cout << "Car " << *carID << " is waiting outside PL" << std::endl;
    EntryDoorOpenRequest* request = new EntryDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    entryMq.send(ID_ENTRY_DOOR_OPEN_REQUEST, request);
}

void carHandleExitIndicator(int* carID, MsgQueue& carMq){
    std::cout << "Car " << *carID << " is driving up to exit" << std::endl;
    ExitDoorOpenRequest* request = new ExitDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    exitMq.send(ID_EXIT_DOOR_OPEN_REQUEST, request);
}

void carHandleEntryOpenConfirm(EntryDoorOpenConfirm* confirm, int* carId, MsgQueue& carMq){
    if(confirm->result){
        std::cout << "Car " << *carId << " has entered PL" << std::endl;
        carMq.send(ID_WAIT_INSIDE_PLCS);
    }
}

void carHandleExitOpenConfirm(ExitDoorOpenConfirm* confirm, int* carId, MsgQueue& carMq){
    if(confirm->result){
        std::cout << "Car " << *carId << " has exited PL" << std::endl;
        carMq.send(ID_WAIT_OUTSIDE_PLCS);
    }
}

void carHandler(unsigned long id, Message* msg, int* carID, MsgQueue& carMq){ //car dispatcher
    switch(id){
        case ID_ENTRY_INDICATOR:
            carHandleEntryIndicator(carID, carMq);
            break;
        case ID_ENTRY_DOOR_OPEN_CONFIRM:
            carHandleEntryOpenConfirm(static_cast<EntryDoorOpenConfirm*>(msg), carID, carMq);
            break;
        case ID_WAIT_INSIDE_PLCS:
            sleep((rand() % 6) + 1); //wait a bit inside parking lot
            exitPLCS(carMq); //SEND EXIT INDICATOR
            break;
        case ID_EXIT_INDICATOR:
            carHandleExitIndicator(carID, carMq);
            break;
        case ID_EXIT_DOOR_OPEN_CONFIRM:
            carHandleExitOpenConfirm(static_cast<ExitDoorOpenConfirm*>(msg), carID, carMq);
            break;
        case ID_WAIT_OUTSIDE_PLCS:
            sleep((rand() % 6) + 1); //wait a bit outside parking lot
            enterPLCS(carMq); //SEND ENTRY INDICATOR AGAIN
            break;
    }
}

void* carThread(void* arg){

    int* carId = (int*) arg;
    MsgQueue carMq(noOfMsg);

    enterPLCS(carMq);

    while(true){    //EVENT LOOP
        unsigned long id;
        Message* msg = carMq.receive(id); //RECEIVE
        carHandler(id, msg, carId, carMq);
        delete msg;
    }

    return nullptr;
}

/* Car thread end */

/* Entry door thread */

void entryHandleOpenRequest(EntryDoorOpenRequest* request){
    EntryDoorOpenConfirm* confirm = new EntryDoorOpenConfirm;
    confirm->result = true;
    request->whoIsAskingMq->send(ID_ENTRY_DOOR_OPEN_CONFIRM, confirm);
}

void entryDoorHandler(unsigned long id, Message *msg){  //entry door dispatcher
    switch(id){
        case ID_ENTRY_DOOR_OPEN_REQUEST:
            entryHandleOpenRequest(static_cast<EntryDoorOpenRequest*>(msg));
            break;
    }
}

void* entryDoorThread(void* arg){
    while(true){                                //event loop
        unsigned long id;
        Message *msg = entryMq.receive(id);
        entryDoorHandler(id, msg);
        delete msg;
    }

    return nullptr;
}

/* Entry door thread end */

/* Exit door thread */

void exitHandleOpenRequest(ExitDoorOpenRequest* request){
    ExitDoorOpenConfirm* confirm = new ExitDoorOpenConfirm;
    confirm->result = true;
    request->whoIsAskingMq->send(ID_EXIT_DOOR_OPEN_CONFIRM, confirm);
}

void exitDoorHandler(unsigned long id, Message *msg){   //exit door dispatcher
    switch(id){
        case ID_EXIT_DOOR_OPEN_REQUEST:
            exitHandleOpenRequest(static_cast<ExitDoorOpenRequest*>(msg));
            break;
    }
}

void* exitDoorThread(void* arg){
    while(true){
        unsigned long id;
        Message *msg = exitMq.receive(id);
        exitDoorHandler(id, msg);
        delete msg;
    }
    return nullptr;
}

/* Entry door thread end */

int main(){
    srand(time(0)); //Generates seed based on current time

    int carID[noOfCars];

    pthread_t cars[noOfCars];
    pthread_t entryDoor, exitDoor;

    for(int i = 0; i < noOfCars; i++){
        carID[i] = i;
    }

    for(int i = 0; i < noOfCars; i++){
        pthread_create(&cars[i], NULL, carThread, &carID[i]);
    }

    pthread_create(&entryDoor, NULL, entryDoorThread, NULL);
    pthread_create(&exitDoor, NULL, exitDoorThread, NULL);

    for(int i = 0; i < noOfCars; i++){
        pthread_join(cars[i], NULL);
    }

    pthread_join(entryDoor, NULL);
    pthread_join(exitDoor, NULL);

    return 0;
}
