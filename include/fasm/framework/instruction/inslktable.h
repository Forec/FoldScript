//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_ASM_INSLKTABLE_H
#define FOLDSCRIPT_ASM_INSLKTABLE_H

#include <string>
#include <unordered_map>
#include "instrlookup.h"

/*
 * InstrLookupTable: 指令查找表
 * @iTable: 以指令助记符为键，映射到指令具体属性
 * @init(): 将 FASM 内置指令添加至查找表
 * @getInstrOpType(): 根据指令名和操作数索引确定操作数类型
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

#endif //FOLDSCRIPT_ASM_INSLKTABLE_H
