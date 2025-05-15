#include <iostream> 
#include <cstdlib>
#include "utils.h"

//Assert if "val" is false, print a message and terminate the program
void Assert(bool val, std::string s) {
    if(!val) {
        std::cout << "Assertion failed: " << s << std::endl;
        exit(-1);
    }
};

int defaultSize = 0;