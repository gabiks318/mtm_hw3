#include "festival.h"
#include "exceptions.h"
#include "./linked_list/linked_list.h"

using mtm::Festival;


Festival::Festival(DateWrap date): EventContainer(), date(date){   
}

void Festival::add(const BaseEvent& event)
{
    if(event.getDate() != date){
        throw DateMismatch();
    }
    BaseEvent* event_clone;
    try{
        event_clone = event.clone();
    } catch(std::bad_alloc& e){
        for(int i = 0; i < events.getSize(); i++){
            delete events[i];
        }    
        throw e;
    }
    try{
        events.insertPointer(event_clone);
    } catch(std::bad_alloc& e){
        delete event_clone;
        for(int i = 0; i < events.getSize(); i++){
            delete events[i];
        }    
        throw e;
    } 
}
