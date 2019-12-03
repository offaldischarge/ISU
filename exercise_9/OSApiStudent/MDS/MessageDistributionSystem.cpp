#include <MessageDistributionSystem.hpp>


void MessageDistributionSystem::subscribe(const std::string& msgId,
                                          osapi::MsgQueue* mq,
                                          unsigned long id)
{
    osapi::ScopedLock lock(m_);

    InsertResult ir = sm_.insert(std::make_pair(msgId, SubscriberIdContainer()));

    SubscriberIdContainer& sl = ir.first->second;

    details::SubscriberId s(mq, id);

    SubscriberIdContainer::iterator iter = find(sl.begin(), sl.end(), s);
    if(iter == sl.end()){
        sl.push_back(s);
    }
}


void MessageDistributionSystem::unSubscribe(const std::string& msgId,
                                            osapi::MsgQueue* mq,
                                            unsigned long id)
{
    osapi::ScopedLock lock(m_);

    SubscriberIdMap::iterator sim_it = sm_.find(msgId);

    if(sim_it != sm_.end()){
        SubscriberIdContainer& subList = sim_it->second;

        details::SubscriberId s(mq, id);

        SubscriberIdContainer::iterator iter;

        iter = find(subList.begin(), subList.end(), s);
        if(iter != subList.end()){
            subList.erase(iter);
        }
    }

}
