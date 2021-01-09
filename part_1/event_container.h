#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "date_wrap.h"
#include "base_event.h"

namespace mtm
{
    class EventContainer
    {
        protected:
        List<BaseEvent*> events;
        
        public:
        class EventIterator
        {
            BaseEvent* event;
            int index;
            List<BaseEvent*> events;
            public:
            int getIndex() const;
            EventIterator(List<BaseEvent*> events, int index);
            EventIterator(const EventIterator& event_iterator);
            EventIterator& operator=(const EventIterator& event_iterator);
            mtm::BaseEvent& operator*();
            EventIterator& operator++();
            bool operator==(const EventIterator& event_iterator) const;
            bool operator!=(const EventIterator& event_iterator) const;
            friend class EventContainer;
        };
        EventContainer(): events() {}
        virtual ~EventContainer() = default;
        virtual void add(const BaseEvent& event) = 0;//TODO: what does it mean blocked adding event not suported?
        EventIterator begin();
        EventIterator end(); 
    };
}

#endif
