#ifndef MESSAGE_DISTRIBUTION_SYSTEM_HPP_
#define MESSAGE_DISTRIBUTION_SYSTEM_HPP_

#include <vector>
#include <map>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>
#include <osapi/ScopedLock.hpp>
#include <osapi/MsgQueue.hpp>

#include <SubscriberId.hpp>


class MessageDistributionSystem : osapi::Notcopyable
{
public:
  /** Subscribes to the message that is globally unique and designated
   *  in msgId  
   * msgId Globally unique message id, the one being subscribed to
   * mq    The message queue to receive a given message once one is 
   *       send to the msgId.
   * id    The receiver chosen id for this particular message
   */
  void subscribe(const std::string& msgId, 
                 osapi::MsgQueue* mq, 
                 unsigned long id);  
  
  /** Unsubscribes to the message that is globally unique and designated in msgId  
   * msgId Globally unique message id, the one being subscribed to
   * mq    The message queue that received message designated by msgId.
   * id    The receiver chosen id for this particular message
   */
  void unSubscribe(const std::string& msgId, 
                   osapi::MsgQueue* mq, 
                   unsigned long id);

  /** All subscribers are notified
   * whereby they receive the message designated with 'm' below.
   * msgId Globally unique message identifier
   * m     Message being send 
   */ 
  template<typename M>
  void notify(const std::string& msgId, M* m) const
  {
    osapi::ScopedLock lock(m_);
    SubscriberIdMap::const_iterator iter = sm_.find(msgId);
    if(iter != sm_.end()) // Found entries
    {
      const SubscriberIdContainer& subList = iter->second; // Why?

      for(SubscriberIdContainer::const_iterator iterSubs = 
      subList.begin(); iterSubs != subList.end(); ++iterSubs)
      {
        M *tmp = new M(*m); // <-- This MUST be explained!
        iterSubs->send(tmp);
      }
    }
    delete m; // <- WHY? Could be more efficient implemented, 
    // such that this de-allocation would be unnecessarily. Explain!
  }

  // Making it a singleton
  static MessageDistributionSystem& getInstance()
  {
    static MessageDistributionSystem mds;
    return mds;
  }
  

private:
  // Constructor is private
  MessageDistributionSystem() {} 

  // Some form af key value pair, where value is signified by 
  //  the msgId and the value is a list of subscribers
  
  typedef std::vector<details::SubscriberId>  SubscriberIdContainer;
  typedef std::map<std::string, SubscriberIdContainer> SubscriberIdMap;
  typedef std::pair<SubscriberIdMap::iterator, bool>   InsertResult;
  SubscriberIdMap         sm_;
  mutable osapi::Mutex    m_;
};


#endif
