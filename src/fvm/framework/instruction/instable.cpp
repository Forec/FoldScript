//
// Created by 王耀 on 2017/11/12.
// 此文件同步自 fasm/framework/instruction/instable.cpp
//

#include "instable.h"


InstrTable::InstrTable() {
    reset();
}

InstrTable::~InstrTable() {
    instrStream.clear();
}

void InstrTable::reset() {
    instrStream.clear();
}

void InstrTable::setSize(unsigned int size) {
    uiSize = size;
}

void InstrTable::fit() {
    instrStream.resize(uiSize, Instr(0, 0));
}

void InstrTable::setOpCode(unsigned long index, unsigned int opCode) {
    if (index < instrStream.size())
        instrStream[index].uiOpCode = opCode;
}

void InstrTable::setOpCount(unsigned long index, unsigned int opCount) {
    if (index < instrStream.size())
        instrStream[index].uiOpCount = opCount;
}

void InstrTable::setValueList(unsigned long index, const std::vector<Value> &valueList) {
    if (index < instrStream.size())
        instrStream[index].ValueList = valueList;
}

unsigned long InstrTable::getSize() {
    return uiSize;
}

void InstrTable::addInstr(const Instr &ins) {
    instrStream.emplace_back(ins);
}

Instr InstrTable::getInstr(unsigned long index) {
    if (index >= instrStream.size())
        return Instr(0);
    return instrStream.at(index);
}

void InstrTable::setInstr(unsigned long index, const Instr &instr) {
    if (index >= instrStream.size())
        return;
    instrStream[index] = instr;
}
