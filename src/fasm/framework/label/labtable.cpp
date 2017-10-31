//
// Created by 王耀 on 2017/10/8.
//

#include "labtable.h"

LabelTable::LabelTable() {
    iTable.clear();
}

void LabelTable::reset() {
    iTable.clear();
}

int LabelTable::addLabel(const std::string &name, unsigned int targetIndex, unsigned int funcIndex) {
    if (getLabel(name, funcIndex).getIndex() != -1)
        return -1;
    LabelNode node((int)iTable.size(), targetIndex, funcIndex);
    iTable.insert(std::make_pair(std::make_pair(name, funcIndex), node));
    return node.getIndex();
}

LabelNode LabelTable::getLabel(const std::string &name, unsigned int funcIndex) {
    auto pair = iTable.find(std::make_pair(name, funcIndex));
    if (pair == iTable.end())
        return LabelNode{};
    return pair->second;
}

unsigned long LabelTable::getSize() {
    return iTable.size();
}