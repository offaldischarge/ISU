#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <osapi/MsgQueue.hpp>
#include <osapi/ThreadFunctor.hpp>

class MessageHandler : public osapi::Thread
{
public:
  MessageHandler(unsigned long count, unsigned long stopId)
    : mq_(count), running_(true), stopId_(stopId) {}
  
  osapi::MsgQueue* getMsgQueue()
  {
    return &mq_;
  }
  
  void stop()
  {
    mq_.send(stopId_);
  }
  
  
protected:  
  void run()
  {
    preMsgHandler();
    while(running_)
    {
      unsigned long id;
      osapi::Message* m = mq_.receive(id);
      if(id == stopId_)
        running_ = false;
      handleMsg(m, id);
      delete m;
    }
    postMsgHandler();
  }
  

  virtual void preMsgHandler() {}
  virtual void handleMsg(osapi::Message*& msg, unsigned long id) = 0;
  virtual void postMsgHandler() {}
  
private:
  osapi::MsgQueue   mq_;
  unsigned long     stopId_;
  bool              running_;
};
