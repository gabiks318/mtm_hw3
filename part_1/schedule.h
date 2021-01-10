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
       

        void addEvents(EventContainer&);
        void registerToEvent(DateWrap date, string name, int student);
        void unregisterFromEvent(DateWrap date, string name, int student);
        void printAllEvents();
        template<typename predict>
        void printSomeEvents(predict, bool verbose = false);
        void printMonthEvents(int month, int year);
        void printEventDetails(string name, DateWrap date); 

        bool eventExists(const BaseEvent& event) const;       
    };
    template<typename predict>
    void printSomeEvents(predict, bool verbose = false)
    {

    }

}

#endif