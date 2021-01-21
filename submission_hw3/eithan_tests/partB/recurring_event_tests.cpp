#include "base_event.h"
#include "closed_event.h"
#include "custom_event.h"
#include "open_event.h"
#include "event_container.h"
#include "../partA/exceptions.h"
#include "recurring_event.h"
#include "../partA/date_wrap.h"
#include "../utilities.h"
#include <sstream>
#include <cassert>

using mtm::EventContainer;
using mtm::RecurringEvent;
using mtm::BaseEvent;
using mtm::OpenEvent;
using mtm::ClosedEvent;
using mtm::CustomEvent;
using mtm::DateWrap;
using std::ostringstream;
using mtm::compare_file_to_buffer;
using mtm::Divisible2;

int main() {
    //iterator and constructor tests
    ostringstream buff;
    RecurringEvent<OpenEvent> recurring1(DateWrap(21, 10, 2020), "Wednesday Noon", 2, 7);
    for(EventContainer::EventIterator it = recurring1.begin(); it != recurring1.end(); ++it){
        (*it).printShort(buff);
    }
    RecurringEvent<ClosedEvent> recurring2(DateWrap(20, 10, 2020), "Thursday Noon", 2, 7);
    for(EventContainer::EventIterator it = recurring2.begin(); it != recurring2.end(); ++it){
        (*it).printShort(buff);
    }
    RecurringEvent<CustomEvent<Divisible2>> recurring3(DateWrap(22, 10, 2020), "Friday Noon", 2, 7);
    for(EventContainer::EventIterator it = recurring3.begin(); it != recurring3.end(); ++it){
        (*it).printShort(buff);
    }
    compare_file_to_buffer(buff, "./outputs/recurring_event_tests.txt");

    //add tests
    DateWrap date1(21,4,1999);
    DateWrap date2(21,8,2011);
    OpenEvent oe1(date1,"a My open birthday!");
    ClosedEvent ce1(date1, "c My Closed Birthday..");
    CustomEvent<Divisible2> cse1(date1, "b My Indie Alternative birthday", Divisible2());
    try{
        recurring1.add(oe1);
        assert(0);
    } catch(NotSupported& ns) {}
    try{
        recurring1.add(ce1);
        assert(0);
    } catch(NotSupported& ns) {}
    try{
        recurring1.add(cse1);
        assert(0);
    } catch(NotSupported& ns) {}
}