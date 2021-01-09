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

#define NUMBER_TESTS 8

template <class T> void print(const T& x) { cout << x << endl; }

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

    ASSERT_TEST(event == event2, returnLabel);

returnLabel:
    return result;
}

bool testOpenEventRegister(){
    bool result = true;
    bool passed = true;
    string name = "Hot event";
    DateWrap date(8,1,2021);
    OpenEvent event(date, name);

    event.registerParticipant(6);
    event.registerParticipant(18);

    List<int> participants = event.getParticipants();
    event.printShort(cout);
    event.printLong(cout);

    ASSERT_TEST(participants.exists(6) == true, returnLabel);
    ASSERT_TEST(participants.exists(18) == true, returnLabel);


    try{
        passed = false;
        event.registerParticipant(6);
    } catch(mtm::AlreadyRegistered& e){
        passed = true;
    } 
    ASSERT_TEST(passed, returnLabel);

    try{
        passed = false;
        event.registerParticipant(-1);
    } catch(mtm::InvalidStudent& e){
        passed = true;
    } 
    ASSERT_TEST(passed, returnLabel);
    

    try{
        passed = false;
        event.registerParticipant(2000000);
    } catch(mtm::InvalidStudent& e){
        passed = true;
    } 
    ASSERT_TEST(passed, returnLabel);


returnLabel:
    return result;
}

bool testOpenEventUnregister(){
    bool result = true;
    bool passed = true;
    string name = "Hot event";
    DateWrap date(8,1,2021);
    OpenEvent event(date, name);

    event.registerParticipant(6);
    event.registerParticipant(18);

    event.unregisterParticpant(6);
    List<int> participants = event.getParticipants();

    ASSERT_TEST(participants.exists(6) == false, returnLabel);
    ASSERT_TEST(participants.exists(18) == true, returnLabel);


    try{
        passed = false;
        event.unregisterParticpant(6);
    } catch(mtm::NotRegistered& e){
        passed = true;
    } 
    ASSERT_TEST(passed, returnLabel);


    try{
        passed = false;
        event.unregisterParticpant(-1);
    } catch(mtm::InvalidStudent& e){
        passed = true;
    } 
    ASSERT_TEST(passed, returnLabel);

    try{
        passed = false;
        event.unregisterParticpant(200000);
    } catch(mtm::InvalidStudent& e){
        passed = true;
    } 
    ASSERT_TEST(passed, returnLabel);

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

bool testClosedEventRegister(){
    bool result = true;
    bool passed; // To check exceptions
    string name = "Cold event";
    DateWrap date(8,1,2021);
    ClosedEvent event(date, name);
    List<int> invitees;
    List<int> participants;

    // Invitee tests
    for(int i = 1; i < 10; i++){
        event.addInvitee(i);
    }
    
    invitees = event.getInvitees();
    for(int i = 1; i < 10; i++){
        ASSERT_TEST(invitees.exists(i), returnLabel);
    }
    
    try{
        passed = false;
        event.addInvitee(2);
    } catch(mtm::AlreadyInvited& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        passed = false;
        event.addInvitee(-20);
    } catch(mtm::InvalidStudent&){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        passed = false;
        event.addInvitee(1500000);
    } catch(mtm::InvalidStudent&){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);
    

    
    // Participants tests

    for(int i = 1; i < 10; i++){
        event.registerParticipant(i);
    }

    participants = event.getParticipants();


    for(int i = 1; i < 10; i++){
        ASSERT_TEST(participants.exists(i), returnLabel);
    }

    try{
        passed = false;
        event.registerParticipant(3);
    } catch(mtm::AlreadyRegistered& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        event.registerParticipant(200);
        passed = false;
    } catch(mtm::RegistrationBlocked& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        event.registerParticipant(1500000);
        passed = false;
    } catch(mtm::InvalidStudent& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        event.registerParticipant(-20);
        passed = false;
    } catch(mtm::InvalidStudent& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);




returnLabel:
    return result;
} 

bool testCustomEventGeneral(){
    bool result = true;
    string name = "Lukewarm event";
    DateWrap date(5,5,2021);
    CustomEvent<StudentFilter> event(date, name, StudentFilter());
    CustomEvent<StudentFilter> event2 = *static_cast<CustomEvent<StudentFilter> *>(event.clone());

    ASSERT_TEST(event.getDate() == date, returnLabel);
    ASSERT_TEST(event.getName() == name, returnLabel);
    
    ASSERT_TEST(event2.getDate() == date, returnLabel);
    ASSERT_TEST(event2.getName() == name, returnLabel);

    ASSERT_TEST(event == event2, returnLabel);


returnLabel:
    return result;
}

bool testCustomEventRegister(){
    bool result = true;
    bool passed = true;
    string name = "Lukewarm event";
    DateWrap date(5,5,2021);
    CustomEvent<StudentFilter> event(DateWrap(), name, StudentFilter());
    List<int> participants;

    event.registerParticipant(1);
    event.registerParticipant(3);
    event.registerParticipant(20000);
    participants = event.getParticipants();

    ASSERT_TEST(participants.exists(1), returnLabel);
    ASSERT_TEST(participants.exists(3), returnLabel);
    ASSERT_TEST(participants.exists(20000), returnLabel);

    try{
        event.registerParticipant(55);
        passed = false;
    } catch(mtm::RegistrationBlocked& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        event.registerParticipant(1);
        passed = false;
    } catch(mtm::AlreadyRegistered& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        event.registerParticipant(1500000);
        passed = false;
    } catch(mtm::InvalidStudent& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    try{
        event.registerParticipant(-20);
        passed = false;
    } catch(mtm::InvalidStudent& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);


returnLabel:
    return result;
}

/* bool test(){
    bool result = true;
    bool passed = true;

returnLabel:
    return result;
}*/

bool (*tests[]) (void) = {
        testEventCreateDestroy,
        testOpenEventGeneral,
        testOpenEventRegister,
        testOpenEventUnregister,
        testClosedEventGeneral,
        testClosedEventRegister,
        testCustomEventGeneral,
        testCustomEventRegister     
};

const char* testNames[] = {
        "testEventCreateDestroy",
        "testOpenEventGeneral",
        "testOpenEventRegisterUnregister",
        "testOpenEventUnregister",
        "testClosedEventGeneral",
        "testClosedEventRegister",
        "testCustomEventGeneral",
        "testCustomEventRegister"
        
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
