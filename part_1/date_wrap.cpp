#include <iostream>
#include "date_wrap.h"

#define MAX_DAY 30
#define MAX_MONTH 12

extern "C"
{
  #include "date/date.h"  
} 
 
static bool isDateLegal(int day, int month , int year)
{
    if(day > MAX_DAY || day < 1 || month > MAX_MONTH || month < 1)
    {
        return false;
    }

    return true;
}

DateWrap::DateWrap(int day, int month, int year){
    if(!isDateLegal(day, month, year)){
        throw InvalidDate();
    }
    date = dateCreate(day, month, year);
    if(date == NULL){
        // TODO: Handle memory fail
    }
    
}
DateWrap::~DateWrap(){
    dateDestroy(date);
}

DateWrap::DateWrap(const DateWrap& date2){
    date = dateCreate(date2.day(), date2.month(), date2.year());
}

int DateWrap::day() const{
    int day, month, year;
    dateGet(date, &day, &month, &year);
    return day;
}

int DateWrap::month() const{
    int day, month, year;
    dateGet(date, &day, &month, &year);
    return month;
}

int DateWrap::year() const{
    int day, month, year;
    dateGet(date, &day, &month, &year);
    return year;
}

ostream& operator<<(ostream& os, const DateWrap& date){
    return os << date.day() << "/" << date.month() << "/" << date.year();
}

bool DateWrap::operator==(const DateWrap& date1) const{
    return dateCompare(this->date, date1.date) == 0;
}

bool operator!=(const DateWrap& date1, const DateWrap& date2){
    return ! (date1 == date2);
}

bool operator<=(const DateWrap& date1, const DateWrap& date2){
    return date2 > date1 || date1 == date2;
}

bool DateWrap::operator>(const DateWrap& date1) const{
    return dateCompare(this->date, date1.date) > 0;
}

bool operator>=(const DateWrap& date1, const DateWrap& date2){
    return date1 > date2 || date1 == date2;
}

bool operator<(const DateWrap& date1, const DateWrap& date2){
    return date2 > date1;
}

DateWrap DateWrap::operator++(int){
    dateTick(date);
    return *this;   
}

DateWrap& DateWrap::operator+=(int num){

    if(num < 0){
        throw NegativeDays();
    }
    for(int i = 0; i < num; i++){
        dateTick(date);
        /* *this++; */
    }
    return *this;
}


DateWrap operator+(DateWrap date, int num){
    DateWrap new_date = date;
    return new_date += num;
}

DateWrap operator+(int num, DateWrap date){
    return date + num;
}