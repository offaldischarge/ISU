#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Timer.hpp>

/** Global message Hello
 */
struct HelloMsg : public osapi::Message
{
  std::string data_;
};
const std::string HELLO_MSG;


class Publisher : public osapi::ThreadFunctor
{
public:
  Publisher();
  ~Publisher();
private:
  void handleMsgIdTimeOut();
  void handleMsg(unsigned long id, osapi::Message* msg);
  virtual void run();
  
  bool                 running_;
  osapi::MsgQueue      mq_;
  osapi::ITimerId*     timer_;
  
  enum { ID_TIME_OUT,
         ID_TERMINATE 
  };

  enum { TIMEOUT = 1000 };
};


#endif
