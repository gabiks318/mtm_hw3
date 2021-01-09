#include "event_container.h"
#include "./linked_list/linked_list.h"
#include "exceptions.h"
#include "base_event.h"

using mtm::EventContainer;


EventContainer::EventIterator::EventIterator(List<BaseEvent*> events, int index): event(), index(index), events(events)
{
    if(index == events.getSize())
    {
        event = nullptr;
        return;
    }
    event = events[index];        
}

EventContainer::EventIterator::EventIterator(const EventIterator& event_iterator){
    event = event_iterator.event;
    index = event_iterator.index;
    events = event_iterator.events;
}
EventContainer::EventIterator& EventContainer::EventIterator::operator=(const EventIterator& event_iterator){
    if(*this == event_iterator){
        return *this;
    }
    delete &events;
    delete &event;
    event = event_iterator.event;
    index = event_iterator.index;
    events = event_iterator.events;
    return *this;
}
mtm::BaseEvent& EventContainer::EventIterator::operator*(){
    return *event;
}

EventContainer::EventIterator& EventContainer::EventIterator::operator++(){
    index++;
    if(index == events.getSize()){
        event = nullptr;
        return *this;
    }
    event = events[index];
    return *this;
}

bool EventContainer::EventIterator::operator==(const EventIterator& event_iterator) const{
    return *event == *event_iterator.event;
}
bool EventContainer::EventIterator::operator!=(const EventIterator& event_iterator) const{
    return !(event == event_iterator.event);
}
   
EventContainer::EventIterator EventContainer::begin(){
    return EventIterator(events, 0);
}
EventContainer::EventIterator EventContainer::end(){
    int size = events.getSize();
    return EventIterator(events, size);
}