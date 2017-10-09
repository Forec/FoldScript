//
// Created by 王耀 on 2017/10/7.
//

#include <new>
#include "funcnode.h"

FuncNode::FuncNode(int entryPoint, unsigned int paramCount, unsigned int localDataSize) {
    new (this)FuncNode(-1, entryPoint, paramCount, localDataSize);
}

FuncNode::FuncNode(int index, int entryPoint, unsigned int paramCount, unsigned int localDataSize) {
    iIndex = index;
    iEntryPoint = entryPoint;
    uiParamCount = paramCount;
    uiLocalDataSize = localDataSize;
}