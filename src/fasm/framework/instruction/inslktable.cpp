//
// Created by 王耀 on 2017/10/8.
//

#include "inslktable.h"
#include "macro.h"

InstrLookupTable::InstrLookupTable() {
    iTable.clear();
}

bool InstrLookupTable::addInstrLookup(const std::string &mnemonic, unsigned int opCode, unsigned int opCount) {
    if (iTable.find(mnemonic) != iTable.end())
        return false;
    iTable.insert(std::make_pair(mnemonic, InstrLookup(opCode, opCount)));
    return true;
}

InstrLookup InstrLookupTable::getInstrLookup(const std::string &mnemonic) {
    auto pair = iTable.find(mnemonic);
    if (pair == iTable.end())
        return InstrLookup(0, 0);
    return pair->second;
}

void InstrLookupTable::setInstrOpType(const std::string &mnemonic, unsigned int opIndex, OpTypes type) {
    InstrLookup instr = getInstrLookup(mnemonic);
    if (instr.getOpCode() != 0) {
        instr.setOpType(opIndex, type);
        iTable.erase(mnemonic);
        iTable.insert(std::make_pair(mnemonic, instr));
    }
}

OpTypes InstrLookupTable::getInstrOpType(const std::string &mnemonic, unsigned int opIndex) {
    InstrLookup instr = getInstrLookup(mnemonic);
    return instr.getOpType(opIndex);
}

