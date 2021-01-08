#include "event_container.h"
#include "./linked_list/linked_list.h"
#include "exceptions.h"
#include "base_event.h"

using mtm::EventContainer;

EventContainer::EventIterator::EventIterator(BaseEvent* event):iterator(event){}


EventContainer::EventIterator::EventIterator(const EventIterator& iterator){

}
EventIterator& EventContainer::EventIterator::operator=(const EventIterator& iterator){

}
EventIterator& EventContainer::EventIterator::operator*(){

}
EventIterator EventContainer::EventIterator::operator++(int){

}
bool EventContainer::EventIterator::operator==(const EventIterator& iterator) const{

}
bool EventContainer::EventIterator::operator!=(const EventIterator& iterator) const{

}
   
EventContainer::EventIterator EventContainer::begin(){
    return EventContainer::EventIterator(events[0]);
}
EventContainer::EventIterator EventContainer::end(){
    return EventContainer::EventIterator(events[getSize(events)]);
}