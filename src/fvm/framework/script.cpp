//
// Created by 王耀 on 2017/11/12.
//

#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "macro.h"
#include "utils.h"
#include "script.h"

Script::Script() {
    instructions = new InstrTable();
    stack = new RuntimeStack();
    functions = new FuncTable();
    apis = new HostAPICallTable();
    init();
}

Script::~Script() {
    delete apis;
    delete functions;
    delete stack;
    delete instructions;
}

void Script::init() {
    iExitCode = 0;
    uiStreamSize = 0;
    uiGlobalDataSize = 0;
    ulPauseEndStamp = 0;
    uiMainFuncIndex = 0;

    isHeaderLoaded = false;
    isHeaderValid = true;
    isMainFuncPresent = false;
    isPaused = false;

    instructions->reset();
    stack->reset();
    functions->reset();
    apis->reset();
}

void Script::reset() {
    if (isMainFuncPresent)
        instructions->setCurrentIndex(functions->getFunction(uiMainFuncIndex).uiEntryPoint);

    stack->reset();

    isPaused = false;

    stack->pushFrame(uiGlobalDataSize);
    stack->pushFrame(functions->getFunction(uiMainFuncIndex).uiStackFrameSize + 1);
}

void Script::fit() {
    stack->fit();
    instructions->fit();
}

void Script::setExecutableFile(const std::string &path) {
    reset();
    executableFile = path;
}

Status Script::loadHeader() {
    isHeaderLoaded = true;
    isHeaderValid = true;
    std::ifstream reader;
    reader.open(executableFile, std::ios_base::binary | std::ios_base::in);
    if (reader.fail()) {                                                 // 文件不存在或无读权限
        reader.close();
        isHeaderValid = false;
        return LOAD_ERROR_FILE_IO;
    }
    char buffer[8];
    memset(buffer, 0, sizeof(buffer));
    reader.read(buffer, 4);                                              // 4B FEC文件标识符
    if (std::string(buffer) != FEC_ID_STRING) {                          // 可执行文件格式不正确
        reader.close();
        isHeaderValid = false;
        return LOAD_ERROR_INVALID_FEC;
    }

    char majorVersion = 0, minorVersion = 0;
    reader.read(&majorVersion, 1);                                       // 1B 主版本号
    reader.read(&minorVersion, 1);                                       // 1B 次版本号

    if (majorVersion != VERSION_MAJOR || minorVersion != VERSION_MINOR) {// 版本不兼容
        reader.close();
        isHeaderValid = false;
        return LOAD_ERROR_UNSUPPORTED_VERS;
    }

    unsigned int uiStackSize = 0;
    reader.read((char *)&uiStackSize, 4);                                // 4B 堆栈空间大小
    stack->setSize(uiStackSize == 0 ? DEF_STACK_SIZE : uiStackSize);

    reader.read((char *)&uiGlobalDataSize, 4);                           // 4B 全局数据大小

    char tmp = 0;
    reader.read(&tmp, 1);                                                // 1B 主函数存在标示
    isMainFuncPresent = tmp == 1;
    reader.read((char *)&uiMainFuncIndex, 4);                            // 4B 主函数索引

    reader.read((char *)&uiStreamSize, 4);                               // 4B 指令流长度
    instructions->setSize(uiStreamSize);

    reader.close();
    return LOAD_OK;
}

bool Script::isValid() {
    if (!isHeaderLoaded)                                                 // 文件元信息未加载时先加载文件头
        loadHeader();
    return isHeaderValid;
}

