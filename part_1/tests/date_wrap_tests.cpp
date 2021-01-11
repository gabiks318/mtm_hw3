#include "test_utilities.h"
#include "../date_wrap.h"
#include "../exceptions.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using namespace mtm;

#define NUMBER_TESTS 6

bool testDateWrapCreateDestroy() {
    bool result = true;

    DateWrap date(11,1, 2021);
    ASSERT_TEST(list.isEmpty() == true, returnListCreateDestroy);
    
returnListCreateDestroy:
    return result;
}

/* bool test(){
    bool result = true;

returnLabel:
    return result;
} */

bool (*tests[]) (void) = {
        testListCreateDestroy,
};

const char* testNames[] = {
        "testListCreateDestroy",
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