void InstrLookupTable::init() {
    // 空转指令
    addInstrLookup(INSTR_NOP_STR, INSTR_NOP, 0);

    // 赋值指令
    addInstrLookup(INSTR_MOV_STR, INSTR_MOV, 2);
    setInstrOpType(INSTR_MOV_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_MOV_STR, 1, OP_FLAG_TYPE_NORMAL);

    // 常见二元、一元运算符
    addInstrLookup(INSTR_ADD_STR, INSTR_ADD, 2);
    setInstrOpType(INSTR_ADD_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_ADD_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_SUB_STR, INSTR_SUB, 2);
    setInstrOpType(INSTR_SUB_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_SUB_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_MUL_STR, INSTR_MUL, 2);
    setInstrOpType(INSTR_MUL_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_MUL_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_DIV_STR, INSTR_DIV, 2);
    setInstrOpType(INSTR_DIV_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_DIV_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_MOD_STR, INSTR_MOD, 2);
    setInstrOpType(INSTR_MOD_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_MOD_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_EXP_STR, INSTR_EXP, 2);
    setInstrOpType(INSTR_EXP_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_EXP_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_NEG_STR, INSTR_NEG, 1);
    setInstrOpType(INSTR_NEG_STR, 0, OP_FLAG_TYPE_TARGET);

    addInstrLookup(INSTR_INC_STR, INSTR_INC, 1);
    setInstrOpType(INSTR_INC_STR, 0, OP_FLAG_TYPE_TARGET);

    addInstrLookup(INSTR_DEC_STR, INSTR_DEC, 1);
    setInstrOpType(INSTR_DEC_STR, 0, OP_FLAG_TYPE_TARGET);

    // 逻辑运算符
    addInstrLookup(INSTR_AND_STR, INSTR_AND, 2);
    setInstrOpType(INSTR_AND_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_AND_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_OR_STR, INSTR_OR, 2);
    setInstrOpType(INSTR_OR_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_OR_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_XOR_STR, INSTR_XOR, 2);
    setInstrOpType(INSTR_XOR_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_XOR_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_NOT_STR, INSTR_DEC, 1);
    setInstrOpType(INSTR_NOT_STR, 0, OP_FLAG_TYPE_TARGET);

    addInstrLookup(INSTR_SHL_STR, INSTR_SHL, 2);
    setInstrOpType(INSTR_SHL_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_SHL_STR, 1, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_SHR_STR, INSTR_SHR, 2);
    setInstrOpType(INSTR_SHR_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_SHR_STR, 1, OP_FLAG_TYPE_NORMAL);

    // 字符串操作
    addInstrLookup(INSTR_CONCAT_STR, INSTR_CONCAT, 2);
    setInstrOpType(INSTR_CONCAT_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_CONCAT_STR, 1, OP_FLAG_TYPE_STRCLASS);

    addInstrLookup(INSTR_GETCHAR_STR, INSTR_GETCHAR, 3);
    setInstrOpType(INSTR_GETCHAR_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_GETCHAR_STR, 1, OP_FLAG_TYPE_STRCLASS);
    setInstrOpType(INSTR_GETCHAR_STR, 2, OP_FLAG_TYPE_TARGET | OP_FLAG_TYPE_INT);

    addInstrLookup(INSTR_SETCHAR_STR, INSTR_SETCHAR, 2);
    setInstrOpType(INSTR_SETCHAR_STR, 0, OP_FLAG_TYPE_TARGET);
    setInstrOpType(INSTR_SETCHAR_STR, 1, OP_FLAG_TYPE_TARGET | OP_FLAG_TYPE_INT);
    setInstrOpType(INSTR_SETCHAR_STR, 2, OP_FLAG_TYPE_STRCLASS);

    // 条件跳转指令
    addInstrLookup(INSTR_JMP_STR, INSTR_JMP, 1);
    setInstrOpType(INSTR_JMP_STR, 0, OP_FLAG_TYPE_LINE_LABEL);

    addInstrLookup(INSTR_JE_STR, INSTR_JE, 3);
    setInstrOpType(INSTR_JE_STR, 0, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JE_STR, 1, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JE_STR, 2, OP_FLAG_TYPE_LINE_LABEL);

    addInstrLookup(INSTR_JNE_STR, INSTR_JNE, 3);
    setInstrOpType(INSTR_JNE_STR, 0, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JNE_STR, 1, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JNE_STR, 2, OP_FLAG_TYPE_LINE_LABEL);

    addInstrLookup(INSTR_JG_STR, INSTR_JG, 3);
    setInstrOpType(INSTR_JG_STR, 0, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JG_STR, 1, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JG_STR, 2, OP_FLAG_TYPE_LINE_LABEL);

    addInstrLookup(INSTR_JL_STR, INSTR_JL, 3);
    setInstrOpType(INSTR_JL_STR, 0, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JL_STR, 1, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JL_STR, 2, OP_FLAG_TYPE_LINE_LABEL);

    addInstrLookup(INSTR_JGE_STR, INSTR_JGE, 3);
    setInstrOpType(INSTR_JGE_STR, 0, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JGE_STR, 1, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JGE_STR, 2, OP_FLAG_TYPE_LINE_LABEL);

    addInstrLookup(INSTR_JLE_STR, INSTR_JLE, 3);
    setInstrOpType(INSTR_JLE_STR, 0, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JLE_STR, 1, OP_FLAG_TYPE_NORMAL);
    setInstrOpType(INSTR_JLE_STR, 2, OP_FLAG_TYPE_LINE_LABEL);

    // 堆栈指令
    addInstrLookup(INSTR_PUSH_STR, INSTR_PUSH, 1);
    setInstrOpType(INSTR_PUSH_STR, 0, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_POP_STR, INSTR_POP, 1);
    setInstrOpType(INSTR_POP_STR, 0, OP_FLAG_TYPE_TARGET);

    // 函数调用指令
    addInstrLookup(INSTR_CALL_STR, INSTR_CALL, 1);
    setInstrOpType(INSTR_CALL_STR, 0, OP_FLAG_TYPE_FUNC_NAME);

    addInstrLookup(INSTR_RET_STR, INSTR_RET, 0);

    addInstrLookup(INSTR_CALLHOST_STR, INSTR_CALLHOST, 1);
    setInstrOpType(INSTR_CALLHOST_STR, 0, OP_FLAG_TYPE_HOST_API_CALL);

    // 控制指令
    addInstrLookup(INSTR_PAUSE_STR, INSTR_PAUSE, 1);
    setInstrOpType(INSTR_PAUSE_STR, 0, OP_FLAG_TYPE_NORMAL);

    addInstrLookup(INSTR_EXIT_STR, INSTR_EXIT, 1);
    setInstrOpType(INSTR_EXIT_STR, 0, OP_FLAG_TYPE_NORMAL);
}