bool Script::loadCode() {
    if (!isValid())                                                      // 判断文件是否合法
        return false;

    std::ifstream reader;
    reader.open(executableFile, std::ios_base::binary | std::ios_base::in);
    if (reader.fail()) {
        reader.close();
        return false;
    }

    fit();                                                               // 动态分配内存

    reader.seekg(23, std::ios_base::beg);                                // 定位至指令流开始处

    std::unordered_map<int, std::unordered_set<unsigned int>> string2InstrIndex;

    unsigned int uiOpCode = 0, uiOpCount = 0;
    for (unsigned int uiCurrInstrIndex = 0; uiCurrInstrIndex < uiStreamSize; ++uiCurrInstrIndex) {
        uiOpCode = 0; uiOpCount = 0;
        reader.read((char *)&uiOpCode, 2);                               // 2B 操作码
        reader.read((char *)&uiOpCount, 1);                              // 1B 操作数数量

        std::vector<Value> valueList;

        for (unsigned int uiCurrOpIndex = 0; uiCurrOpIndex < uiOpCount; ++uiCurrOpIndex) {
            Value value;
            reader.read((char *)&(value.iType), 1);

            switch(value.iType) {
                case OP_TYPE_INT:                                        // 普通整型数据：2/4B int
                    reader.read((char *)&(value.iIntLiteral), sizeof(int));
                    break;
                case OP_TYPE_FLOAT:                                      // 普通浮点数据：4B float
                    reader.read((char *)&(value.fFloatLiteral), sizeof(float));
                    break;
                case OP_TYPE_STRING:                                     // 字符串索引：2/4B int
                    reader.read((char *)&(value.iIntLiteral), sizeof(int));
                    if (string2InstrIndex.find(value.iIntLiteral) == string2InstrIndex.end())
                        string2InstrIndex.insert(std::make_pair(value.iIntLiteral, std::unordered_set<unsigned int>()));
                    string2InstrIndex[value.iIntLiteral].insert(uiCurrInstrIndex);
                    break;
                case OP_TYPE_INSTR_INDEX:                                // 指令索引：2/4B unsigned int
                    reader.read((char *)&(value.uiInstrIndex), sizeof(unsigned int));
                    break;
                case OP_TYPE_ABS_STACK_INDEX:                            // 堆栈绝对索引：2/4B int
                    reader.read((char *)&(value.iStackIndex), sizeof(int));
                    break;
                case OP_TYPE_REL_STACK_INDEX:                            // 堆栈相对索引：4/8B 2 x int
                    reader.read((char *)&(value.iStackIndex), sizeof(int));
                    reader.read((char *)&(value.iOffsetIndex), sizeof(int));
                    break;
                case OP_TYPE_FUNC_INDEX:                                 // 函数索引：2/4B int
                    reader.read((char *)&(value.iFuncIndex), sizeof(int));
                    break;
                case OP_TYPE_HOST_API_CALL_INDEX:                        // 系统调用索引：2/4B unsigned int
                    reader.read((char *)&(value.uiHostAPICallIndex), sizeof(unsigned int));
                    break;
                case OP_TYPE_REG:                                        // 寄存器索引：2/4B unsigned
                    reader.read((char *)&(value.uiReg), sizeof(unsigned int));
                    break;
                default:
                    return false;
            }

            valueList.emplace_back(value);
        }

        Instr instruction(uiOpCode, uiOpCount, valueList);
        instructions->setInstr(uiCurrInstrIndex, instruction);
    }

    // 读取字符串表
    unsigned long ulStringTableSize = 0;
    reader.read((char *)&ulStringTableSize, sizeof(unsigned long));      // 字符串表长度：4/8B

    for (unsigned long ulStringIndex = 0; ulStringIndex < ulStringTableSize; ++ulStringIndex) {
        unsigned long ulStringLength = 0;
        reader.read((char *)&ulStringLength, sizeof(unsigned long));     // 字符串长度：4/8B
        auto buffer = new char[ulStringLength + 1];
        reader.read(buffer, ulStringLength);                             // 字符串：长度不定
        buffer[ulStringLength] = '\0';

        auto instrIndex = string2InstrIndex.find((int)ulStringIndex);    // 根据字符串索引获取引用了该字符串的指令索引
        if (instrIndex == string2InstrIndex.end()) {
            delete []buffer;
            continue;
        }

        std::unordered_set<unsigned int> instrSet = instrIndex->second;
        for (unsigned int index: instrSet) {                             // 对每条引用了字符串的指令，更新其字符串指针
            Instr matchedInstr = instructions->getInstr(index);
            for (auto& iterator : matchedInstr.ValueList) {
                if (iterator.iType == OP_TYPE_STRING && iterator.iIntLiteral == (int)ulStringIndex) {
                    iterator.sStrLiteral = std::string(buffer);
                }
            }
        }

        delete []buffer;
    }

    // 读取函数表
    unsigned int functableSize = 0;
    reader.read((char *)&functableSize, sizeof(unsigned int));           // 函数表长度：2/4B
    for (unsigned int uiCurrFuncIndex = 0; uiCurrFuncIndex < functableSize; ++uiCurrFuncIndex) {
        unsigned int entryPoint = 0;
        reader.read((char *)&entryPoint, sizeof(unsigned int));          // 函数入口点：2/4B
        unsigned int paramCount = 0;
        reader.read((char *)&paramCount, sizeof(unsigned int));          // 函数参数数量：2/4B
        unsigned int localDataSize = 0;
        reader.read((char *)&localDataSize, sizeof(unsigned int));       // 局部数据大小
        unsigned int stackFrameSize = paramCount + 1 + localDataSize;
        functions->append(Func{entryPoint, paramCount, localDataSize, stackFrameSize});
    }

    // 读取系统调用表
    unsigned int apiTableSize = 0;
    reader.read((char *)&apiTableSize, sizeof(unsigned int));            // 系统调用表长度：2/4B
    for (unsigned int uiCurrCallIndex = 0; uiCurrCallIndex < apiTableSize; uiCurrCallIndex++) {
        unsigned int callLength = 0;
        reader.read((char *)&callLength, sizeof(unsigned int));          // 系统调用名长度：2/4B
        auto buffer = new char[callLength + 1];
        reader.read(buffer, callLength);                                 // 系统调用
        buffer[callLength] = '\0';
        apis->append(buffer);
        delete []buffer;
    }

    reader.close();
    return true;
}

