//
// Created by 王耀 on 2017/11/12.
//

#ifndef FOLDSCRIPT_VM_FUNCTABLE_H
#define FOLDSCRIPT_VM_FUNCTABLE_H

#include <vector>

/*
 * Func: 函数
 * @uiEntryPoint: 函数入口地址
 * @uiParamCount: 函数参数数量
 * @uiLocalDataSize: 函数局部数据大小
 * @uiStackFrameSize: 函数堆栈大小 = 局部数据大小 + 参数大小 + 1（返回地址）
 */

struct Func {
    unsigned int uiEntryPoint;
    unsigned int uiParamCount;
    unsigned int uiLocalDataSize;
    unsigned int uiStackFrameSize;
    Func();
    Func(unsigned int, unsigned int, unsigned int, unsigned int);
};

/*
 * FuncTable: 函数表
 */

class FuncTable {
private:
    std::vector<Func> functions;
public:
    FuncTable();
    ~FuncTable();
    void reset();
    void append(Func function);
    unsigned long getSize();
    Func getFunction(unsigned long index);
};

#endif //FOLDSCRIPT_VM_FUNCTABLE_H
