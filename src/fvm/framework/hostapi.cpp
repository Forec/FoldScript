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