std::string Script::status2string() {
    if (!isValid())
        return "文件 \"" + executableFile + "\" 加载失败！";
    std::ostringstream ss;
    ss << "文件 \"" << executableFile << "\" 元信息:" << std::endl;
    ss << "  文件版本: " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
    ss << "  堆栈大小: " << stack->getSize() << std::endl;
    ss << "  全局空间: " << uiGlobalDataSize << std::endl;
    ss << "  函数定义: " << functions->getSize() << std::endl;
    ss << "  指令长度: " << uiStreamSize << std::endl;
    ss << "  系统调用: " << apis->getSize() << std::endl;
    ss << "  主函数" << (isMainFuncPresent ? "" : "不") << "存在"
       << (isMainFuncPresent ? ", 主函数下标为 " + std::to_string(uiMainFuncIndex) : "") << std::endl;
    ss.flush();
    return ss.str();
}

void Script::run() {
    bool exitExecution = false;
    while (true) {
        if (isPaused) {                                                  // 当前脚本处于等待状态
            if (getCurrentTimestamp() >= ulPauseEndStamp)                // 检查是否可以激活 TODO：从忙等改为中断
                isPaused = false;
            else
                continue;
        }
        unsigned int currentInstrIndex = instructions->getCurrentIndex();
        Instr currentInstr = instructions->getCurrentInstr();

        switch (currentInstr.uiOpCode) {
            case INSTR_MOV:
            case INSTR_ADD:
            case INSTR_SUB:
            case INSTR_MUL:
            case INSTR_DIV:
            case INSTR_MOD:
            case INSTR_EXP:
            case INSTR_AND:
            case INSTR_OR:
            case INSTR_XOR:
            case INSTR_SHL:
            case INSTR_SHR: {
                Value &dest = resolveOpRef(0);
                Value source = resolveOp(1);

                switch (currentInstr.uiOpCode) {
                    case INSTR_MOV:
                        dest = source;
                        break;
                    case INSTR_ADD:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral += source.toInt();
                        else if (dest.iType == OP_TYPE_FLOAT)
                            dest.fFloatLiteral += source.toFloat();
                        else
                            exitOnInvalidOp();
                        break;
                    case INSTR_SUB:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral -= source.toInt();
                        else if (dest.iType == OP_TYPE_FLOAT)
                            dest.fFloatLiteral -= source.toFloat();
                        else exitOnInvalidOp();
                        break;
                    case INSTR_MUL:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral *= source.toInt();
                        else if (dest.iType == OP_TYPE_FLOAT)
                            dest.fFloatLiteral *= source.toFloat();
                        else exitOnInvalidOp();
                        break;
                    case INSTR_DIV: {
                        if (dest.iType == OP_TYPE_INT) {
                            int divider = source.toInt();
                            if (divider == 0)
                                exitOnError("除 0 异常");
                            dest.iIntLiteral /= divider;
                        } else if (dest.iType == OP_TYPE_FLOAT) {
                            float divider = source.toFloat();
                            if (divider == 0.0)
                                exitOnError("除 0 异常");
                            dest.fFloatLiteral /= divider;
                        } else exitOnInvalidOp();
                        break;
                    }
                    case INSTR_MOD: {
                        int moder = source.toInt();
                        if (moder == 0)
                            exitOnError("模 0 异常");
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral %= moder;
                        else exitOnInvalidOp();
                        break;
                    }
                    case INSTR_AND:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral &= source.toInt();
                        else exitOnInvalidOp();
                        break;
                    case INSTR_OR:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral |= source.toInt();
                        else exitOnInvalidOp();
                        break;
                    case INSTR_XOR:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral ^= source.toInt();
                        else exitOnInvalidOp();
                        break;
                    case INSTR_SHL:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral <<= source.toInt();
                        else exitOnInvalidOp();
                        break;
                    case INSTR_SHR:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral >>= source.toInt();
                        else exitOnInvalidOp();
                        break;
                    default:
                        break;
                }
                break;
            }

            case INSTR_NEG:
            case INSTR_NOT:
            case INSTR_INC:
            case INSTR_DEC: {
                Value &dest = resolveOpRef(0);
                switch (currentInstr.uiOpCode) {
                    case INSTR_NEG:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral = -dest.iIntLiteral;
                        else if (dest.iType == OP_TYPE_FLOAT)
                            dest.fFloatLiteral = -dest.fFloatLiteral;
                        else exitOnInvalidOp();
                        break;
                    case INSTR_NOT:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral = ~dest.iIntLiteral;
                        else exitOnInvalidOp();
                        break;
                    case INSTR_INC:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral++;
                        else if (dest.iType == OP_TYPE_FLOAT)
                            dest.fFloatLiteral++;
                        else exitOnInvalidOp();
                        break;
                    case INSTR_DEC:
                        if (dest.iType == OP_TYPE_INT)
                            dest.iIntLiteral--;
                        else if (dest.iType == OP_TYPE_FLOAT)
                            dest.fFloatLiteral--;
                        else exitOnInvalidOp();
                        break;
                    default:
                        break;
                }
                break;
            }
            case INSTR_CONCAT: {
                Value &dest = resolveOpRef(0);
                std::string append = resolveOp(1).toString();
                if (dest.iType != OP_TYPE_STRING)
                    exitOnInvalidOp();
                dest.sStrLiteral += append;
                break;
            }
            case INSTR_GETCHAR: {
                Value &dest = resolveOpRef(0);
                Value source = resolveOp(1);
                int index = resolveOp(2).toInt();
                std::string str = source.toString();
                dest.sStrLiteral = str.substr((unsigned long)index, 1);
                break;
            }
            case INSTR_SETCHAR: {
                Value &dest = resolveOpRef(0);
                if (dest.iType != OP_TYPE_STRING)
                    exitOnInvalidOp();
                int index = resolveOp(1).toInt();
                std::string str = resolveOp(2).toString();
                if (dest.sStrLiteral.length() < index || str.empty())
                    break;
                dest.sStrLiteral[index] = str[0];
                break;
            }
            case INSTR_JMP: {
                int iTargetIndex = resolveOp(0).toInstrIndex();
                if (iTargetIndex == -1)
                    exitOnInvalidOp();
                instructions->setCurrentIndex((unsigned int)iTargetIndex);
                break;
            }
            case INSTR_JE:
            case INSTR_JNE:
            case INSTR_JG:
            case INSTR_JL:
            case INSTR_JGE:
            case INSTR_JLE: {
                Value op0 = resolveOp(0);
                Value op1 = resolveOp(1);
                int iTargetIndex = resolveOp(2).toInstrIndex();
                if (iTargetIndex == -1)
                    exitOnInvalidOp();

                bool jump = false;

                switch (currentInstr.uiOpCode) {
                    case INSTR_JE: {
                        switch (op0.iType) {
                            case OP_TYPE_INT:
                                if (op0.toInt() == op1.toInt())
                                    jump = true;
                                break;
                            case OP_TYPE_FLOAT:
                                if (op0.toFloat() == op1.toFloat())
                                    jump = true;
                                break;
                            case OP_TYPE_STRING:
                                if (op0.toString() == op1.toString())
                                    jump = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    case INSTR_JNE: {
                        switch (op0.iType) {
                            case OP_TYPE_INT:
                                if (op0.toInt() != op1.toInt())
                                    jump = true;
                                break;
                            case OP_TYPE_FLOAT:
                                if (op0.toFloat() != op1.toFloat())
                                    jump = true;
                                break;
                            case OP_TYPE_STRING:
                                if (op0.toString() != op1.toString())
                                    jump = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    case INSTR_JG: {
                        switch (op0.iType) {
                            case OP_TYPE_INT:
                                if (op0.toInt() > op1.toInt())
                                    jump = true;
                                break;
                            case OP_TYPE_FLOAT:
                                if (op0.toFloat() > op1.toFloat())
                                    jump = true;
                                break;
                            case OP_TYPE_STRING:
                                if (op0.toString() > op1.toString())
                                    jump = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    case INSTR_JL: {
                        switch (op0.iType) {
                            case OP_TYPE_INT:
                                if (op0.toInt() < op1.toInt())
                                    jump = true;
                                break;
                            case OP_TYPE_FLOAT:
                                if (op0.toFloat() < op1.toFloat())
                                    jump = true;
                                break;
                            case OP_TYPE_STRING:
                                if (op0.toString() < op1.toString())
                                    jump = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    case INSTR_JGE: {
                        switch (op0.iType) {
                            case OP_TYPE_INT:
                                if (op0.toInt() >= op1.toInt())
                                    jump = true;
                                break;
                            case OP_TYPE_FLOAT:
                                if (op0.toFloat() >= op1.toFloat())
                                    jump = true;
                                break;
                            case OP_TYPE_STRING:
                                if (op0.toString() >= op1.toString())
                                    jump = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    case INSTR_JLE: {
                        switch (op0.iType) {
                            case OP_TYPE_INT:
                                if (op0.toInt() <= op1.toInt())
                                    jump = true;
                                break;
                            case OP_TYPE_FLOAT:
                                if (op0.toFloat() <= op1.toFloat())
                                    jump = true;
                                break;
                            case OP_TYPE_STRING:
                                if (op0.toString() <= op1.toString())
                                    jump = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    default:
                        break;
                }

                if (jump)
                    instructions->setCurrentIndex((unsigned int)iTargetIndex);
                break;
            }
            case INSTR_PUSH: {
                Value source = resolveOp(0);
                if (!stack->push(source))
                    exitOnError("栈溢出!");
                break;
            }
            case INSTR_POP: {
                resolveOpRef(0) = stack->pop();
                break;
            }
            case INSTR_CALL: {
                int iFuncIndex = resolveOp(0).toFuncIndex();
                if (iFuncIndex == -1)
                    exitOnError("不存在的地址跳转");
                Func dest = functions->getFunction((unsigned int)iFuncIndex);
                Value returnAddr;
                returnAddr.uiInstrIndex = instructions->getCurrentIndex() + 1;
                stack->push(returnAddr);
                stack->pushFrame(dest.uiLocalDataSize + 1);

                Value funcIndex;
                funcIndex.iFuncIndex = iFuncIndex;
                stack->setValue(stack->getTopIndex() - 1, funcIndex);
                instructions->setCurrentIndex(dest.uiEntryPoint);
                break;
            }
            case INSTR_RET: {
                break;
            }
            case INSTR_CALLHOST: {
                // TODO: 下版本实现系统调用
                std::cout << "系统调用 \"" << resolveOp(0).toString() << "\"\n";
                break;
            }
            case INSTR_PAUSE: {
                if (isPaused)
                    break;
                int pauseDuration = resolveOp(0).toInt();
                ulPauseEndStamp = getCurrentTimestamp() + pauseDuration;
                isPaused = true;
                break;
            }
            case INSTR_EXIT: {
                iExitCode = resolveOp(0).toInt();
                exitExecution = true;
                break;
            }
            default:
                break;
        }

        if (currentInstrIndex == instructions->getCurrentIndex())
            instructions->incCurrentIndex();

        if (exitExecution)
            break;
    }
}

Value Script::resolveOp(unsigned int uiOpIndex) {
    Instr currentInstr = instructions->getCurrentInstr();
    Value opValue = currentInstr.getOp(uiOpIndex);
    switch (opValue.iType) {
        case OP_TYPE_ABS_STACK_INDEX:
        case OP_TYPE_REL_STACK_INDEX: {
            int iAbsIndex = resolveOpStackIndex(uiOpIndex);
            return stack->getValue(iAbsIndex);
        }
        case OP_TYPE_REG:
            return _RetVal;
        default:
            return opValue;
    }
}

Value & Script::resolveOpRef(unsigned int uiOpIndex) {
    switch (instructions->getOpType(uiOpIndex)) {
        case OP_TYPE_REG:
            return _RetVal;
        case OP_TYPE_REL_STACK_INDEX:
        case OP_TYPE_ABS_STACK_INDEX: {
            int stackIndex = resolveOpStackIndex(uiOpIndex);
            return stack->getValueRef(stack->resolveIndex(stackIndex));
        }
        default:
            return null;
    }
}

int Script::resolveOpType(unsigned int uiOpIndex) {
    return resolveOp(uiOpIndex).iType;
}

int Script::resolveOpStackIndex(unsigned int uiOpIndex) {
    Instr currentInstr = instructions->getCurrentInstr();
    Value opValue = currentInstr.getOp(uiOpIndex);
    switch (opValue.iType) {
        case OP_TYPE_ABS_STACK_INDEX:
            return opValue.iStackIndex;
        case OP_TYPE_REL_STACK_INDEX: {
            Value stackValue = stack->getValue(opValue.iOffsetIndex);
            return opValue.iStackIndex + stackValue.iIntLiteral;
        }
        default:
            return 0;
    }
}

std::string Script::formatOp(unsigned int uiOpIndex) {
    Value opValue = instructions->getCurrentInstr().getOp(uiOpIndex);
    switch (opValue.iType) {
        case OP_TYPE_NULL:
            return "NULL";
        case OP_TYPE_INT:
        case OP_TYPE_FLOAT:
        case OP_TYPE_INSTR_INDEX:
            return std::to_string(opValue.iIntLiteral);
        case OP_TYPE_STRING:
            return "\"" + opValue.sStrLiteral + "\"";
        case OP_TYPE_HOST_API_CALL_INDEX:
            return apis->getCall(opValue.toHostApiIndex());
        default:
            return "NOP";
    }
}