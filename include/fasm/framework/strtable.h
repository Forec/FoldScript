//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_STRTABLE_H
#define FOLDSCRIPT_STRTABLE_H

#include <string>
#include <unordered_map>
#include <vector>

class StringTable {
private:
    std::unordered_map<std::string, unsigned int> iMap;
    std::vector<std::string> iTable;
public:
    StringTable();
    ~StringTable();
    void reset();
    unsigned long getSize();
    unsigned int insert(const std::string & string);
};

#endif //FOLDSCRIPT_STRTABLE_H
