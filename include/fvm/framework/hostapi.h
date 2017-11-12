//
// Created by 王耀 on 2017/11/12.
//

#ifndef FOLDSCRIPT_VM_HOSTAPI_H
#define FOLDSCRIPT_VM_HOSTAPI_H

#include <string>
#include <vector>

/*
 * HostAPICallTable: 系统调用表
 */

class HostAPICallTable {
private:
    std::vector<std::string> calls;
public:
    HostAPICallTable();
    ~HostAPICallTable();
    void reset();
    void append(const std::string& name);
    unsigned long getSize();
};

#endif //FOLDSCRIPT_VM_HOSTAPI_H
