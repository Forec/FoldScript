//
// Created by 王耀 on 2017/11/11.
//

#include <string>
#include <iostream>
#include <cstdlib>
#include "utils.h"

// TODO
unsigned long getCurrentTimestamp() {
    return 0;
}

void exitOnError(const std::string &msg) {
    std::cerr << "致命错误：" << msg << std::endl;
    exit(1);
}

void exitOnInvalidOp() {
    exitOnError("与指令不匹配的非法操作数!");
}