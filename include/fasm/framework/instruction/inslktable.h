//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_INSLKTABLE_H
#define FOLDSCRIPT_INSLKTABLE_H

#include <string>
#include <unordered_map>
#include "instrlookup.h"

/*
 * InstrLookupTable: 指令查找表
 * @iTable: 以指令助记符为键，映射到指令具体属性
 */

class InstrLookupTable {
private:
    std::unordered_map<std::string, InstrLookup> iTable;
public:
    InstrLookupTable();
    ~InstrLookupTable();
    void init();
    bool addInstrLookup(const std::string &mnemonic, unsigned int opCode, unsigned int opCount);
    InstrLookup getInstrLookup(const std::string &mnemonic);
    void setInstrOpType(const std::string &mnemonic, unsigned int opIndex, OpTypes type);
    OpTypes getInstrOpType(const std::string &mnemonic, unsigned int opIndex);
};

#endif //FOLDSCRIPT_INSLKTABLE_H
