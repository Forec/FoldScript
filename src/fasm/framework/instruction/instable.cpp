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