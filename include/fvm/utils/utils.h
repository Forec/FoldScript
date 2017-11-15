//
// Created by 王耀 on 2017/11/13.
//

#ifndef FOLDSCRIPT_VM_UTILS_H
#define FOLDSCRIPT_VM_UTILS_H

#include <string>

extern char INSTR_TABLE[][16];
unsigned long getCurrentTimestamp();

void exitOnError(const std::string &msg);
void exitOnInvalidOp();

#endif //FOLDSCRIPT_VM_UTILS_H
