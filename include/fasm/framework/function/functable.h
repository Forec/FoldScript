//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_ASM_FUNCTABLE_H
#define FOLDSCRIPT_ASM_FUNCTABLE_H

#include <string>
#include <unordered_map>
#include "funcnode.h"

/*
 * FuncTable: 函数表
 * @iTable: 函数名称->信息映射
 *
 * @addFunction: 将新函数添加至函数表，只提供函数入口点，其余属性在语法分析时更新
 * @setFunction: 在语法分析时更新函数的参数个数和局部数据大小
 * @getFunction: 根据函数名称从函数表获取函数信息，不存在对应名称的函数时返回的信息中 iIndex 为 -1
 */

class FuncTable {
private:
    std::unordered_map<std::string, FuncNode> iTable;
public:
    FuncTable();
    ~FuncTable();
    void reset();
    unsigned long getSize();
    int addFunction(const std::string & name, int entryPoint);
    void setFunction(const std::string & name, unsigned int paramCount, unsigned int localDataSize);
    FuncNode getFunction(const std::string & name);
};

#endif //FOLDSCRIPT_ASM_UNCTABLE_H
