#ifndef SUBSCRIBER_HPP_
#define SUBSCRIBER_HPP_

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <Publisher.hpp>


/**
 * class Subsciber
 */
class Subscriber : public osapi::ThreadFunctor
{
public:
  enum { MAX_MSG_COUNT = 10 };
  Subscriber(unsigned int subId);
  ~Subscriber();

protected:
  // The subscription it self is missing and os is the unsubscription - Where will you put these?
  void handleMsgIdHello(HelloMsg* hm);
  void handleMsg(unsigned long id, osapi::Message* msg);
  virtual void run();

  bool                 running_;
  osapi::MsgQueue      mq_;

private:
  enum {
    ID_TERMINATE,
    ID_HELLO 
  };
  unsigned int subId_;
};

#endif

