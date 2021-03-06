//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_ASM_OP_H
#define FOLDSCRIPT_ASM_OP_H

/*
* Op: 操作数
* @iType: 操作数类型
* @union: 操作数对应值
* @iOffsetIndex: 偏移量索引，仅在操作数为相对堆栈索引时使用，此时 iStackIndex 对应堆栈基址，iOffSetIndex 对应偏移量
*/

struct Op {
    unsigned char iType;
    union {
        int iIntLiteral;                         // 整型
        float fFloatLiteral;                     // 浮点型
        int iFuncIndex;                          // 函数索引
        int iStackIndex;                         // 堆栈索引
        unsigned int uiStringTableIndex;         // 字符串表索引
        unsigned int uiInstrIndex;               // 指令索引
        unsigned int uiHostAPICallIndex;         // 系统 API 调用编号
        unsigned int uiReg;                      // 寄存器编号
    };
    int iOffsetIndex;
};

#endif //FOLDSCRIPT_ASM_OP_H
