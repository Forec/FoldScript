//
// Created by 王耀 on 2017/11/11.
//

#include <iostream>
#include <gflags/gflags.h>

DEFINE_int32(core, 1, "How many processors to be used");

int main(int argc, char * argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << FLAGS_core << " cores specified." << std::endl;

    return 0;
}