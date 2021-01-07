#ifndef DATE_WRAP_H
#define DATE_WRAP_H

#include <iostream>

extern "C"
{
  #include "date/date.h"  
}
namespace mtm
{


class DateWrap{
    Date date;

    public:
    DateWrap(int day = 1, int month = 1, int year = 2021);
    DateWrap(const DateWrap& date2);
    DateWrap& operator=(const DateWrap& date_wrap);
    ~DateWrap();
    int day() const;
    int month() const;
    int year() const;
    DateWrap operator++(int);
    DateWrap& operator+=(int num);
    friend std::ostream& operator<<(std::ostream& os, const DateWrap&);
    bool operator==(const DateWrap& date1) const;
    bool operator>(const DateWrap& date1) const;
};

std::ostream& operator<<(std::ostream& os, const DateWrap&);
bool operator!=(const DateWrap& date1, const DateWrap& date2);
bool operator<=(const DateWrap& date1, const DateWrap& date2);
bool operator<(const DateWrap& date1, const DateWrap& date2);
bool operator>=(const DateWrap& date1, const DateWrap& date2);
DateWrap operator+(DateWrap& date ,int num);
DateWrap operator+(int num, DateWrap& date);

}
#endif //DATE_WRAP_H
