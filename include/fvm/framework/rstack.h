//
// Created by 王耀 on 2017/11/11.
//

#ifndef FOLDSCRIPT_VM_STACK_H
#define FOLDSCRIPT_VM_STACK_H

#include <vector>
#include "value.h"

/*
 * RuntimeStack: 运行时堆栈
 * @elems: 元素栈
 * @uiSize: 堆栈大小
 * @iFrameIndex: 当前堆栈框架顶部的索引
 *
 * @setSize(): 设置堆栈大小，堆栈不会自动调整元素栈的容量，需通过 fit 自适应
 */

class RuntimeStack {
private:
    std::vector<Value> elems;
    Value exception;
    unsigned int iTop;
    unsigned int uiSize;
    int iFrameIndex;
public:
    RuntimeStack();
    ~RuntimeStack();
    void reset();
    void setSize(unsigned int size);
    void fit();
    void pushFrame(unsigned int size);
    unsigned int getSize();
    unsigned int getTopIndex();
    int resolveIndex(int iIndex);
    Value getValue(int iIndex);
    Value &getValueRef(int iIndex);
    bool setValue(int iIndex, Value val);
    bool push(Value val);
    Value pop();
};

#endif //FOLDSCRIPT_VM_STACK_H
