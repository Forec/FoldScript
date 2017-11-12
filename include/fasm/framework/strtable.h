//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_ASM_STRTABLE_H
#define FOLDSCRIPT_ASM_STRTABLE_H

#include <string>
#include <unordered_map>
#include <vector>

/*
 * StringTable: 字符串表，存储脚本中使用到的字符串常量
 * @iMap: 字符串到字符串索引的映射
 * @iTable: 字符串索引到字符串的映射
 */

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
    std::string getString(unsigned int index);
};

#endif //FOLDSCRIPT_ASM_STRTABLE_H
