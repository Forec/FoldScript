//
// Created by 王耀 on 2017/11/11.
//

#ifndef FOLDSCRIPT_VM_MACRO_H
#define FOLDSCRIPT_VM_MACRO_H

/*
 * FEC 可执行文件格式
 */
#define EXEC_FILE_EXT                 ".FEC"   // 可执行文件扩展名
#define FEC_ID_STRING                 "FEC0"   // FEC 可执行文件标识符

/*
 * 虚拟机加载状态
 */
#define LOAD_OK                       0        // 成功加载 FEC 可执行文件
#define LOAD_ERROR_FILE_IO            1        // 文件 I/O 操作失败（如文件不存在）
#define LOAD_ERROR_INVALID_FEC        2        // 非法的 FEC 文件结构
#define LOAD_ERROR_UNSUPPORTED_VERS   3        // FEC 文件版本不支持

/*
 * 默认信息及限制
 */
#define DEF_STACK_SIZE                1024     // 默认堆栈大小
#define MAX_COERCION_STRING_SIZE      65       // 待定







/*
 * 以下部分与 fasm/utils/macro.h 中定义一致
 */

/*
 * FEC 操作码宏定义
 */

#define OP_TYPE_NULL                  0xFF     // 未初始化数据
#define OP_TYPE_INT                   0x00     // 整型
#define OP_TYPE_FLOAT                 0x01     // 浮点型
#define OP_TYPE_STRING_INDEX          0x02     // 字符串
#define OP_TYPE_ABS_STACK_INDEX       0x03     // 绝对堆栈索引
#define OP_TYPE_REL_STACK_INDEX       0x04     // 相对堆栈索引
#define OP_TYPE_INSTR_INDEX           0x05     // 指令索引
#define OP_TYPE_FUNC_INDEX            0x06     // 函数索引
#define OP_TYPE_HOST_API_CALL_INDEX   0x07     // 系统调用索引
#define OP_TYPE_REG                   0x08     // 寄存器

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

#endif //FOLDSCRIPT_VM_MACRO_H
