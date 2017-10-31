//
// Created by 王耀 on 2017/10/7.
//

#include "symtable.h"

SymbolTable::SymbolTable() {
    iTable.clear();
    iGlobal.clear();
}

void SymbolTable::reset() {
    iTable.clear();
    iGlobal.clear();
}

int SymbolTable::addSymbol(const std::string &ident, unsigned int size, int stackIndex, unsigned int funcIndex) {
    if (getSymbol(ident, funcIndex).getIndex() != -1)     // 已存在同名符号且位于同一函数内（或与全局符号冲突）
        return -1;
    SymbolNode symNode((int)(iTable.size() + iGlobal.size()), stackIndex, funcIndex, size);

    // 根据该符号在栈区偏移量的正负确定该符号为全局／局部变量
    if (stackIndex >= 0)
        iGlobal.insert(std::make_pair(ident, symNode));
    else
        iTable.insert(std::make_pair(std::make_pair(ident, funcIndex), symNode));
    return symNode.getIndex();
}

SymbolNode SymbolTable::getSymbol(const std::string &ident, unsigned int funcIndex) {
    // 首先查询全局符号中是否存在声明
    auto gPair = iGlobal.find(ident);
    if (gPair != iGlobal.end()) {
        return gPair->second;
    }

    // 按符号名和函数索引查询局部符号表
    auto lPair = iTable.find(std::make_pair(ident, funcIndex));
    if (lPair == iTable.end())
        return SymbolNode{};
    return lPair->second;
}

int SymbolTable::getStackIndex(const std::string &ident, unsigned int funcIndex) {
    return getSymbol(ident, funcIndex).getStackIndex();
}

int SymbolTable::getSize(const std::string &ident, unsigned int funcIndex) {
    return getSymbol(ident, funcIndex).getSize();
}

unsigned long SymbolTable::getGlobalCount() {
    return iGlobal.size();
}

std::pair<unsigned long, unsigned long> SymbolTable::getSymbolCount() {
    std::pair<unsigned long, unsigned long> count = std::make_pair(0, 0);
    for (auto iterator: iTable) {
        if (iterator.second.getSize() > 1)
            count.second++;
        else
            count.first++;
    }
    for (auto iterator: iGlobal) {
        if (iterator.second.getSize() > 1)
            count.second++;
        else
            count.first++;
    }
    return count;
}