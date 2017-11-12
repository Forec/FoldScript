//
// Created by 王耀 on 2017/11/12.
//

#ifndef FOLDSCRIPT_VM_HOSTAPI_H
#define FOLDSCRIPT_VM_HOSTAPI_H

#include <string>
#include <vector>

class HostAPICallTable {
private:
    std::vector<std::string> calls;
public:
    HostAPICallTable();
    ~HostAPICallTable();
    void reset();
};

#endif //FOLDSCRIPT_VM_HOSTAPI_H
