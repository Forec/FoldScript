#include <string>
#include <iostream>
#include <gflags/gflags.h>
#include "utils.h"

DEFINE_string(o, "a.fse", "Output filename after assembled.");

int main(int argc, char * argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "Output Filename: " << FLAGS_o << std::endl;
    std::string s = "-12.4123";
    std::cout << "String \"" << s << "\" is " << (isStringFloat(s) ? "" : "not ")
              << "in float format" << std::endl;
    return 0;
}