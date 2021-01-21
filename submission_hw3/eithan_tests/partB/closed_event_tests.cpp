#include "../../partB/base_event.h"
#include "../../partB/closed_event.h"
#include "../../partA/exceptions.h"
#include <sstream>
#include <cassert>
using std::ostringstream;
using std::string;
using std::cout;
using mtm::ClosedEvent;
using mtm::DateWrap;

bool compare_and_clear(ostringstream& buf, string s) {
	bool compare = buf.str() == s;
	buf.str("");
	buf.clear();
	return compare;
}

int main() {
	ostringstream buf;
	ClosedEvent* ce = new ClosedEvent(DateWrap(26, 12, 2020), "Boxing Day");
	ce->printShort(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n"));
	for(int i=1; i<1000; i++) {
		try {
			ce->registerParticipant(i);
			assert(0);
		} catch (mtm::RegistrationBlocked&) {}
		ce->addInvitee(i);
		ce->registerParticipant(i);
	}
	try {
		ce->addInvitee(100);
		assert(0);
	} catch (mtm::AlreadyInvited&) {}

	try {
		ce->unregisterParticipant(1001);
		assert(0);
	} catch (mtm::NotRegistered&) {}


	try {
		ce->registerParticipant(0);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	try {
		ce->registerParticipant(1234567891);
		assert(0);
	} catch (mtm::InvalidStudent&) {}

	try {
		ce->unregisterParticipant(0);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	try {
		ce->unregisterParticipant(1234567891);
		assert(0);
	} catch (mtm::InvalidStudent&) {}

	try {
		ce->addInvitee(0);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	try {
		ce->addInvitee(1234567891);
		assert(0);
	} catch (mtm::InvalidStudent&) {}

	for(int i=1; i<1000; i++) {
		if (i != 1 && i != 503 && i != 745) {
			ce->unregisterParticipant(i);
		}
	}
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n745\n"));

	//Clone testing
	ClosedEvent* cloned = ce->clone();
	cloned->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n745\n"));
	cloned->unregisterParticipant(503);
	ce->unregisterParticipant(745);
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n"));
	cloned->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n745\n"));

	cloned->addInvitee(1001);
	cloned->registerParticipant(1001);
	try {
		ce->registerParticipant(1001);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}

	//Copy constructor testing - same functionality as clone
	ce->registerParticipant(745);
	ClosedEvent* cloned2 = new ClosedEvent(*ce);
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n745\n"));
	cloned2->unregisterParticipant(503);
	ce->unregisterParticipant(745);
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n"));
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n745\n"));

	cloned2->addInvitee(1001);
	cloned2->registerParticipant(1001);
	try {
		ce->registerParticipant(1001);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}

	//Assignment operator testing - same functionality as clone
	ce->registerParticipant(745);
	*cloned2 = *ce;
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n745\n"));
	cloned2->unregisterParticipant(503);
	ce->unregisterParticipant(745);
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n"));
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n745\n"));

	cloned2->addInvitee(1001);
	cloned2->registerParticipant(1001);
	try {
		ce->registerParticipant(1001);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}

	delete ce;
	delete cloned;
	delete cloned2;
	return 0;
}