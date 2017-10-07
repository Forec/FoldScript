//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_FUNCNODE_H
#define FOLDSCRIPT_FUNCNODE_H

/*
 * FuncNode: 函数
 * @iIndex: 函数索引
 * @iEntryPoint: 函数入口点
 * @iParamCount: 函数参数个数
 * @iLocalDataSize: 局部数据大小
 * @iName: 函数名称
 */

class FuncNode {
private:
    int iIndex;
    int iEntryPoint;
    unsigned int iParamCount;
    unsigned int iLocalDataSize;
public:
    explicit FuncNode(int entryPoint, unsigned int paramCount = 0, unsigned int localDataSize = 0);
    int getIndex() { return iIndex; }
    void setIndex(int index) { iIndex = index; }
    void setParamCount(unsigned int paramCount) { iParamCount = paramCount; }
    void setLocalDataSize(unsigned int localDataSize) { iLocalDataSize = localDataSize; }
    int getEntryPoint() { return iEntryPoint; }
    unsigned int getParamCount() { return iParamCount; }
    unsigned int getLocalDataSize() { return iLocalDataSize; }
};

#endif //FOLDSCRIPT_FUNCNODE_H
