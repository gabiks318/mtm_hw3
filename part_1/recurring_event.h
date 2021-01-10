#ifndef RECURRING_EVENT_H
#define RECURRING_EVENT_H

#include "event_container.h"
#include "base_event.h"
#include "exceptions.h"
#include "date_wrap.h"
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
        DateWrap* date = new DateWrap(first_date);
        EventType* current_event = new EventType(*date, name);
        for(int i = 0; i < num_occurrences; i++){
            events.insert(current_event);
            date = new DateWrap(first_date + (i+1)*interval);
            current_event = new EventType(*date, name);
        }
    }

    template<class EventType>
    void RecurringEvent<EventType>::add(const BaseEvent& event)
    {
        throw NotSupported();
    }
}


#endif