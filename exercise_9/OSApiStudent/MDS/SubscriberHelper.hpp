#ifndef SUBSCRIBER_HELPER_HPP_
#define SUBSCRIBER_HELPER_HPP_

#include <string>
#include <osapi/MsgQueue.hpp>

class SubscriberHelper
{
public:
  SubscriberHelper();
  SubscriberHelper(const std::string& msgId, osapi::MsgQueue* mq, unsigned long id);
  SubscriberHelper& operator=(SubscriberHelper& other);
  void unSubscribe();
  ~SubscriberHelper();
private:
  std::string      msgId_;
  osapi::MsgQueue* mq_;
  unsigned long    id_;  
};

#endif
