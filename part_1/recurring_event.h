#ifndef RECURRING_EVENT_H
#define RECURRING_EVENT_H

#include "event_container.h"
#include "base_event.h"
#include "exceptions.h"
#include "./linked_list/linked_list.h"
#include <string>

namespace mtm
{
    template<class EventType>
    class RecurringEvent: public EventContainer
    {
        public:
        RecurringEvent(DateWrap first_date, string name, int num_occurrences, int interval);
        ~RecurringEvent() = default;
        void add(const BaseEvent& event) override;
    };
    //==============Implementation==========//
    template<class EventType>
    RecurringEvent<EventType>::RecurringEvent(DateWrap first_date, string name, int num_occurrences, int interval):EventContainer()
    {
        if(num_occurrences <= 0){
            throw InvalidNumber();
        }
        if(interval <= 0){
            throw InvalidInterval();
        }
        EventType event();
        
        for(int i = 0; i < num_occurrences; i++){
            event(first_date + i*interval, name);
            events.insert(event);
        }
    }
    template<class EventType>
    void RecurringEvent<EventType>::add(const BaseEvent& event)
    {
        throw NotSupported();
    }
}


#endif