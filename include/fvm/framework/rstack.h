//
// Created by 王耀 on 2017/11/11.
//

#ifndef FOLDSCRIPT_VM_STACK_H
#define FOLDSCRIPT_VM_STACK_H

#include <stack>
#include "value.h"

class RuntimeStack {
    std::stack<Value> elems;                    // 元素栈
    int iFrameIndex;                            // 当前堆栈框架顶部的索引
};

#endif //FOLDSCRIPT_VM_STACK_H
