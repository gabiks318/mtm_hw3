#include "base_event.h"
#include "exceptions.h"
#include "open_event.h"

using mtm::BaseEvent;
using mtm::OpenEvent;
using mtm::List;

OpenEvent::OpenEvent(DateWrap date, string name):BaseEvent(date,name){

}

OpenEvent::OpenEvent(const OpenEvent& event):BaseEvent(event){

}

OpenEvent& OpenEvent::operator=(const OpenEvent& event)
{
   if(this == &event){
        return *this;
    }
    delete &name;
    delete &date;
    delete &participants;
    name = *(new string(event.name));
    date = *(new DateWrap(event.date));
    participants = *(new List<int>(event.participants));
    return *this;
}

BaseEvent* OpenEvent::clone() const
{
    return new OpenEvent(*this);
}