//
// Created by 王耀 on 2017/11/11.
//

#ifndef FOLDSCRIPT_VM_STACK_H
#define FOLDSCRIPT_VM_STACK_H

#include <vector>
#include "value.h"

class RuntimeStack {
private:
    std::vector<Value> elems;                   // 元素栈
    unsigned int uiSize;                        // 堆栈大小
    int iFrameIndex;                            // 当前堆栈框架顶部的索引
public:
    RuntimeStack();
    ~RuntimeStack();
    void reset();
    void setSize(unsigned int size);
    unsigned int getSize();
};

#endif //FOLDSCRIPT_VM_STACK_H
