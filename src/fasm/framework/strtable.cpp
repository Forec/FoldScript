//
// Created by 王耀 on 2017/10/7.
//

#include "strtable.h"

StringTable::StringTable() {
    reset();
}

StringTable::~StringTable() {
    iMap.clear();
    iTable.clear();
}

void StringTable::reset() {
    iMap.clear();
    iTable.clear();
    insert("");
}


unsigned int StringTable::insert(const std::string &string) {
    auto pair = iMap.find(string);
    if (pair != iMap.end())
        return pair->second;
    iTable.emplace_back(string);
    iMap.insert(std::make_pair(string, iTable.size() - 1));
    return (unsigned int)iTable.size() - 1;
}

unsigned long StringTable::getSize() {
    return iTable.size();
}