#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include <iostream>
#include <fstream>
using mtm::DateWrap;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using mtm::Exception;

#define ASSERT_TEST(expr)                                                         \
     do {                                                                          \
         if (!(expr)) {                                                            \
             cout << "\nAssertion failed at"<< __FILE__<< __LINE__ << #expr << endl; \
             result = false;                                                       \
         }                                                                         \
     } while (0);

#define RUN_TEST(test, name)                  \
    do {                                 \
        cout << "+ Running" << name << "...";  \
        if (test()) {                    \
            cout << "[OK]\n" << endl;         \
        } else {                         \
            cout << "[Failed]\n\n <span>To see what the test does and why it failed, please check the link at the top of the page to the test file</span>" << endl;       \
        }                                \
    } while (0);


template <class T> void print(const T& x, ofstream& stream) { stream << x << endl; }

#define ASSERT(expr) ASSERT_TEST(expr)

class FileFailed{
public:
    FileFailed() = default;
    ~FileFailed() = default;
};

class FileOutputWrong{
public:
    FileOutputWrong() = default;
    ~FileOutputWrong() = default;
};


bool matchFiles(const char* out,const char*  exp){
    ifstream output(out);
    if(!output){
        cout << "can't open file" << endl;
    }
    ifstream expOutput(exp);
    if(!expOutput){
        cout << "can't open file" << endl;
    }
    while(!output.eof()){
        char c;
        output >> c;
        char ex;
        expOutput >> ex;
        if(ex != c) {
            return false;
        }
    }
    return true;
}




/**________________________________________________*/
/** HERE START THE TESTS*/

bool testConstructor(){
    bool result = true;
    const char* fileName = "../provided/testOutputs/partA/your_outputs/testConstructor.txt";
    std::ofstream out(fileName, std::ios_base::in);
    out.open(fileName);
    if(!out.is_open()){
        throw FileFailed();
    }
    DateWrap d1(1,1,2000);
    DateWrap d2(2,1,2000);
    DateWrap d3(3,1,2000);
    print(d1, out);
    print(d2, out);
    print(d3, out);
    try{
        DateWrap d4(0, 1, 2000);
    }catch(mtm::InvalidDate&){
        out << "InvalidDate" << endl;
    }
    try{
        DateWrap d4(1, 0, 2000);
    }catch(mtm::InvalidDate&){
        out << "InvalidDate" << endl;
    }
    DateWrap d4(1, 1, 1);
    print(d4, out);
    out.close();
    ASSERT(matchFiles(fileName,"../provided/testOutputs/partA/expected/testConstructor.txt"))
    return result;
}

bool testBooleanOperators()
{
    bool result = true;
    DateWrap d1(1,1,2000);
    DateWrap d2(1,1,2000);
    DateWrap d3(2,1,2000);
    ASSERT(d3 > d1)
    ASSERT(d1 >= d2)
    ASSERT(d1 <= d2)
    ASSERT(d1 == d2)
    ASSERT(d1 < d3)
    ASSERT(d1 != d3)
    return result;
}

bool testArithmeticOperators(){
    bool result = true;
    DateWrap d1(1,1,2000);
    DateWrap d2(1,1,2000);
    DateWrap d3(2,1,2000);
    d1+=1;
    ASSERT(d1 == d3)
    DateWrap d4(30,2,3);
    d4+=1;
    ASSERT(d4.day() == 1)
    d1++;
    ASSERT(d4.month() == 3)
    ASSERT(d1.year() == 2000)
    return result;
}

bool testExceptions()
{
    bool result = true;
    const char* fileName = "../provided/testOutputs/partA/your_outputs/testExceptions.txt";
    std::ofstream out(fileName, std::ios_base::in);
    out.open(fileName);
    if(!out.is_open()){
        throw FileFailed();
    }
    DateWrap d1(1,1,2000);
    DateWrap d2(2,1,2000);
    DateWrap d3(3,1,2000);
    try{
        d1 += -1;
    }catch(mtm::NegativeDays&){
        out << "NegativeDays" << endl;
    }
    try{
        d2 = d1 + (-1);
        print(d2, out);
    }catch(mtm::NegativeDays&){
        out << "NegativeDays" << endl;
    }
    out.close();
    ASSERT(matchFiles(fileName, "../provided/testOutputs/partA/expected/testExceptions.txt"))
    return result;
}
const int NUMBER_OF_TESTS = 4;

#define TEST_NAMES \
    X(testConstructor) \
    X(testBooleanOperators) \
    X(testArithmeticOperators) \
    X(testExceptions)




const char *testNames[] = {
#define X(name) #name,
        TEST_NAMES
#undef X
};
bool (*tests[])(void) = {
#define X(test_name) test_name,
        TEST_NAMES
#undef X
};


int main(int argc, char* argv[]) {
    if (argc < 2) {
        for(int i = 0; i < NUMBER_OF_TESTS ; i++){
            RUN_TEST(tests[i], testNames[i])
        }
    } else if (argc > 2) {
        std::cout << "invalid arguments" << std::endl;
    } else {
        int i = std::atoi(argv[1]);
        tests[i - 1]();
    }
    return 0;
}