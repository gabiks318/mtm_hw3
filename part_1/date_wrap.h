#ifndef DATE_WRAP_H
#define DATE_WRAP_H

#include <iostream>

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
    friend std::ostream& operator<<(std::ostream& os, const DateWrap&);
    friend bool operator==(const DateWrap& date1, const DateWrap& date2);
    friend bool operator>(const DateWrap& date1, const DateWrap& date2);

    class InvalidDate{};
    class NegativeDays{};
};

bool isDateLegal(int day, int month , int year);

bool operator!=(const DateWrap& date1, const DateWrap& date2);
bool operator<=(const DateWrap& date1, const DateWrap& date2);
bool operator>(const DateWrap& date1, const DateWrap& date2);
bool operator>=(const DateWrap& date1, const DateWrap& date2);
DateWrap operator+(DateWrap date ,int num);
DateWrap operator+(int num, DateWrap date);


#endif //DATE_WRAP_H