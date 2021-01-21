#include "../../partB/base_event.h"
#include "../../partB/custom_event.h"
#include "../../partA/exceptions.h"
#include <sstream>
#include <cassert>
using std::ostringstream;
using std::string;
using std::cout;
using mtm::CustomEvent;
using mtm::DateWrap;

bool compare_and_clear(ostringstream& buf, string s) {
	bool compare = buf.str() == s;
	buf.str("");
	buf.clear();
	return compare;
}

struct Divisible2 {
	bool operator()(int num) {
		return (num % 2 == 0);
	}
};


int main() {
	ostringstream buf;
	CustomEvent<Divisible2>* ce = new CustomEvent<Divisible2>(DateWrap(26, 12, 2020), "Boxing Day", Divisible2());
	ce->printShort(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n"));
	for(int i=1; i<1000; i++) {
		try {
			ce->registerParticipant(i);
			if (i % 2 != 0) {
				assert(0);
			}
		} catch (mtm::RegistrationBlocked&) {}
	}

	try {
		ce->unregisterParticipant(501);
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


	for(int i=1; i<1000; i++) {
		if (i != 2 && i != 500 && i != 742 && i%2==0) {
			ce->unregisterParticipant(i);
		}
	}
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n500\n742\n"));

	//Clone testing
	CustomEvent<Divisible2>* cloned = ce->clone();
	cloned->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n500\n742\n"));
	cloned->unregisterParticipant(500);
	ce->unregisterParticipant(742);
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n500\n"));
	cloned->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n742\n"));

	try {
		cloned->registerParticipant(501);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}

	//Copy constructor testing - same functionality as clone
	ce->registerParticipant(742);
	CustomEvent<Divisible2>* cloned2 = new CustomEvent<Divisible2>(*ce);
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n500\n742\n"));
	cloned2->unregisterParticipant(500);
	ce->unregisterParticipant(742);
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n500\n"));
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n742\n"));

	try {
		cloned2->registerParticipant(501);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}

	//Assignment operator testing - same functionality as clone
	ce->registerParticipant(742);
	*cloned2 = *ce;
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n500\n742\n"));
	cloned2->unregisterParticipant(500);
	ce->unregisterParticipant(742);
	ce->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n500\n"));
	cloned2->printLong(buf);
	assert(compare_and_clear(buf, "Boxing Day 26/12/2020\n2\n742\n"));

	try {
		cloned2->registerParticipant(501);
		assert(0);
	} catch (mtm::RegistrationBlocked&) {}

	delete ce;
	delete cloned;
	delete cloned2;
	return 0;
}