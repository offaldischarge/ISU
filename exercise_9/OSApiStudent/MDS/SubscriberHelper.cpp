#include <SubscriberHelper.hpp>


SubscriberHelper::SubscriberHelper()
  : mq_(NULL), id_(0)
{
}


SubscriberHelper::SubscriberHelper(const std::string& msgId, osapi::MsgQueue* mq, unsigned long id)
  : msgId_(msgId), mq_(mq), id_(id)
{
  /* Missing code */
}




SubscriberHelper& SubscriberHelper::operator=(SubscriberHelper& other)
{
  unSubscribe(); // Unsubscribe, if we have subscription
  msgId_ = other.msgId_;
  mq_    = other.mq_;
  id_    = other.id_;
  other.mq_ = NULL; // Destructive copy

  return *this;
}


void SubscriberHelper::unSubscribe()
{
  /* Missing code */
}


SubscriberHelper::~SubscriberHelper()
{
  /* Missing code */
}
