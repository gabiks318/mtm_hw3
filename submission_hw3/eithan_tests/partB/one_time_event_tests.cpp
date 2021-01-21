#include "../../partB/base_event.h"
#include "../../partB/closed_event.h"
#include "../../partB/custom_event.h"
#include "../../partB/open_event.h"
#include "../../partB/event_container.h"
#include "../../partA/exceptions.h"
#include "../../partB/recurring_event.h"
#include "../../partB/one_time_event.h"
#include "../../partA/date_wrap.h"
#include "../utilities.h"
#include <string>
#include <sstream>
#include <cassert>

using mtm::EventContainer;
using mtm::OneTimeEvent;
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
    OneTimeEvent<OpenEvent> ote1(DateWrap(21, 10, 2020), "Wednesday Noon");
    for(EventContainer::EventIterator it = ote1.begin(); it != ote1.end(); ++it){
        (*it).printShort(buff);
    }
    OneTimeEvent<ClosedEvent> ote2(DateWrap(20, 10, 2020), "Thursday Noon");
    for(EventContainer::EventIterator it = ote2.begin(); it != ote2.end(); ++it){
        (*it).printShort(buff);
    }
    OneTimeEvent<CustomEvent<Divisible2>> ote3(DateWrap(22, 10, 2020), "Friday Noon");
    for(EventContainer::EventIterator it = ote3.begin(); it != ote3.end(); ++it){
        (*it).printShort(buff);
    }
    compare_file_to_buffer(buff, "./outputs/ote_tests.txt");

    //add tests
    DateWrap date1(21,4,1999);
    DateWrap date2(21,8,2011);
    OpenEvent oe1(date1,"a My open birthday!");
    ClosedEvent ce1(date1, "c My Closed Birthday..");
    CustomEvent<Divisible2> cse1(date1, "b My Indie Alternative birthday", Divisible2());
    try{
        ote1.add(oe1);
        assert(0);
    } catch(NotSupported& ns) {}
    try{
        ote1.add(ce1);
        assert(0);
    } catch(NotSupported& ns) {}
    try{
        ote1.add(cse1);
        assert(0);
    } catch(NotSupported& ns) {}
}