#ifndef TEST_UTILITIES_H_
#define TEST_UTILITIES_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
using std::ofstream;


void writeOutputToFile(char *file_name, char *file_content) {
    char *new_name = (char * )malloc(strlen(file_name) + strlen("expected_") + 1);
    strcpy(new_name, "expected_");
    strcat(new_name, file_name);
    FILE *file = fopen(new_name, "w");
    if (!file) {
        return;
    }

    fprintf(file, "%s", file_content);
    free(new_name);
    fclose(file);
}

bool isFilePrintOutputCorrect(char *file_name, char *expected_output) {
    FILE *infile;
    char *buffer;
    long numbytes;

    infile = fopen(file_name, "r");

    if (infile == NULL) {
        return false;
    }

    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    fseek(infile, 0L, SEEK_SET);

    buffer = (char *) calloc(numbytes + 1, sizeof(char));

    if (buffer == NULL) {
        return false;
    }

    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    if (numbytes == 0 && strlen(expected_output) != 0) {
        free(buffer);
        return false;
    }

    writeOutputToFile(file_name, expected_output);
    printf("<br>&nbsp;&nbsp;&nbsp;&nbsp;> Printing output: <a href='/staging/{STAGING_ID}/%s'>%s</a> | Expected output: <a href='/staging/{STAGING_ID}/expected_%s'>expected_%s</a> (Might be correct)",
           file_name, file_name, file_name, file_name);
    bool result = (strncmp(buffer, expected_output, numbytes) == 0);
    free(buffer);
    return result;
}

void clearFile(std::string file_name){
    std::ifstream ifs (file_name);
    ifs.close ();
    ofstream ofs(file_name, ofstream::out | ofstream::trunc);
    ofs.close();
}

/**
 * These macros are here to help you create tests more easily and keep them
 * clear.
 *
 * The basic idea with unit-testing is create a test function for every real
 * function and inside the test function declare some variables and execute the
 * function under test.
 *
 * Use the ASSERT_TEST and ASSERT_TEST_WITH_FREE to verify correctness of
 * values.
 */


/**
 * Evaluates expr and continues if expr is true.
 * If expr is false, ends the test by returning false and prints a detailed
 * message about the failure.
 */
 #define ASSERT_TEST(expr, goto_label)                                                         \
     do {                                                                          \
         if (!(expr)) {                                                            \
             printf("\nAssertion failed at %s:%d %s ", __FILE__, __LINE__, #expr); \
             result = false;                                                       \
             goto goto_label;                                                         \
         }                                                                         \
     } while (0)



/**
 * Macro used for running a test from the main function
 */
#define RUN_TEST(test, name)                  \
    do {                                 \
      printf("Running %s ... ", name);   \
        if (test()) {                    \
            printf("[OK]\n");            \
        } else {                         \
            printf("[Failed]\n");        \
        }                                \
    } while (0)

#endif /* TEST_UTILITIES_H_ */
