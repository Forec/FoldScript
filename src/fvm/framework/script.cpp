//
// Created by 王耀 on 2017/11/12.
//

#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include "macro.h"
#include "utils.h"
#include "script.h"

Script::Script() {
    instructions = new InstrTable();
    stack = new RuntimeStack();
    functions = new FuncTable();
    apis = new HostAPICallTable();
    reset();
}

Script::~Script() {
    delete apis;
    delete functions;
    delete stack;
    delete instructions;
}

void Script::reset() {
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
        reader.read((char *)&ulStringLength, sizeof(unsigned long));
        auto buffer = new char[ulStringLength + 1];
        reader.read(buffer, ulStringLength);
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
                    iterator.sStrLiteral = buffer;
                }
            }
        }
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
        reader.read(buffer, callLength);
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
    ss << "\"" << executableFile << "\" 加载成功!" << std::endl;
    ss << "    文件版本: " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
    ss << "    堆栈大小: " << stack->getSize() << std::endl;
    ss << "    全局空间: " << uiGlobalDataSize << std::endl;
    ss << "    函数定义: " << functions->getSize() << std::endl;
    ss << "    指令长度: " << uiStreamSize << std::endl;
    ss << "    系统调用: " << apis->getSize() << std::endl;
    ss << "主函数" << (isMainFuncPresent ? "" : "不") << "存在"
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
                Value dest = currentInstr.ValueList[0];
            }
        }
    }
}

Value Script::resolveOp(unsigned int uiOpIndex) {
    Instr currentInstr = instructions->getCurrentInstr();
    Value opValue = currentInstr.getOp(uiOpIndex);
    switch (opValue.iType) {
        case OP_TYPE_ABS_STACK_INDEX:
        case OP_TYPE_REL_STACK_INDEX: {
            int iAbsIndex = resolveOpStackIndex(uiOpIndex);
            return getStackValue(iAbsIndex);
        }
        case OP_TYPE_REG:
            return _RetVal;
        default:
            return opValue;
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
            Value stackValue = getStackValue(opValue.iOffsetIndex);
            return opValue.iStackIndex + stackValue.iIntLiteral;
        }
        default:
            return 0;
    }
}

// TODO
Value Script::getStackValue(int stackIndex) {
    return Value{0, 0, 0};
}