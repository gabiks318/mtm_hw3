#include "date_wrap.h"
#include "exceptions.h"
#include "../utilities.h"
#include <iostream>
#include <sstream>
#include <cassert>
using std::ostringstream;
using mtm::DateWrap;
using mtm::compare_and_clear;
using std::cout;
using std::endl;

template <class T> void print(const T& x) { cout << x << endl; }

int main() {
    DateWrap date(30, 12, 2020);
	assert(date.day() == 30 && date.month() == 12 && date.year() == 2020);
	ostringstream buf;
	buf << date << endl;
	assert(compare_and_clear(buf, "30/12/2020\n"));
	DateWrap date1 = date + 4;
	DateWrap date2 = 4 + date;
	assert(date1.day() == 4 && date1.month() == 1 && date1.year() == 2021);
	assert(date2.day() == 4 && date2.month() == 1 && date2.year() == 2021);
	assert(date1 == date2);
	assert(date1 <= date2);
	assert(date1 >= date2);
	assert(date < date1);
	assert(date < date2);
	assert(date1 > date);
	assert(date2 > date);
	buf << date1 << endl;
	assert(compare_and_clear(buf, "4/1/2021\n"));
	date += 4;
	assert(date == date1 && date == date2);
	buf << date << endl;
	assert(compare_and_clear(buf, "4/1/2021\n"));
	date++;
	assert(date.day() == 5 && date.month() == 1 && date.year() == 2021);
	buf << date << endl;
	assert(compare_and_clear(buf, "5/1/2021\n"));
    try {
        DateWrap date2(-1, 1, 2000);
		assert(0);
    } catch (mtm::InvalidDate) {}
    try {
        DateWrap date2(31, 1, 2000);
		assert(0);
    } catch (mtm::InvalidDate) {}
    try {
        DateWrap date2(1, 0, 2000);
		assert(0);
    } catch (mtm::InvalidDate) {}
    try {
        DateWrap date2(1, -1, 2000);
		assert(0);
    } catch (mtm::InvalidDate) {}
    try {
        DateWrap date2(1, 13, 2000);
		assert(0);
    } catch (mtm::InvalidDate) {}
    try {
        date += (-3);
		assert(0);
    } catch (mtm::NegativeDays) {}
    try {
        date = date + (-3);
		assert(0);
    } catch (mtm::NegativeDays) {}
    try {
        date = -3 + date;
		assert(0);
    } catch (mtm::NegativeDays) {}
    return 0;
}
