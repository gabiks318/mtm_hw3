#include "schedule.h"
#include <list>
#include "event_container.h"
#include "exceptions.h"

using mtm::Schedule;


Schedule::Schedule(): events_list(){}

void Schedule::addEvents(EventContainer& events)
{
    for(mtm::EventContainer::EventIterator events_iterator = events.begin(); events_iterator!= events.end(); ++events_iterator){
        mtm::BaseEvent& event = *events_iterator;
        if(eventExists(event)){
            throw EventAlreadyExists();
        }
        events_list.push_back(&event);    
    }
    events_list.sort();
}

bool Schedule::eventExists(const mtm::BaseEvent& event) const
{
    for(std::list<BaseEvent*>::iterator it = events_list.begin(); it != events_list.end(); ++it){
        if(*it == event){
            return true;
        }
    }

}

void Schedule::registerToEvent(DateWrap date, string name, int student)
{ 
    // TODO: Should the function catch the student id exceptions or let event class handle it
    for(std::list<BaseEvent*>::iterator iterator = events_list.begin(); iterator != events_list.end(); ++iterator){
        mtm::BaseEvent& event = *iterator;
        if(event.getName() == name && event.getDate() == date){
            event.registerParticipant(student);
            return;
        }
    }
    throw EventDoesNotExists();    
}

void Schedule::unregisterFromEvent(DateWrap date, string name, int student)
{

}

void Schedule::printAllEvents()
{

}

void Schedule::printMonthEvents(int month, int year)
{

}

void Schedule::printEventDetails(string name, DateWrap date)
{

}