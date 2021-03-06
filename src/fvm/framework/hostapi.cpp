//
// Created by 王耀 on 2017/11/12.
//

#include "hostapi.h"

HostAPICallTable::HostAPICallTable() {
    reset();
}

HostAPICallTable::~HostAPICallTable() {
    reset();
}

void HostAPICallTable::reset() {
    calls.clear();
}

void HostAPICallTable::append(const std::string &name) {
    calls.emplace_back(name);
}

unsigned long HostAPICallTable::getSize() {
    return calls.size();
}

std::string HostAPICallTable::getCall(unsigned int uiCallIndex) {
    if (uiCallIndex >= calls.size())
        return "NOP";
    return calls.at(uiCallIndex);
}