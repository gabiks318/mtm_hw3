#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "event_container.h"
#include "./linked_list/linked_list.h"
#include <list> 

using std::list;

namespace mtm
{
    class Schedule
    {
        list<BaseEvent*> events_list;
        public:
        Schedule();
       
        void addEvents(const EventContainer&);
        void registerToEvent(DateWrap date, string name, int student);
        void unregisterFromEvent(DateWrap date, string name, int student);
        void printAllEvents() const;
        template<typename Predicate>
        void printSomeEvents(Predicate predicate, bool verbose = false) const;
        void printMonthEvents(int month, int year) const;
        void printEventDetails(DateWrap date, string name) const; 
    };

    template<typename Predicate>
    void Schedule::printSomeEvents(Predicate predicate, bool verbose) const
    {
        for(mtm::BaseEvent* event : events_list){
            if(predicate(*event)){
                if(verbose){
                    event->printLong(std::cout);
                } else {
                    event->printLong(std::cout);
                }
            }
        }
    }

}

#endif