//
// Created by 王耀 on 2017/10/7.
//

#include "funcnode.h"

FuncNode::FuncNode(int entryPoint, unsigned int paramCount, unsigned int localDataSize) {
    iEntryPoint = entryPoint;
    iParamCount = paramCount;
    iLocalDataSize = localDataSize;
    iIndex = -1;
}
