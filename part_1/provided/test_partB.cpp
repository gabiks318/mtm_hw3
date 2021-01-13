#include "../base_event.h"
#include "../closed_event.h"
#include "../custom_event.h"
#include "../date_wrap.h"
#include "../event_container.h"
#include "../exceptions.h"
#include "../festival.h"
#include "../one_time_event.h"
#include "../open_event.h"
#include "../recurring_event.h"
#include <cstdlib>
#include <iostream>

typedef mtm::EventContainer::EventIterator Iter;

void printEventsShort(mtm::EventContainer& events) {
    for (Iter iter = events.begin(); iter != events.end(); ++iter) {

        mtm::BaseEvent& event = *iter;
        event.printLong(std::cout);
    }
}

void test1() {
    mtm::Festival festival(mtm::DateWrap(21, 10, 2020));
    festival.add(mtm::OpenEvent(mtm::DateWrap(21, 10, 2020), "YanB"));
    mtm::ClosedEvent closed(mtm::DateWrap(21, 10, 2020), "YanA");
    festival.add(closed);
    closed.addInvitee(1);
    closed.addInvitee(500);
    closed.registerParticipant(1);
    closed.registerParticipant(500);
    //festival.add(closed);
    printEventsShort(festival);
    // assume `ec` in an EventContainer with 2 events
    mtm::EventContainer& ec = festival;
    mtm::EventContainer::EventIterator it = ec.begin();
    mtm::EventContainer::EventIterator it_end = ec.end();
    mtm::BaseEvent& ev = *it; // `ev` is the first event stored in `ec`
    ev.printShort(std::cout); // print short description of 1st event
    (*it).printShort(std::cout); // same output as previous line
    ++it;
    (*it).printShort(std::cout); // print short description of 2nd event
    std::cout << (it == it_end) << std::endl; // print "0"
    std::cout << (it != it_end) << std::endl; // print "1"
    ++it;
    std::cout << (it == it_end) << std::endl; // print "1"
    std::cout << (it != it_end) << std::endl;
    mtm::RecurringEvent<mtm::OpenEvent> recurring(mtm::DateWrap(21, 10, 2020),
                                               "Wednesday Noon", 13, 7);
    printEventsShort(recurring);

    mtm::OneTimeEvent<mtm::OpenEvent> one_time(mtm::DateWrap(2, 3, 80),
                                               "A long time ago");
    printEventsShort(one_time);
    std::cout<< "finished first test \n" << std::endl;
}

void test2_aux(mtm::BaseEvent& event) {
    event.registerParticipant(1);
    /* event.registerParticipant(20000); */
    event.unregisterParticipant(1);
    /* event.registerParticipant(3); */
    mtm::BaseEvent* clone = event.clone();
    clone->printShort(std::cout);
    clone->printLong(std::cout);
    delete clone;
}

struct StudentFilter {
    bool operator()(int student) {
        return student == 1 || student == 3 || student == 20000;
    }
};

void test2() {
    /* mtm::OpenEvent open(mtm::DateWrap(21, 10, 2020), "An Open Event");
    test2_aux(open); */
    mtm::ClosedEvent closed(mtm::DateWrap(21, 10, 2020), "A Closed Event");
    closed.addInvitee(2);
    closed.addInvitee(4);
    closed.addInvitee(1);
    closed.registerParticipant(2);
    closed.registerParticipant(4);
    closed.registerParticipant(1);
    closed.printLong(cout);
    /* test2_aux(closed); */
    /* mtm::CustomEvent<StudentFilter> custom(mtm::DateWrap(21, 10, 2020),
                                           "A Custom Event", StudentFilter());
    test2_aux(custom); */
}

typedef void (*Test)();
const Test tests[] = {test1, test2};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        test1();
        test2();
    } else if (argc > 2) {
        std::cout << "invalid arguments" << std::endl;
    } else {
        int i = std::atoi(argv[1]);
        tests[i - 1]();
    }
    return 0;
}
