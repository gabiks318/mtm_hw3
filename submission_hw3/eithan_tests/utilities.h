#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::ostringstream;
using std::ofstream;
using std::string;
using std::endl;

namespace mtm{
    void compare_file_to_buffer(ostringstream& buf, string file_address) {
        system("> ./tmp.txt");
        ofstream fp("./tmp.txt");
        fp << buf.str();
        fp.close();
        string output("diff -u ./tmp.txt ");
        output.append(file_address);
        int exit_code = system(output.c_str());
		if (exit_code) {
			cout << " ^^^ Error when comparing to file " << file_address << endl;
		}
        system("rm ./tmp.txt");
		buf.str("");
		buf.clear();
    }

	bool compare_and_clear(ostringstream& buf, string s) {
		bool compare = buf.str() == s;
		buf.str("");
		buf.clear();
		return compare;
	}

    struct Divisible2 {
        bool operator()(int num) {
            return (num % 2 == 0);
        }
    };
}

#endif //UTILITIES_H