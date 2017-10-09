//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_MACRO_H
#define FOLDSCRIPT_MACRO_H

/*
 * 操作数类型宏定义
 */

#define OP_FLAG_TYPE_INT              0x01     // 整型
#define OP_FLAG_TYPE_FLOAT            0x02     // 浮点型
#define OP_FLAG_TYPE_STRING           0x04     // 字符串
#define OP_FLAG_TYPE_MEM_REF          0x08     // 内存引用（变量或数组索引）
#define OP_FLAG_TYPE_LINE_LABEL       0x10     // 行标签（用于跳转指令）
#define OP_FLAG_TYPE_FUNC_NAME        0x20     // 函数名（用于 Call 指令）
#define OP_FLAG_TYPE_HOST_API_CALL    0x40     // 系统调用（用于 CallHost 指令）
#define OP_FLAG_TYPE_REG              0x80     // 寄存器类型

#define OP_FLAG_TYPE_NORMAL           (OP_FLAG_TYPE_INT     | OP_FLAG_TYPE_FLOAT | OP_FLAG_TYPE_STRING | \
                                       OP_FLAG_TYPE_MEM_REF | OP_FLAG_TYPE_REG)
#define OP_FLAG_TYPE_STRCLASS         (OP_FLAG_TYPE_MEM_REF | OP_FLAG_TYPE_REG   | OP_FLAG_TYPE_STRING)
#define OP_FLAG_TYPE_TARGET           (OP_FLAG_TYPE_MEM_REF | OP_FLAG_TYPE_REG)

/*
 * 助记符宏定义
 */
#define INSTR_NOP_STR                 "NOP"    // 空转指令
#define INSTR_MOV_STR                 "MOV"    // 赋值指令

#define INSTR_ADD_STR                 "ADD"    // 常见二元、一元算术运算符
#define INSTR_SUB_STR                 "SUB"
#define INSTR_MUL_STR                 "MUL"
#define INSTR_DIV_STR                 "DIV"
#define INSTR_MOD_STR                 "MOD"
#define INSTR_EXP_STR                 "EXP"
#define INSTR_NEG_STR                 "NEG"
#define INSTR_INC_STR                 "INC"
#define INSTR_DEC_STR                 "DEC"

#define INSTR_AND_STR                 "AND"    // 逻辑运算符
#define INSTR_OR_STR                  "OR"
#define INSTR_XOR_STR                 "XOR"
#define INSTR_NOT_STR                 "NOT"
#define INSTR_SHL_STR                 "SHL"
#define INSTR_SHR_STR                 "SHR"

#define INSTR_CONCAT_STR              "CONCAT" // 字符串操作
#define INSTR_GETCHAR_STR             "GETCHAR"
#define INSTR_SETCHAR_STR             "SETCHAR"

#define INSTR_JMP_STR                 "JMP"    // 跳转指令
#define INSTR_JE_STR                  "JE"
#define INSTR_JNE_STR                 "JNE"
#define INSTR_JG_STR                  "JG"
#define INSTR_JL_STR                  "JL"
#define INSTR_JGE_STR                 "JGE"
#define INSTR_JLE_STR                 "JLE"

#define INSTR_PUSH_STR                "PUSH"   // 堆栈指令
#define INSTR_POP_STR                 "POP"

#define INSTR_CALL_STR                "CALL"   // 函数调用指令
#define INSTR_RET_STR                 "RET"
#define INSTR_CALLHOST_STR            "CALLHOST"

#define INSTR_PAUSE_STR               "PAUSE"  // 控制指令
#define INSTR_EXIT_STR                "EXIT"

/*
 * 操作码宏定义
 */
#define INSTR_NOP                     0x00     // 空转指令
#define INSTR_MOV                     0x01     // 赋值指令

#define INSTR_ADD                     0x02     // 常见二元、一元算术运算符
#define INSTR_SUB                     0x03
#define INSTR_MUL                     0x04
#define INSTR_DIV                     0x05
#define INSTR_MOD                     0x06
#define INSTR_EXP                     0x07
#define INSTR_NEG                     0x08
#define INSTR_INC                     0x09
#define INSTR_DEC                     0x0A

#define INSTR_AND                     0x0B     // 逻辑运算符
#define INSTR_OR                      0x0C
#define INSTR_XOR                     0x0D
#define INSTR_NOT                     0x0E
#define INSTR_SHL                     0x0F
#define INSTR_SHR                     0x10

#define INSTR_CONCAT                  0x11     // 字符串操作
#define INSTR_GETCHAR                 0x12
#define INSTR_SETCHAR                 0x13

#define INSTR_JMP                     0x14     // 跳转指令
#define INSTR_JE                      0x15
#define INSTR_JNE                     0x16
#define INSTR_JG                      0x17
#define INSTR_JL                      0x18
#define INSTR_JGE                     0x19
#define INSTR_JLE                     0x1A

#define INSTR_PUSH                    0x1B     // 堆栈指令
#define INSTR_POP                     0x1C

#define INSTR_CALL                    0x1D     // 函数调用指令
#define INSTR_RET                     0x1E
#define INSTR_CALLHOST                0x1F

#define INSTR_PAUSE                   0x20     // 控制指令
#define INSTR_EXIT                    0x21

#endif //FOLDSCRIPT_MACRO_H
