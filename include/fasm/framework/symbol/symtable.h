//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_SYMTABLE_H
#define FOLDSCRIPT_SYMTABLE_H

#include "symnode.h"
#include <utility>
#include <functional>
#include <string>
#include <unordered_map>

/*
 * SymbolTable: 符号表
 * @iTable: 局部符号表，以符号名和该符号所处的函数索引为键，映射到该符号的具体信息
 * @iGlobal: 全局符号表
 *
 * @addSymbol: 向符号表中添加全局／局部符号，若与已有符号冲突则返回 -1
 * @getSymbol: 根据符号名和符号所处的函数索引（若为全局符号则忽略）来确定符号信息
 */

typedef std::pair<std::string, unsigned int> kpair;

struct hash_func {
    size_t operator()(const kpair &pair) const {
        std::hash<std::string> h;
        size_t string_hash = h(pair.first);
        return string_hash + pair.second;
    }
};

struct cmp_func {
    bool operator()(const kpair &k1, const kpair &k2) const {
        return k1.first == k2.first && k1.second == k2.second;
    }
};

class SymbolTable {
private:
    std::unordered_map<kpair, SymbolNode, hash_func, cmp_func> iTable;
    std::unordered_map<std::string, SymbolNode> iGlobal;
public:
    SymbolTable();
    int addSymbol(const std::string &ident, unsigned int size, int stackIndex, unsigned int funcIndex);
    SymbolNode getSymbol(const std::string &ident, unsigned int funcIndex = 0);
    int getStackIndex(const std::string &ident, unsigned int funcIndex = 0);
    int getSize(const std::string &ident, unsigned int funcIndex = 0);
};

#endif //FOLDSCRIPT_SYMTABLE_H
