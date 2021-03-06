#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "date_wrap.h"
#include "base_event.h"

namespace mtm
{   
    
    class EventContainer
    {
        protected:
        
        class CompareEvents{
        public:
        bool operator()(const BaseEvent* event1, const BaseEvent* event2){
            return *event1 < *event2;
            }
        };
        List<BaseEvent*, CompareEvents> events;

        public:
        class EventIterator
        {
            int index;
            List<BaseEvent*, CompareEvents> events;
            
            public:
            EventIterator(List<BaseEvent*, CompareEvents> events, int index);
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
