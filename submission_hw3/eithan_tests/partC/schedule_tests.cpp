#include "schedule.h"
#include "../utilities.h"
#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include "../partB/sorted_list.h"
#include "../partB/base_event.h"
#include "../partB/open_event.h"
#include "../partB/closed_event.h"
#include "../partB/one_time_event.h"
#include "../partB/custom_event.h"
#include "../partB/event_container.h"
#include "../partB/festival.h"
#include "../partB/recurring_event.h"
#include <cassert>
#include <sstream>
using std::ostringstream;

using std::string;
using std::cout;
using mtm::DateWrap;
using mtm::Schedule;
using mtm::Festival;
using mtm::RecurringEvent;
using mtm::OpenEvent;
using mtm::ClosedEvent;
using mtm::CustomEvent;
using mtm::OneTimeEvent;
using mtm::compare_file_to_buffer;

struct Divisible2 {
	bool operator()(int num) {
		return (num % 2 == 0);
	}
};

bool predicateNameS(const BaseEvent& event) {
	ostringstream buf;
	event.printShort(buf);
	return buf.str()[0] == 'S';
}


void staffTests() {
	ostringstream buf;
	mtm::Schedule schedule;
    schedule.addEvents(mtm::OneTimeEvent<mtm::OpenEvent>(
        mtm::DateWrap(27, 12, 2020), "Publish Test"));

    mtm::RecurringEvent<mtm::ClosedEvent> closed(mtm::DateWrap(20, 12, 2020),
                                                 "Update Q&A", 6, 5);
    for (mtm::BaseEvent& event : closed) {
        mtm::ClosedEvent& closed_event = dynamic_cast<mtm::ClosedEvent&>(event);
        closed_event.addInvitee(1337);
        closed_event.addInvitee(850);
        closed_event.addInvitee(1500);
    }
    schedule.addEvents(closed);

    schedule.registerToEvent(mtm::DateWrap(20, 12, 2020), "Update Q&A", 850);
    schedule.registerToEvent(mtm::DateWrap(20, 12, 2020), "Update Q&A", 1500);
    schedule.registerToEvent(mtm::DateWrap(5, 1, 2021), "Update Q&A", 850);
    schedule.registerToEvent(mtm::DateWrap(5, 1, 2021), "Update Q&A", 1500);
    schedule.unregisterFromEvent(mtm::DateWrap(20, 12, 2020), "Update Q&A",
                                 1500);
	
	schedule.printAllEvents(buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test1.txt");
    schedule.printEventDetails(mtm::DateWrap(27, 12, 2020), "Publish Test", buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test2.txt");
    schedule.printEventDetails(mtm::DateWrap(5, 1, 2021), "Update Q&A", buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test3.txt");
	schedule.printMonthEvents(12, 2020, buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test4.txt");

	class MutatingPredicate {
		int counter = 0;

	public:
		bool operator()(const mtm::BaseEvent& event) {
			++counter;
			return true;
		}
	};
	schedule.printSomeEvents(MutatingPredicate(), true, buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test5.txt");
}

void addTests() {
	Schedule* s = new Schedule();
	DateWrap my_date1(16, 1, 2021);
	Festival f(my_date1);
	f.add(OpenEvent(my_date1, "Event 1"));
	s->addEvents(f);
	f.add(OpenEvent(my_date1, "Event 2"));
	try {
		s->addEvents(f);
		assert(0);
	} catch (mtm::EventAlreadyExists& e) {}
	DateWrap earlier_date(12, 1, 2021);
	RecurringEvent<OpenEvent> re(earlier_date, "Recurring Open Event", 3, 5);
	s->addEvents(re);
	// s->printAllEvents();
	delete s;
}

void registerUnregisterTests() {
	Schedule* s = new Schedule();
	DateWrap my_date1(16, 1, 2021);
	DateWrap earlier_date(12, 1, 2021);
	Festival f(my_date1);
	f.add(OpenEvent(my_date1, "Event 1"));
	f.add(ClosedEvent(my_date1, "Closed Event"));
	OneTimeEvent<CustomEvent<Divisible2>> divisible(earlier_date, "For even only");
	s->addEvents(f);
	s->addEvents(divisible);
	try {
		s->registerToEvent(my_date1, "Event 1", 0);
		assert(0);
	} catch (mtm::InvalidStudent& e) {}
	try {
		s->registerToEvent(my_date1, "Event 2", 1);
		assert(0);
	} catch (mtm::EventDoesNotExist& e) {}
	s->registerToEvent(my_date1, "Event 1", 532);
	try {
		s->registerToEvent(my_date1, "Event 1", 532);
		assert(0);
	} catch (mtm::AlreadyRegistered& e) {}
	try {
		s->registerToEvent(my_date1, "Closed Event", 24);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}
	try {
		s->registerToEvent(earlier_date, "For even only", 23);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}
	try {
		s->unregisterFromEvent(my_date1, "For even only", 23);
		assert(0);
	} catch (mtm::EventDoesNotExist&) {}
	try {
		s->unregisterFromEvent(earlier_date, "For even only", 23);
		assert(0);
	} catch (mtm::NotRegistered&) {}
	try {
		s->unregisterFromEvent(my_date1, "Event 1", 0);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	s->unregisterFromEvent(my_date1, "Event 1", 532);
	try {
		s->unregisterFromEvent(my_date1, "Event 1", 532);
		assert(0);
	} catch (mtm::NotRegistered&) {}
	delete s;
}

void bigTest() {
	Schedule* s = new Schedule();
	RecurringEvent<ClosedEvent> meeting_5g(DateWrap(15, 1, 2020), "Monthly 5G Community Meeting", 12, 30);
	for (BaseEvent& event : meeting_5g) {
		ClosedEvent& ce = dynamic_cast<ClosedEvent&>(event);
		ce.addInvitee(666);
		ce.addInvitee(420);
		ce.addInvitee(1337);
	}
	s->addEvents(meeting_5g);
	for (BaseEvent& event : meeting_5g) {
		int month = event.getDate().month();
		if (month % 2 == 0) {s->registerToEvent(event.getDate(), "Monthly 5G Community Meeting", 420);}
		else if (month % 3 == 0) {s->registerToEvent(event.getDate(), "Monthly 5G Community Meeting", 1337);}
		if (month % 4 == 0) {
			s->unregisterFromEvent(event.getDate(), "Monthly 5G Community Meeting", 420);
			s->registerToEvent(event.getDate(), "Monthly 5G Community Meeting", 666);
		}
	}
	OneTimeEvent<CustomEvent<Divisible2> > summer_pool_party(DateWrap(15, 7, 2020), "Summer Pool Party");
	s->addEvents(summer_pool_party);
	RecurringEvent<OpenEvent> july_hackathon(DateWrap(14, 7, 2020), "July Hackathon", 3, 1);
	s->addEvents(july_hackathon);
	s->registerToEvent(DateWrap(15, 7, 2020), "Summer Pool Party", 100);
	s->registerToEvent(DateWrap(15, 7, 2020), "Summer Pool Party", 200);
	s->registerToEvent(DateWrap(15, 7, 2020), "Summer Pool Party", 300);
	s->registerToEvent(DateWrap(14, 7, 2020), "July Hackathon", 14);
	s->registerToEvent(DateWrap(15, 7, 2020), "July Hackathon", 15);
	s->registerToEvent(DateWrap(16, 7, 2020), "July Hackathon", 16);
	Festival midspring_festival(DateWrap(15, 3, 2020));
	try {
		midspring_festival.add(OpenEvent(DateWrap(16, 3, 2020), "Static&Ben el"));
		assert(0);
	} catch (mtm::DateMismatch&) {}
	midspring_festival.add(OpenEvent(DateWrap(15, 3, 2020), "Static&Ben el"));
	midspring_festival.add(OpenEvent(DateWrap(15, 3, 2020), "Inflatables"));
	midspring_festival.add(OpenEvent(DateWrap(15, 3, 2020), "Free Infi2 tests"));
	for (BaseEvent& event : midspring_festival) {
		OpenEvent& ce = dynamic_cast<OpenEvent&>(event);
		for (int i=1; i<11; i++) {
			ce.registerParticipant(i);
		}
	}
	s->addEvents(midspring_festival);
	ostringstream buf;
	s->printAllEvents(buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test6.txt");
	s->printMonthEvents(1, 2019, buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test7.txt");
	s->printMonthEvents(7, 2020, buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test8.txt");

	s->printSomeEvents(predicateNameS, true, buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test9.txt");

	s->printSomeEvents(predicateNameS, false, buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test10.txt");

	s->printEventDetails(DateWrap(15, 3, 2020), "Static&Ben el", buf);
	compare_file_to_buffer(buf, "~/mtm/ex3/outputs/partC_test11.txt");

	delete s;
}

int main() {
	staffTests();
	addTests();
	registerUnregisterTests();
	bigTest();

	return 0;
}