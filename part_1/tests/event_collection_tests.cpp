#include <iostream>
#include <string>

#include "test_utilities.h"
#include "../exceptions.h"
#include "../date_wrap.h"
#include "../open_event.h"
#include "../closed_event.h"
#include "../custom_event.h"
#include "../festival.h"

using std::string;
using std::cout;
using std::endl;
using namespace mtm;

#define NUMBER_TESTS 1

template <class T> void print(const T& x) { cout << x << endl; }

struct StudentFilter {
    bool operator()(int student) {
        return student == 1 || student == 3 || student == 20000;
    }
};

Festival initFestivalEventList(){
    DateWrap date(28,2,2021);
    Festival festival(date);
    
    festival.add(OpenEvent(date, "Travis Scott performance"));
    festival.add(CustomEvent<StudentFilter>(date, "Water fight", StudentFilter()));
    festival.add(OpenEvent(date, "Kendrick Lamar performance"));
    festival.add(ClosedEvent(date, "Drake performance"));
    festival.add(ClosedEvent(date, "Eating comptetition"));
    
}

bool testFestivalCreateDestroy() {
    bool result = true;

    string name = "Hot event";
    OpenEvent event(DateWrap(), name);
    ClosedEvent event2(DateWrap(), name);
    CustomEvent<StudentFilter> event3(DateWrap(), name, StudentFilter());
    
    return result;
}


/* bool test(){
    bool result = true;
    bool passed = true;

returnLabel:
    return result;
}*/

bool (*tests[]) (void) = {
        testFestivalCreateDestroy,     
};

const char* testNames[] = {
        "testFestivalCreateDestroy",
        
};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        for (int test_idx = 0; test_idx < NUMBER_TESTS; test_idx++) {
            RUN_TEST(tests[test_idx], testNames[test_idx]);
        }
        return 0;
    }
    if (argc != 2) {
        fprintf(stdout, "Usage: priority_queue_tests <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > NUMBER_TESTS) {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);
    return 0;
}
