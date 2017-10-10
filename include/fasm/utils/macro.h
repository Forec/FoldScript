//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_MACRO_H
#define FOLDSCRIPT_MACRO_H

/*
 * 操作系统相关
 */
#define LINUX_CLASS

#ifdef LINUX_CLASS
#define CODE_LINE_DELIMITER '\n'
#else
#define CODE_LINE_DELIMITER "\r\n"
#endif

/*
 * 词法相关分隔符定义
 */
#define CODE_STRING_DELIMITER '"'
#define CODE_COMMENT_DELIMITER ';'

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

/*
 * 属性字类型
 */
#define TOKEN_TYPE_INT                0x00
#define TOKEN_TYPE_FLOAT              0x01
#define TOKEN_TYPE_STRING             0x02
#define TOKEN_TYPE_QUOTE              0x03     // 双引号
#define TOKEN_TYPE_IDENT              0x04     // 标识符
#define TOKEN_TYPE_COLON              0x05     // 冒号
#define TOKEN_TYPE_OPEN_BRACKET       0x06     // 左中括号
#define TOKEN_TYPE_CLOSE_BRACKET      0x07     // 右中括号
#define TOKEN_TYPE_COMMA              0x08     // 逗号
#define TOKEN_TYPE_OPEN_BRACE         0x09     // 左大括号
#define TOKEN_TYPE_CLOSE_BRACE        0x0A     // 右大括号
#define TOKEN_TYPE_NEWLINE            0x0B     // 换行

#define TOKEN_TYPE_INSTR		      0x0C	   // 指令

#define TOKEN_TYPE_SETSTACKSIZE       0x0D     // SetStackSize 指令
#define TOKEN_TYPE_VAR                0x0E     // 变量声明保留字
#define TOKEN_TYPE_FUNC               0x0F     // 函数声明保留字
#define TOKEN_TYPE_PARAM              0x10     // 参数声明保留字
#define TOKEN_TYPE_REG_RETVAL         0x11     // _RetVar 寄存器

#define TOKEN_TYPE_INVALID            0x12     // 非法属性字
#define END_OF_TOKEN_STREAM           0x13     // 到达属性字流末尾

/*
 * 词法分析器状态
 */
#define LEX_STATE_NO_STRING           0x00     // 默认
#define LEX_STATE_IN_STRING           0x01     // 字符串中
#define LEX_STATE_END_STRING          0x02     // 字符串结束

#endif //FOLDSCRIPT_MACRO_H
