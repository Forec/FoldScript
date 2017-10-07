//
// Created by 王耀 on 2017/10/7.
//

#include "functable.h"

FuncTable::FuncTable() {
    iTable.clear();
}

int FuncTable::addFunction(const std::string &name, int iEntryPoint) {
    if (iTable.find(name) != iTable.end())    // 已存在同名函数，返回无效索引
        return -1;
    FuncNode func(iEntryPoint);
    func.setIndex((int)iTable.size());
    iTable.insert(std::make_pair(name, func));
    return func.getIndex();
}

void FuncTable::setFunction(const std::string &name, unsigned int iParamCount, unsigned int iLocalDataSize) {
    auto pair = iTable.find(name);
    if (pair == iTable.end())
        return;
    pair->second.setParamCount(iParamCount);
    pair->second.setLocalDataSize(iLocalDataSize);
}

FuncNode FuncTable::getFunction(const std::string &name) {
    auto pair = iTable.find(name);
    if (pair == iTable.end())
        return FuncNode(0);
    return pair->second;
}