#include <Publisher.hpp>
#include <MessageDistributionSystem.hpp>
#include <osapi/Log.hpp>

static const int MAX_QUEUE_SIZE=10;

Publisher::Publisher()
  : running_(true),
    mq_(MAX_QUEUE_SIZE),
    timer_(osapi::createNewTimer(&mq_, ID_TIME_OUT))
{
  OSAPI_LOG_DBG("Creating publisher with associated timer...");
}

Publisher::~Publisher()
{
  delete timer_;
  mq_.send(ID_TERMINATE);
}


void Publisher::handleMsgIdTimeOut()
{
  OSAPI_LOG_DBG("Got timeout, publishing message and rearming...");
  /************************************************/
  /************************************************/
  /* Write the necessary code to publish an event */
  /************************************************/
  /************************************************/
  
  timer_->reArm(); // Timeout in TIMEOUT msec
}

void Publisher::handleMsg(unsigned long id, osapi::Message* msg)
{
  switch(id)
  {
    case ID_TIME_OUT:
      handleMsgIdTimeOut();
      break;

    case ID_TERMINATE:
      running_ = false;
      break;

    default:
      OSAPI_LOG_DBG("Arg, got unknown event...");
      break;
  }
  
}


void Publisher::run()
{
  OSAPI_LOG_DBG("Preparing for loop, arming timer...");
  timer_->arm(TIMEOUT);

  while(running_)
  {
    unsigned long id;
    osapi::Message* m = mq_.receive(id);
    handleMsg(id, m);
    delete m;
  }

  OSAPI_LOG_DBG("Ensuring timers are stopped...");
  timer_->disArm();

  OSAPI_LOG_DBG("Thread terminating...");
}


