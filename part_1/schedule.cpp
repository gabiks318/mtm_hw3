#include "schedule.h"
#include <list>
#include "event_container.h"
#include "exceptions.h"
#include <algorithm>
using mtm::Schedule;

#define MIN_MONTH 1
#define MAX_MONTH 12

Schedule::Schedule(): events_list(){}

void Schedule::addEvents(EventContainer& events)
{
    for(mtm::EventContainer::EventIterator events_iterator = events.begin(); events_iterator!= events.end(); ++events_iterator){
        mtm::BaseEvent& event = *events_iterator;
        if((std::find(events_list.begin(), events_list.end(), &event) != events_list.end())){
            throw EventAlreadyExists();
        }
        events_list.push_back(&event);    
    }
    events_list.sort();
}

void Schedule::registerToEvent(DateWrap date, string name, int student)
{ 
    // TODO: Should the function catch the student id exceptions or let event class handle it
    for(mtm::BaseEvent* event : events_list){
        if(event->getName() == name && event->getDate() == date){
            event->registerParticipant(student);
            return;
        }
    }
    throw EventDoesNotExists();    
}

void Schedule::unregisterFromEvent(DateWrap date, string name, int student)
{
    for(mtm::BaseEvent* event : events_list){
        if(event->getName() == name && event->getDate() == date){
            event->unregisterParticipant(student);
            return;
        }
    }
    throw EventDoesNotExists(); 
}

void Schedule::printAllEvents()
{
    for(mtm::BaseEvent* event : events_list){
        event->printShort(std::cout);
    }    
}



void Schedule::printMonthEvents(int month, int year)
{
    if(month < MIN_MONTH || month > MAX_MONTH){
        // TODO: check what to do here
        throw InvalidDate();
    }

    
    for(mtm::BaseEvent* event : events_list){
        DateWrap date = event->getDate();
        if(date.month() == month && date.year() == year){
            event->printShort(std::cout);
        }
    }  
}

void Schedule::printEventDetails(string name, DateWrap date)
{
    for(mtm::BaseEvent* event : events_list){
        if(event->getName() == name && event->getDate() == date){
            event->printLong(std::cout);
            break;
        }
    }    
}
