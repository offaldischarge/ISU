#ifndef SUBSCRIBER_ID_HPP_
#define SUBSCRIBER_ID_HPP_

#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>
#include <osapi/MsgQueue.hpp>


namespace details 
{
  /** Container for each subscriber, that holds relevant 
   *  information that uniquely identifies a subscriber 
   *  and ensures that when a message is send to the 
   *  subscriber, it is done as per the subscriber requirements.
   */
  class SubscriberId
  {
  public:
    SubscriberId(osapi::MsgQueue* mq_, unsigned long id_);
    
    /** Send the message to the subscriber
     */
    void send(osapi::Message* m) const;

    /** Used to find subscribers in the vector
     */
    bool operator==(const SubscriberId& other) const
    { 
      return (mq_ == other.mq_) && (id_ == other.id_); 
    }
  private:
    osapi::MsgQueue*  mq_;
    unsigned long     id_;
  };
}


#endif
