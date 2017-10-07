//
// Created by 王耀 on 2017/10/7.
//

#include "symnode.h"

SymbolNode::SymbolNode() {
    iIndex = -1;
    iSize = 1;
    iStackIndex = 0;
    iFuncIndex = 0;
}

SymbolNode::SymbolNode(int stackIndex, unsigned int funcIndex, unsigned int size) {
    iIndex = -1;
    iSize = size;
    iStackIndex = stackIndex;
    iFuncIndex = funcIndex;
}

void SymbolNode::setIndex(int index) {
    iIndex = index;
}

int SymbolNode::getIndex() {
    return iIndex;
}

int SymbolNode::getStackIndex() {
    return iStackIndex;
}

unsigned int SymbolNode::getSize() {
    return iSize;
}