
static int noOfMsg = 10;

static int noOfCars = 10;
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

/* Car thread */

enum{
    ID_ENTRY_INDICATOR,
    ID_EXIT_INDICATOR,
    ID_ENTRY_DOOR_OPEN_CONFIRM,
    ID_EXIT_DOOR_OPEN_CONFIRM
};

MsgQueue carMq(noOfMsg);

void carHandler(unsigned long id, Message* msg, carid id){
    switch(id){
        case ID_ENTRY_INDICATOR:
            carHandleEntryIndicator(id);
            break;
		case ID_EXIT_INDICATOR:
            carHandleExitIndicator(id);
            break;
        case ID_ENTRY_DOOR_OPEN_CONFIRM:
            carHandleEntryOpenConfirm(static_cast<EntryDoorOpenConfirm*>(msg), id);
			wait outside of PL
			exitPLCS();
            break;
        case ID_EXIT_DOOR_OPEN_CONFIRM:
            carHandleExitOpenConfirm(static_cast<ExitDoorOpenConfirm*>(msg), id);
			wait inside PL
			enterPLCS(); //SEND ENTRY INDICATOR AGAIN
            break;
    }
}

void* carThread(void* arg){

    carID = arg;

    for(;;){    //EVENT LOOP
        unsigned long id;
        Message* msg = carMq.receive(id); //RECEIVE
        carHandler(id, msg, carID);
        delete msg;
    }
}

void enterPLCS(){
    carMq.send(ID_ENTRY_INDICATOR); //SEND ENTRY INDICATOR
}

void exitPLCS(){
    carMq.send(ID_EXIT_INDICATOR); //SEND EXIT INDICATOR
}


void carHandleEntryIndicator(carid id){
    cout << car id is waiting outside PL << endl;
    EntryDoorOpenRequest* request = new EntryDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    entryMq.send(ID_ENTRY_DOOR_OPEN_REQUEST, request);
}

void carHandleExitIndicator(carid id){
    cout << car id is driving up to exit << endl;
    ExitDoorOpenRequest* request = new ExitDoorOpenRequest;
    request->whoIsAskingMq = &carMq;
    exitMq.send(ID_EXIT_DOOR_OPEN_REQUEST, request);
}

void carHandleEntryDoorOpenConfirm(EntryDoorOpenConfirm* confirm, carid id){
    if(confirm->result){
        cout << car id has entered pl << endl;
    }
}

void carHandleExitDoorOpenConfirm(ExitDoorOpenConfirm* confirm, carid id){
    if(confirm->result){
        cout << car id has exited pl << endl;
    }
}
/* Car thread end */

/* Entry door thread */

enum{ID_ENTRY_DOOR_OPEN_REQUEST}

MsgQueue entryMq(noOfMsg);

void entryHandleRequest(EntryDoorOpenRequest* request){
    EntryDoorOpenConfirm* confirm = new EntryDoorOpenConfirm;
    confirm->result = true;
    request->whoIsAskingMq->send(ID_ENTRY_DOOR_OPEN_CONFIRM, confirm);
}

void entryDoorHandler(unsigned long id, Message *msg){
    switch(id){
        case ID_ENTRY_DOOR_OPEN_REQUEST:
            entryHandleOpenRequest(static_cast<EntryDoorOpenRequest*>(msg));
            break;
    }
}

void* entryDoorController(void* arg){
    for(;;){
        unsigned long id;
        Message *msg = entryMq.receive(id);
        entryDoorHandler(id, msg);
        delete msg;
    }
}

/* Entry door thread end */

/* Exit door thread */

enum{ID_EXIT_DOOR_OPEN_REQUEST}

MsgQueue exitMq(noOfMsg);

void exitHandleOpenRequest(ExitDoorOpenRequest* request){
    ExitDoorOpenConfirm* confirm = new ExitDoorOpenConfirm;
    confirm->result = true;
    request->whoIsAskingMq->send(ID_EXIT_DOOR_OPEN_CONFIRM, confirm);
}

void exitDoorHandler(unsigned long id, Message *msg){
    switch(id){
        case ID_EXIT_DOOR_OPEN_REQUEST:
            exitHandleOpenRequest(static_cast<ExitDoorOpenRequest*>(msg));
            break;
    }
}

void* exitDoorController(void* arg){
    for(;;){
        unsigned long id;
        Message *msg = exitMq.receive(id);
        exitDoorHandler(id, msg);
        delete msg;
    }
}

/* Entry door thread end */

int main(){
    srand(time(0)); //Generates seed based on current time

    int carID[noOfCars];

    pthread_t cars[noOfCars];
    pthread_t entryDoor;
    pthread_t exitDoor;

    for(each car){
        carID = id;
    }

    for(each car){
        pthread_create(car);
    }
    pthread_create(entry);
    pthread_create(exit);

    for(each car){
        pthread_join(car);
    }
    pthread_join(entry);
    pthread_join(exit);

    return 0;
}
