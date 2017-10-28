//
// Created by 王耀 on 2017/10/17.
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

void InstrTable::resize(unsigned long size) {
    instrStream.resize(size, Instr(0, 0));
}

void InstrTable::setOpCode(unsigned long index, unsigned int opCode) {
    if (index < instrStream.size())
        instrStream[index].uiOpCode = opCode;
}

void InstrTable::setOpCount(unsigned long index, unsigned int opCount) {
    if (index < instrStream.size())
        instrStream[index].uiOpCount = opCount;
}

void InstrTable::setOpList(unsigned long index, const std::vector<Op> &opList) {
    if (index < instrStream.size())
        instrStream[index].OpList = opList;
}

unsigned long InstrTable::getSize() {
    return instrStream.size();
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