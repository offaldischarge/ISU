#ifndef PLCSMESSAGES_H_
#define PLCSMESSAGES_H_

struct EntryDoorOpenRequest : public osapi::Message {
    osapi::MsgQueue* whoIsAskingMq;
};

struct ExitDoorOpenRequest : public osapi::Message {
    osapi::MsgQueue* whoIsAskingMq;
};

struct EntryDoorOpenConfirm : public osapi::Message {
    bool result;
};

struct ExitDoorOpenConfirm : public osapi::Message {
    bool result;
};


#endif
