#ifndef DATE_WRAP_H
#define DATE_WRAP_H

#include <iostream>
using std::ostream;

extern "C"
{
  #include "date/date.h"  
}

class DateWrap{
    Date date;

    public:
    DateWrap(int day, int month, int year);
    DateWrap(const DateWrap& date2);
    ~DateWrap();
    int day() const;
    int month() const;
    int year() const;
    DateWrap operator++(int);
    DateWrap& operator+=(int num);
    friend ostream& operator<<(ostream& os, const DateWrap&);
    bool operator==(const DateWrap& date1) const;
    bool operator>(const DateWrap& date1) const;

    class InvalidDate{};
    class NegativeDays{};
};


bool operator!=(const DateWrap& date1, const DateWrap& date2);
bool operator<=(const DateWrap& date1, const DateWrap& date2);
bool operator>=(const DateWrap& date1, const DateWrap& date2);
DateWrap operator+(DateWrap date ,int num);
DateWrap operator+(int num, DateWrap date);


#endif //DATE_WRAP_H