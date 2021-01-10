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
    events.insert(event.clone());
}
