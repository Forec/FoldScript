//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_SYMNODE_H
#define FOLDSCRIPT_SYMNODE_H

/*
 * SymbolNode: 符号节点（变量）
 * @iIndex: 符号索引
 * @iSize: 该符号代表的大小（变量为 1，数组为 N）
 * @iStackIndex: 符号指向的堆栈索引
 * @iFuncIndex: 符号所在的函数索引
 */


class SymbolNode {
private:
    int iIndex;
    unsigned int iSize;
    int iStackIndex;
    unsigned int iFuncIndex;
public:
    SymbolNode();
    SymbolNode(int stackIndex, unsigned int funcIndex, unsigned int size = 1);
    void setIndex(int index);
    int getIndex();
    int getStackIndex();
    unsigned int getSize();
};

#endif //FOLDSCRIPT_SYMNODE_H
