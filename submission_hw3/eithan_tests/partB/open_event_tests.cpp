#include "base_event.h"
#include "open_event.h"
#include "../partA/exceptions.h"
#include <sstream>
#include <cassert>
using std::ostringstream;
using std::string;
using std::cout;
using mtm::OpenEvent;
using mtm::DateWrap;

bool compare_and_clear(ostringstream& buf, string s) {
	bool compare = buf.str() == s;
	buf.str("");
	buf.clear();
	return compare;
}

int main() {
	ostringstream buf;
	OpenEvent* oe = new OpenEvent(DateWrap(26, 12, 2020), "Boxing Day");
	oe->printShort(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n"));
	for(int i=1; i<1000; i++) {
		oe->registerParticipant(i);
		try {
			oe->registerParticipant(i);
			assert(0);
		} catch (mtm::AlreadyRegistered&) {}
	}
	try {
		oe->unregisterParticipant(1001);
		assert(0);
	} catch (mtm::NotRegistered&) {}
	try {
		oe->registerParticipant(0);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	try {
		oe->registerParticipant(1234567891);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	try {
		oe->unregisterParticipant(0);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	try {
		oe->unregisterParticipant(1234567891);
		assert(0);
	} catch (mtm::InvalidStudent&) {}
	for(int i=1; i<1000; i++) {
		if (i != 1 && i != 503 && i != 745) {
			oe->unregisterParticipant(i);
		}
	}
	oe->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n745\n"));
	OpenEvent* cloned = oe->clone();
	cloned->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n745\n"));
	cloned->unregisterParticipant(503);
	oe->unregisterParticipant(745);
	oe->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n503\n"));
	cloned->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n1\n745\n"));

	OpenEvent* oe_later = new OpenEvent(DateWrap(27, 12, 2020), "Boxing Day");
	OpenEvent* oe_golf = new OpenEvent(DateWrap(26, 12, 2020), "golf");
	OpenEvent* oe_athletics = new OpenEvent(DateWrap(26, 12, 2020), "Athletics");
	OpenEvent* oe_identical = new OpenEvent(DateWrap(26, 12, 2020), "Boxing Day");

	assert(*oe < *oe_later && *oe < *oe_golf && *oe_athletics < *oe && *oe_identical == *oe);

	delete oe;
	delete cloned;
	delete oe_later;
	delete oe_golf;
	delete oe_athletics;
	delete oe_identical;
	return 0;
}