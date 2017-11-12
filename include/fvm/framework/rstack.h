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
 * @setSize(): 设置堆栈大小，堆栈会自动调整元素栈的容量
 */

class RuntimeStack {
private:
    std::vector<Value> elems;
    unsigned int uiSize;
    int iFrameIndex;
public:
    RuntimeStack();
    ~RuntimeStack();
    void reset();
    void setSize(unsigned int size);
    unsigned int getSize();
};

#endif //FOLDSCRIPT_VM_STACK_H
