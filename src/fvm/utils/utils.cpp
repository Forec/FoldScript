//
// Created by 王耀 on 2017/11/11.
//

#include <cstdlib>
#include <string>
#include <iostream>
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

char INSTR_TABLE[][16] = {
        "NOP", "MOV", "ADD", "SUB", "MUL", "DIV", "MOD",
        "EXP", "NEG", "INC", "DEC", "AND", "OR", "XOR",
        "NOT", "SHL", "SHR", "CONCAT", "GETCHAR", "SETCHAR",
        "JMP", "JE", "JNE", "JG", "JL", "JGE", "JLE",
        "PUSH", "POP", "CALL", "RET", "CALLHOST", "PAUSE",
        "EXIT"
};