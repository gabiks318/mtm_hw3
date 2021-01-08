#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "date_wrap.h"
#include "base_event.h"

namespace mtm
{
    class EventContainer
    {
        List<BaseEvent> events;
        class EventIterator
        {
            typedef BaseEvent* iterator;
            public:
            EventIterator(BaseEvent* event);
            EventIterator(const EventIterator& iterator);
            EventIterator& operator=(const EventIterator& iterator);
            EventIterator& operator*();
            EventIterator operator++(int);
            bool operator==(const EventIterator& iterator1) const;
            bool operator!=(const EventIterator& iterator1) const;
            friend class EventContainer;
        };
        public:
        EventContainer(): events() {}
        virtual void add(const BaseEvent& event) = 0;//TO DO: what does it mean blocked adding event not suported?
        EventContainer::EventIterator begin();
        EventContainer::EventIterator end(); 
    };
}

#endif
