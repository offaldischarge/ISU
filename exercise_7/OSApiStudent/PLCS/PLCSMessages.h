#ifndef PLCSMESSAGES_H_
#define PLCSMESSAGES_H_

class Car; //Forward declaration

struct EntryDoorOpenRequest : public osapi::Message {
    Car* car;
};

struct ExitDoorOpenRequest : public osapi::Message {
    Car* car;
};

struct EntryDoorOpenConfirm : public osapi::Message {
    bool result;
};

struct ExitDoorOpenConfirm : public osapi::Message {
    bool result;
};


#endif
