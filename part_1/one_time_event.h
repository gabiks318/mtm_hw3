#ifndef ONE_TIME_EVENT_H
#define ONE_TIME_EVENT_H

#include "event_container.h"
#include "base_event.h"
#include "exceptions.h"
#include "./linked_list/linked_list.h"
#include <string>

namespace mtm
{
    template<class EventType>
    class OneTimeEvent: public EventContainer
    {
    public:
        OneTimeEvent(DateWrap date, string name);
        ~OneTimeEvent();
        
        void add(const BaseEvent& event) override;
    };

    //==============Implementation==========//


    template<class EventType>
    OneTimeEvent<EventType>::OneTimeEvent(DateWrap date, string name):EventContainer()
    {
        EventType* current_event = new EventType(date,name);
        events.insert(current_event);
    }

    
    template<class EventType>
    OneTimeEvent<EventType>::~OneTimeEvent()
    {
        events.ListPointerDelete();
    }

    template<class EventType>
    void OneTimeEvent<EventType>::add(const BaseEvent& event)
    {
        throw NotSupported();
    }
}

#endif