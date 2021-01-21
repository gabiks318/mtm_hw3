#include "../../partB/base_event.h"
#include "../../partB/closed_event.h"
#include "../../partB/custom_event.h"
#include "../../partB/open_event.h"
#include "../../partB/event_container.h"
#include "../../partA/exceptions.h"
#include "../../partB/recurring_event.h"
#include "../../partB/one_time_event.h"
#include "../../partB/festival.h"
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
using mtm::compare_and_clear;
using mtm::Divisible2;
using mtm::Festival;
using std::cout;

void polymorphismTest() {
	BaseEvent* event_array[3];
	ostringstream buf;
	event_array[0] = new OpenEvent(DateWrap(19,1,2021), "Open");
	event_array[1] = new ClosedEvent(DateWrap(20,1,2021), "Closed");
	event_array[2] = new CustomEvent<Divisible2>(DateWrap(21,1,2021), "Custom");
	event_array[0]->registerParticipant(1);
	try {
		event_array[1]->registerParticipant(1);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}
	try {
		event_array[2]->registerParticipant(1);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}
	dynamic_cast<ClosedEvent*>(event_array[1])->addInvitee(2);
	event_array[1]->registerParticipant(2);
	event_array[2]->registerParticipant(4);
	event_array[0]->printLong(buf);
	assert(compare_and_clear(buf, "Open 19/1/2021\n1\n"));
	event_array[1]->printLong(buf);
	assert(compare_and_clear(buf, "Closed 20/1/2021\n2\n"));
	event_array[2]->printLong(buf);
	assert(compare_and_clear(buf, "Custom 21/1/2021\n4\n"));

	for (int i=0; i<3; i++) {delete event_array[i];}
}

void iteratorTest() {
	Festival f(DateWrap(19,1,2021));
	try {
		f.add(OpenEvent(DateWrap(20,1,2021), "Failed open"));
		assert(0);
	} catch (mtm::DateMismatch&) {}
	f.add(OpenEvent(DateWrap(19,1,2021), "Aopen"));
	f.add(OpenEvent(DateWrap(19,1,2021), "Bopen"));
	f.add(OpenEvent(DateWrap(19,1,2021), "Copen"));
	EventContainer::EventIterator iter1 = f.begin();
	assert((*iter1).getName() == "Aopen");
	EventContainer::EventIterator iter2 = EventContainer::EventIterator(iter1);
	assert(iter2 == iter1 && &(*iter2) == &(*iter1));
	++iter1;
	assert(iter2 != iter1);
	assert((*iter2).getName() == "Aopen" && (*iter1).getName() == "Bopen");
	iter2 = iter1;
	assert(iter2 == iter1 && &(*iter2) == &(*iter1));
	++iter1;
	assert(iter2 != iter1);
	assert((*iter2).getName() == "Bopen" && (*iter1).getName() == "Copen");
	//Problem? This allows bypassing DateMismatch
	*iter1 = OpenEvent(DateWrap(20,1,2021), "Dopen");
	assert((*iter1).getName() == "Dopen");
	++iter1;
	assert(iter1 == f.end());
	//Check that program does not crash when we iterate past NULL
	++iter1;

}

int main() {
	polymorphismTest();
    iteratorTest();
}