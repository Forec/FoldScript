//
// Created by 王耀 on 2017/10/7.
//

#include <new>
#include "symnode.h"

SymbolNode::SymbolNode() {
    iIndex = -1;
    iStackIndex = 0;
    uiSize = 1;
    uiFuncIndex = 0;
}

SymbolNode::SymbolNode(int stackIndex, unsigned int funcIndex, unsigned int size) {
    new (this)SymbolNode(-1, stackIndex, funcIndex, size);
}

SymbolNode::SymbolNode(int index, int stackIndex, unsigned int funcIndex, unsigned int size) {
    iIndex = index;
    iStackIndex = stackIndex;
    uiSize = size;
    uiFuncIndex = funcIndex;
}