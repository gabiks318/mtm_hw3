#include "../partB/base_event.h"
#include "../partB/closed_event.h"
#include "../partB/custom_event.h"
#include "../partA/date_wrap.h"
#include "../partB/event_container.h"
#include "../partA/exceptions.h"
#include "../partB/festival.h"
#include "../partB/one_time_event.h"
#include "../partB/open_event.h"
#include "../partB/recurring_event.h"
#include "../partC/schedule.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

void test_cover_date_wrap();
void test_cover_open_event();
void test_cover_closed_event();
void test_cover_custom_event();
void test_cover_festival();
void test_cover_recurring_event();
void test_cover_one_time_event();
void test_cover_schedule();

template <class T> void dump(const T& x) {
    std::stringstream s;
    s << x;
}

// partA

void test_cover_date_wrap() {
    try {
        mtm::DateWrap date(40, 200, 2000);
    } catch (mtm::InvalidDate&) {
    }
    mtm::DateWrap date(1, 1, 1);
    date.day();
    date.month();
    date.year();
    dump(date);
    date == date;
    date < date;
    date > date;
    date != date;
    date >= date;
    date <= date;
    date++;
    date += 2;
    date + 2;
    2 + date;
    try {
        date += (-3);
        date + (-3);
        (-3) + date;
    } catch (mtm::NegativeDays&) {
    }
}

// partB - single events

template <class T> void test_cover_event(T& e) {
    try {
        e.registerParticipant(4);
        e.registerParticipant(4);
        e.registerParticipant(30000);
    } catch (mtm::InvalidStudent&) {
    } catch (mtm::AlreadyRegistered&) {
    } catch (mtm::RegistrationBlocked&) {
    }

    try {
        e.unregisterParticipant(4);
        e.unregisterParticipant(30000);
    } catch (mtm::InvalidStudent&) {
    } catch (mtm::NotRegistered&) {
    }

    std::stringstream s;
    e.printShort(s);
    e.printLong(s);

    delete e.clone();
}

void test_cover_open_event() {
    mtm::OpenEvent e(mtm::DateWrap(1, 1, 1), "event");
    test_cover_event<mtm::OpenEvent>(e);
    test_cover_event<mtm::BaseEvent>(e);
}

void test_cover_closed_event() {
    mtm::ClosedEvent e(mtm::DateWrap(1, 1, 1), "event");
    try {
        e.addInvitee(4);
        e.addInvitee(4);
        e.addInvitee(30000);
    } catch (mtm::InvalidStudent&) {
    } catch (mtm::AlreadyInvited&) {
    }

    test_cover_event<mtm::ClosedEvent>(e);
    test_cover_event<mtm::BaseEvent>(e);
}

struct AlwaysTrue {
    bool operator()(int student) { return true; }
};

void test_cover_custom_event() {
    mtm::CustomEvent<AlwaysTrue> e(mtm::DateWrap(1, 1, 1), "event",
                                   AlwaysTrue());
    test_cover_event<mtm::CustomEvent<AlwaysTrue>>(e);
    test_cover_event<mtm::BaseEvent>(e);
}

template <class T> void test_cover_container(T& cnt) {
    try {
        cnt.add(mtm::OpenEvent(mtm::DateWrap(1, 1, 1), "event"));
    } catch (mtm::NotSupported&) {
    }

    std::stringstream s;
    for (mtm::EventContainer::EventIterator it = cnt.begin(); it != cnt.end();
         ++it) {
        mtm::BaseEvent& e = *it;
        e.printShort(s);
    }

    mtm::EventContainer::EventIterator it1 = cnt.begin();
    ++it1;
    mtm::EventContainer::EventIterator it2 = cnt.begin();
    mtm::EventContainer::EventIterator it3(it2);
    it2 = it1;
    it2 == it1;
}

void test_cover_festival() {
    mtm::Festival festival(mtm::DateWrap(1, 1, 1));
    try {
        festival.add(mtm::OpenEvent(mtm::DateWrap(2, 2, 2), "event"));
    } catch (mtm::DateMismatch&) {
    }
    test_cover_container<mtm::Festival>(festival);
    test_cover_container<mtm::EventContainer>(festival);
}

void test_cover_recurring_event() {
    mtm::RecurringEvent<mtm::OpenEvent> recurring(mtm::DateWrap(1, 1, 1),
                                                  "event", 2, 3);
    test_cover_container<mtm::RecurringEvent<mtm::OpenEvent>>(recurring);
    test_cover_container<mtm::EventContainer>(recurring);
    try {
        mtm::RecurringEvent<mtm::OpenEvent> recurring(mtm::DateWrap(1, 1, 1),
                                                      "event", 0, 0);
    } catch (mtm::InvalidNumber&) {
    } catch (mtm::InvalidInterval&) {
    }
}

void test_cover_one_time_event() {
    mtm::OneTimeEvent<mtm::OpenEvent> one_time(mtm::DateWrap(2, 2, 2), "event");
    test_cover_container<mtm::OneTimeEvent<mtm::OpenEvent>>(one_time);
    test_cover_container<mtm::EventContainer>(one_time);
}

void test_cover_schedule() {
    mtm::Schedule schedule;
    try {
        schedule.addEvents(
            mtm::OneTimeEvent<mtm::OpenEvent>(mtm::DateWrap(1, 1, 1), "event"));
        schedule.addEvents(
            mtm::OneTimeEvent<mtm::OpenEvent>(mtm::DateWrap(1, 1, 1), "event"));
    } catch (mtm::EventAlreadyExists&) {
    }

    try {
        schedule.registerToEvent(mtm::DateWrap(1, 1, 1), "event", 300);
        schedule.registerToEvent(mtm::DateWrap(2, 2, 2), "event", 400);
        schedule.unregisterFromEvent(mtm::DateWrap(1, 1, 1), "event", 300);
        schedule.unregisterFromEvent(mtm::DateWrap(2, 2, 2), "event", 400);
    } catch (mtm::EventDoesNotExist&) {
    }

    // don't need to cover print functions because they are already covered
}

int main() {
    try {
        test_cover_date_wrap();
        test_cover_open_event();
        test_cover_closed_event();
        test_cover_custom_event();
        test_cover_festival();
        test_cover_recurring_event();
        test_cover_one_time_event();
        test_cover_schedule();
    } catch (...) {
    }
    return 0;
}
