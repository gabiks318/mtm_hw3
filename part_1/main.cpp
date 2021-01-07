#include <iostream>
#include "date_wrap.h"
#include "base_event.h"
using std::cout;
using std::endl;
using mtm::DateWrap;

int main(){
    DateWrap date(30, 11, 2020);
    cout << date << endl; // output: "30/11/2020"
    cout << date + 4 << endl; // output: "4/12/2020"
    cout << 3 + date << endl; // output: "3/12/2020"
    date++;
    cout << date << endl; // output: "1/12/2020"
    date += 7;
    cout << date << endl; // output: "8/12/2020"
    cout << (date > DateWrap(29, 11, 2020)) << endl; // output: "1"
    cout << (date <= DateWrap(29, 11, 2020)) << endl; // output: "0"
    cout << (date == DateWrap(30, 11, 2020)) << endl; // output: "0"
    date += (-3); // throw exception NegativeDays
    date = date + (-3); // throw exception NegativeDays
    return 0;
}