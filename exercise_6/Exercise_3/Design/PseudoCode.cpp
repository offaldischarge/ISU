

/* Car thread */

enum{
    ID_START_INDICATOR,
    ID_ENTRY_DOOR_OPEN_CONFIRM,
    ID_EXIT_DOOR_OPEN_CONFIRM
}

pthread car;
MsgQueue carMsgQ;

MsgQueue entryMsgQ;

MsgQueue exitMsgQ;

void startCarThread(){
    pthread_create();

    carMsgQ.send(ID_START_INDICATOR); //SEND
}

void* carEventLoop(void*){
    for(;;){    //EVENT LOOP
        unsigned long id;
        Message* msg = carMq.receive(id); //RECEIVE
        carHandler(id, msg);
        delete(msg);
    }
}

void carHandler(unsigned long id, Message* msg){
    switch(id){
        case ID_START_INDICATOR:
            carHandleStartIndicator();
            break;
        case ID_ENTRY_DOOR_OPEN_CONFIRM:
            car
    }
}
