//
// Created by 王耀 on 2017/11/11.
//

#ifndef FOLDSCRIPT_VM_VALUE_H
#define FOLDSCRIPT_VM_VALUE_H

/*
* Value: 运行时值
* @iType: 值类型
* @union: 实际值
* @iOffsetIndex: 偏移量索引，仅在操作数为相对堆栈索引时使用，此时 iStackIndex 对应堆栈基址，iOffSetIndex 对应偏移量
*/

struct Value {
    int iType;                                  // 类型
    union {
        int iIntLiteral;                        // 整型
        float fFloatLiteral;                    // 浮点型
        char * sStrLiteral;				        // 字符串指针
        int iStackIndex;                        // 堆栈索引
        int iFuncIndex;                         // 函数索引
        int uiInstrIndex;                       // 指令索引
        unsigned int uiHostAPICallIndex;        // 系统调用索引
        unsigned int uiReg;                     // 寄存器编号
    };
    int iOffsetIndex;
};

#endif //FOLDSCRIPT_VM_VALUE_H
