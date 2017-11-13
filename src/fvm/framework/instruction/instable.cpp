//
// Created by 王耀 on 2017/11/12.
// 此文件部分同步自 fasm/framework/instruction/instable.cpp
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
    uiSize = 0;
    uiCurrentInstrIndex = 0;
}

void InstrTable::setSize(unsigned int size) {
    uiSize = size;
}

unsigned int InstrTable::getCurrentIndex() {
    return uiCurrentInstrIndex;
}

void InstrTable::fit() {
    if (instrStream.size() < uiSize)
        instrStream.resize(uiSize, Instr(0, 0));
}

void InstrTable::setOpCode(unsigned long index, unsigned int opCode) {
    fit();
    if (index < instrStream.size())
        instrStream[index].uiOpCode = opCode;
}

void InstrTable::setOpCount(unsigned long index, unsigned int opCount) {
    fit();
    if (index < instrStream.size())
        instrStream[index].uiOpCount = opCount;
}

void InstrTable::setValueList(unsigned long index, const std::vector<Value> &valueList) {
    fit();
    if (index < instrStream.size())
        instrStream[index].ValueList = valueList;
}

unsigned long InstrTable::getSize() {
    return uiSize;
}

int InstrTable::getOpType(unsigned int uiOpIndex) {
    return getCurrentInstr().getOp(uiOpIndex).iType;
}

void InstrTable::addInstr(const Instr &ins) {
    instrStream.emplace_back(ins);
}

Instr InstrTable::getInstr(unsigned long index) {
    fit();
    if (index >= instrStream.size())
        return Instr(0);
    return instrStream.at(index);
}

Instr InstrTable::getCurrentInstr() {
    return getInstr(getCurrentIndex());
}

void InstrTable::setInstr(unsigned long index, const Instr &instr) {
    fit();
    if (index >= instrStream.size())
        return;
    instrStream[index] = instr;
}

void InstrTable::setCurrentIndex(unsigned int index) {
    uiCurrentInstrIndex = index;
}

void InstrTable::incCurrentIndex() {
    ++uiCurrentInstrIndex;
}