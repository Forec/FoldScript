//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_LABTABLE_H
#define FOLDSCRIPT_LABTABLE_H

#include <string>
#include <unordered_map>
#include "labnode.h"
#include "../../utils/utils.h"

/*
 * LabelTable: 标签表
 * @iTable: 标签映射
 *
 * @addLabel: 根据标签名和所在函数索引添加标签信息，返回添加的标签索引，若冲突则返回 -1
 * @getLabel: 根据标签名和所在函数索引获取标签信息，不存在时返回的标签信息中索引为 -1
 */

class LabelTable {
private:
    std::unordered_map<kpair, LabelNode, hash_func, cmp_func> iTable;
public:
    LabelTable();
    void reset();
    unsigned long getSize();
    int addLabel(const std::string &name, unsigned int targetIndex, unsigned int funcIndex);
    LabelNode getLabel(const std::string &name, unsigned int funcIndex);
};

#endif //FOLDSCRIPT_LABTABLE_H
