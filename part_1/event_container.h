#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "date_wrap.h"
#include "base_event.h"

namespace mtm
{
    class EventContainer
    {
        protected:
        class ComparePointerToEvents{
            public:
            bool operator()(const BaseEvent*,const BaseEvent*);
        };
        List<BaseEvent*,ComparePointerToEvents> events;
        
        public:
        class EventIterator
        {
            BaseEvent* event;
            int index;
            List<BaseEvent*,ComparePointerToEvents> events;
            
            public:
            EventIterator(List<BaseEvent*,ComparePointerToEvents> events, int index);
            EventIterator(const EventIterator& event_iterator);
            EventIterator& operator=(const EventIterator& event_iterator);
            ~EventIterator() = default;

            mtm::BaseEvent& operator*();
            EventIterator& operator++();
            bool operator==(const EventIterator& event_iterator) const;
            bool operator!=(const EventIterator& event_iterator) const;
            friend class EventContainer;
        };

        EventContainer();
        virtual ~EventContainer();

        virtual void add(const BaseEvent& event) = 0;//TODO: what does it mean blocked adding event not suported?
        EventIterator begin() const;
        EventIterator end() const; 
    };
}

#endif
