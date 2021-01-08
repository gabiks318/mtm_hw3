#include <iostream>
#include <string>

#include "test_utilities.h"
#include "../exceptions.h"
#include "../date_wrap.h"
#include "../open_event.h"
#include "../closed_event.h"
#include "../custom_event.h"

using std::string;
using std::cout;
using std::endl;
using namespace mtm;

#define NUMBER_TESTS 4

struct StudentFilter {
    bool operator()(int student) {
        return student == 1 || student == 3 || student == 20000;
    }
};

bool testEventCreateDestroy() {
    bool result = true;

    string name = "Hot event";
    OpenEvent event(DateWrap(), name);
    ClosedEvent event2(DateWrap(), name);
    CustomEvent<StudentFilter> event3(DateWrap(), name, StudentFilter());
    
    return result;
}

bool testOpenEventGeneral(){
    bool result = true;
    string name = "Hot event";
    DateWrap date(8,1,2021);
    OpenEvent event(date, name);
    OpenEvent event2 = *static_cast<OpenEvent *>(event.clone());

    ASSERT_TEST(event.getDate() == date, returnLabel);
    ASSERT_TEST(event.getName() == name, returnLabel);
    
    ASSERT_TEST(event2.getDate() == date, returnLabel);
    ASSERT_TEST(event2.getName() == name, returnLabel);

returnLabel:
    return result;
}

bool testOpenEventRegisterUnregister(){
    bool result = true;
    string name = "Hot event";
    DateWrap date(8,1,2021);
    OpenEvent event(date, name);

    event.registerParticipant(6);

    try{
        event.registerParticipant(6);
    } catch(mtm::AlreadyRegistered& e){

    } catch(std::exception& e){
        ASSERT_TEST(false, returnLabel);
    }

    try{
        event.registerParticipant(-1);
    } catch(mtm::InvalidStudent& e){

    } catch(std::exception& e){
        ASSERT_TEST(false, returnLabel);
    }

    try{
        event.registerParticipant(20000);
    } catch(mtm::InvalidStudent& e){

    } catch(std::exception& e){
        ASSERT_TEST(false, returnLabel);
    }

returnLabel:
    return result;
}

bool testClosedEventGeneral(){
    bool result = true;

    string name = "Cold event";
    DateWrap date(8,1,2021);
    ClosedEvent event(date, name);
    ClosedEvent event2 = *static_cast<ClosedEvent *>(event.clone());

    ASSERT_TEST(event.getDate() == date, returnLabel);
    ASSERT_TEST(event.getName() == name, returnLabel);
    
    ASSERT_TEST(event2.getDate() == date, returnLabel);
    ASSERT_TEST(event2.getName() == name, returnLabel);
    
returnLabel:
    return result;
}

/* bool test(){
    bool result = true;

returnLabel:
    return result;
} */

bool (*tests[]) (void) = {
        testEventCreateDestroy,
        testOpenEventGeneral,
        testOpenEventRegisterUnregister,
        testClosedEventGeneral
        
};

const char* testNames[] = {
        "testEventCreateDestroy",
        "testOpenEventGeneral",
        "testOpenEventRegisterUnregister",
        "testClosedEventGeneral"
        
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
