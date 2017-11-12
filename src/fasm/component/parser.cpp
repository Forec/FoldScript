//
// Created by 王耀 on 2017/10/14.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include "utils.h"
#include "macro.h"
#include "instrlookup.h"
#include "parser.h"

Parser::Parser() {
    lexer = new Lexer();
    functions = new FuncTable();
    symbols = new SymbolTable();
    labels = new LabelTable();
    instructions = new InstrTable();
    strings = new StringTable();
    hostapis = new StringTable();
    reset();
}

Parser::~Parser() {
    delete hostapis;
    delete strings;
    delete instructions;
    delete labels;
    delete symbols;
    delete functions;
    delete lexer;
}

void Parser::reset() {
    uiStackSize = 0;
    uiGlobalDataSize = 0;
    uiCurrentInstrIndex = 0;
    uiCurrentFuncLocalDataSize = 0;
    uiCurrentFuncParamCount = 0;
    iInstrStreamSize = 0;
    uiCurrentFuncIndex = 0;
    uiMainFuncIndex = 0;
    isMainFunctionPresent = false;
    isSetStackSizeFound = false;
    isFuncActive = false;
    currentFunction = FuncNode(0, 0);
    execFilename = "default.fec";

    lexer->reset();
    functions->reset();
    symbols->reset();
    labels->reset();
    instructions->reset();
    strings->reset();
    hostapis->reset();
}

void Parser::codeError(const std::string &err) {
    std::string LineInfo = "第 " + std::to_string(lexer->getCurrentSourceLine() + 1 + lexer->getSource()->getSkipLine()) + " 行: ";
    std::cerr << "错误: " << err << std::endl << LineInfo;
    std::cerr << lexer->getSource()->readCompressedLine(lexer->getCurrentSourceLine()) << std::endl;
    std::string space;
    space.resize(lexer->getFirstIndex() + LineInfo.length(), ' ');
    std::cerr << space << "^" << std::endl;
    exitOnError("无法汇编文件 \"" + lexer->getSource()->getFilename() +  "\"");
}

void Parser::charExpectError(char code) {
    codeError("缺少" + std::to_string(code));
}

void Parser::setExecFilename(const std::string & name) {
    execFilename = name;
}

void Parser::initFromString(const std::string &str) {
    reset();
    lexer->initFromString(str);
}

bool Parser::initFromFile(const std::string &path) {
    reset();
    return lexer->initFromFile(path);
}

void Parser::assemble() {
    reset();

    while(true) {                                                       // 第一次遍历，构建标识符表等
        if (lexer->getNextToken() == END_OF_TOKEN_STREAM)
            break;

        switch(lexer->getCurrentToken()) {
            case TOKEN_TYPE_SETSTACKSIZE: {                             // 设置程序堆栈大小
                if (isFuncActive)                                       // 元指令必须在全局区域设置
                    codeError(ERROR_MSSG_LOCAL_SETSTACKSIZE);
                if (isSetStackSizeFound)                                // 堆栈大小不可重复设置
                    codeError(ERROR_MSSG_MULTIPLE_SETSTACKSIZES);
                if (lexer->getNextToken() != TOKEN_TYPE_INT)            // 参数必须为正整数
                    codeError(ERROR_MSSG_INVALID_STACK_SIZE);
                if (strtol(lexer->getCurrentLexeme().c_str(), nullptr, 10) < 0)
                    codeError(ERROR_MSSG_INVALID_STACK_SIZE);
                uiStackSize = (unsigned int) strtol(lexer->getCurrentLexeme().c_str(), nullptr, 10);
                isSetStackSizeFound = true;
                break;
            }
            case TOKEN_TYPE_FUNC: {
                if (isFuncActive)                                       // 不可出现函数嵌套 TODO: 支持函数嵌套
                    codeError(ERROR_MSSG_NESTED_FUNC);
                if (lexer->getNextToken() != TOKEN_TYPE_IDENT)          // 函数声明后必须为标识符
                    codeError(ERROR_MSSG_IDENT_EXPECTED);
                int funcIndex = functions->addFunction(lexer->getCurrentLexeme(), iInstrStreamSize);
                if (-1 == funcIndex)                                    // 不可重复定义同名函数
                    codeError(ERROR_MSSG_FUNC_REDEFINITION);
                uiCurrentFuncIndex = (unsigned int)funcIndex;
                currentFuncName = lexer->getCurrentLexeme();
                if (currentFuncName == GRAMMAR_MAIN_FUNC_NAME) {        // 定义主函数
                    isMainFunctionPresent = true;
                    uiMainFuncIndex = uiCurrentFuncIndex;
                }
                isFuncActive = true;
                while (lexer->getNextToken() == TOKEN_TYPE_NEWLINE);    // 过滤掉函数标识符之后紧随的一系列空字符
                if (lexer->getCurrentToken() != TOKEN_TYPE_OPEN_BRACE)  // 函数标识符后必须跟随左花括号
                    charExpectError('{');
                ++iInstrStreamSize;                                     // 函数末尾自动附加 RET，因此增加指令流大小
                break;
            }
            case TOKEN_TYPE_CLOSE_BRACE:{
                if (!isFuncActive)                                      // 出现花括号表明当前应处于函数内部
                        charExpectError('}');
                functions->setFunction(currentFuncName, uiCurrentFuncParamCount, uiCurrentFuncLocalDataSize);
                isFuncActive = false;
                uiCurrentFuncIndex = 0;
                uiCurrentFuncParamCount = 0;
                uiCurrentFuncLocalDataSize = 0;
                break;
            }
            case TOKEN_TYPE_VAR: {
                if (lexer->getNextToken() != TOKEN_TYPE_IDENT)          // VAR 后应当跟随标识符定义变量
                    codeError(ERROR_MSSG_IDENT_EXPECTED);
                std::string currentVar = lexer->getCurrentLexeme();
                unsigned int uiSize = 1;
                if (lexer->getLookAheadChar() == '[') {                 // 标识符后跟随左中括号表明定义数组
                    if (lexer->getNextToken() != TOKEN_TYPE_OPEN_BRACKET)
                        charExpectError('[');
                    if (lexer->getNextToken() != TOKEN_TYPE_INT)        // 数组大小必须为正整数
                        codeError(ERROR_MSSG_INVALID_ARRAY_SIZE);
                    long iSize = strtol(lexer->getCurrentLexeme().c_str(), nullptr, 10);
                    if (iSize <= 0)
                        codeError(ERROR_MSSG_INVALID_ARRAY_SIZE);
                    if (lexer->getNextToken() != TOKEN_TYPE_CLOSE_BRACKET) // 数组大小后应当紧随右中括号
                        charExpectError(']');
                    uiSize = (unsigned int) iSize;
                }
                int iStackIndex;
                if (isFuncActive) {                                     // 根据是否在函数内确定变量对应全局／局部
                    iStackIndex = -(uiCurrentFuncLocalDataSize + 2);
                    uiCurrentFuncLocalDataSize += uiSize;
                } else {
                    iStackIndex = (int) uiGlobalDataSize;
                    uiGlobalDataSize += uiSize;
                }
                if (-1 == symbols->addSymbol(currentVar, uiSize, iStackIndex, uiCurrentFuncIndex))
                    codeError(ERROR_MSSG_IDENT_REDEFINITION);
                break;
            }
            case TOKEN_TYPE_PARAM: {
                if (!isFuncActive)                                      // 参数只能在函数内部定义
                    codeError(ERROR_MSSG_GLOBAL_PARAM);
                if (currentFuncName == GRAMMAR_MAIN_FUNC_NAME)          // 主函数中无法声明参数
                    codeError(ERROR_MSSG_MAIN_PARAM);
                if (lexer->getNextToken() != TOKEN_TYPE_IDENT)          // PARAM 后应当紧随标识符
                    codeError(ERROR_MSSG_IDENT_EXPECTED);
                ++uiCurrentFuncParamCount;                              // 增加当前函数的参数数量
                break;
            }
            case TOKEN_TYPE_IDENT: {
                if (lexer->getLookAheadChar() != ':')                   // 标识符不可独立存在，其后跟冒号表明为行标签
                    codeError(ERROR_MSSG_INVALID_INSTR);
                if (!isFuncActive)                                      // 行标签只能定义在函数内部
                    codeError(ERROR_MSSG_GLOBAL_LINE_LABEL);
                unsigned int iTargetIndex = (unsigned int)iInstrStreamSize - 1;     // 目标指令为当前指令的地址
                if (-1 == labels->addLabel(lexer->getCurrentLexeme(), iTargetIndex, uiCurrentFuncIndex))
                    codeError(ERROR_MSSG_LINE_LABEL_REDEFINITION);
                break;
            }
            case TOKEN_TYPE_INSTR: {
                if (!isFuncActive)
                    codeError(ERROR_MSSG_GLOBAL_INSTR);
                iInstrStreamSize++;
                break;
            }
            default: {
                if (lexer->getCurrentToken() != TOKEN_TYPE_NEWLINE)
                    codeError(ERROR_MSSG_INVALID_INPUT);
            }
        }
        if (!lexer->skipLine())
            break;
    }

    instructions->resize((unsigned long)iInstrStreamSize);              // 将指令表的大小置为第一次遍历后得到的大小
    lexer->reset();

    // 已完成第一次遍历，假设语法没有错误

    while (true) {                                                      // 第二次遍历，汇编为二进制代码
        if (lexer->getNextToken() == END_OF_TOKEN_STREAM)
            break;

        switch (lexer->getCurrentToken()) {
            case TOKEN_TYPE_FUNC: {
                lexer->getNextToken();
                currentFuncName = lexer->getCurrentLexeme();
                currentFunction = functions->getFunction(currentFuncName);
                uiCurrentFuncIndex = (unsigned int) currentFunction.getIndex();             // 保存当前函数索引
                isFuncActive = true;
                uiCurrentFuncParamCount = 0;                                                // 重置当前函数参数数量
                while (lexer->getNextToken() == TOKEN_TYPE_NEWLINE);
                break;
            }
            case TOKEN_TYPE_CLOSE_BRACE: {                                                  // 遇到右花括号时表示函数结束，增加额外的 RET 或 EXIT 指令
                Instr endInstr(INSTR_EXIT, 1);
                isFuncActive = false;
                if (currentFuncName == GRAMMAR_MAIN_FUNC_NAME) {                            // 当前函数为 Main，退出时增加 exit 指令
                    endInstr.OpList.emplace_back(Op{OP_TYPE_INT, 0, 0});
                } else {
                    endInstr.uiOpCode = INSTR_RET;
                    endInstr.uiOpCount = 0;
                }
                instructions->setInstr(uiCurrentInstrIndex++, endInstr);                    // 将 RET 或 EXIT 指令加入函数末尾
                break;
            }
            case TOKEN_TYPE_PARAM: {                                                        // 第二次遍历遇到参数时需要将其加入参数表
                if (lexer->getNextToken() != TOKEN_TYPE_IDENT)
                    codeError(ERROR_MSSG_IDENT_EXPECTED);
                int iStackIndex = -(currentFunction.getLocalDataSize() + 2 + uiCurrentFuncParamCount + 1);
                if (-1 == symbols->addSymbol(lexer->getCurrentLexeme(), 1, iStackIndex, uiCurrentFuncIndex))
                    codeError(ERROR_MSSG_IDENT_REDEFINITION);
                ++uiCurrentFuncParamCount;
                break;
            }
            case TOKEN_TYPE_INSTR: {
                InstrLookup instr = lexer->getLookupTable()->getInstrLookup(lexer->getCurrentLexeme());
                instructions->setOpCode(uiCurrentInstrIndex, instr.getOpCode());
                instructions->setOpCount(uiCurrentInstrIndex, instr.getOpCount());
                std::vector<Op> opList;
                for (unsigned int uiOpIndex = 0; uiOpIndex < instr.getOpCount(); ++uiOpIndex) {
                    OpTypes currentOpTypes = instr.getOpType(uiOpIndex);                    // 获得该位置参数可选类型的 BIT 表示
                    Op currentOp{0, 0, 0};
                    Token initOpToken = lexer->getNextToken();
                    switch (initOpToken) {
                        case TOKEN_TYPE_INT: {
                            if (currentOpTypes & OP_FLAG_TYPE_INT) {
                                currentOp.iType = OP_TYPE_INT;
                                currentOp.iIntLiteral = (int) strtol(lexer->getCurrentLexeme().c_str(), nullptr, 10);
                            } else
                                codeError(ERROR_MSSG_INVALID_OP);
                            break;
                        }
                        case TOKEN_TYPE_FLOAT: {
                            if (currentOpTypes & OP_FLAG_TYPE_FLOAT) {
                                currentOp.iType = OP_TYPE_FLOAT;
                                currentOp.fFloatLiteral = strtof(lexer->getCurrentLexeme().c_str(), nullptr);
                            } else
                                codeError(ERROR_MSSG_INVALID_OP);
                            break;
                        }
                        case TOKEN_TYPE_QUOTE: {                                            // 遇到双引号则识别字符串
                            if (currentOpTypes & OP_FLAG_TYPE_STRING) {
                                lexer->getNextToken();
                                currentOp.iType = OP_TYPE_STRING_INDEX;
                                switch (lexer->getCurrentToken()) {
                                    case TOKEN_TYPE_QUOTE: {                                // 左右双引号紧邻则字符串为空
                                        currentOp.uiStringTableIndex = 0;                   // 空字符串对应字符串表中第一行
                                        break;
                                    }
                                    case TOKEN_TYPE_STRING: {
                                        currentOp.uiStringTableIndex = strings->insert(lexer->getCurrentLexeme());
                                        if (lexer->getNextToken() != TOKEN_TYPE_QUOTE)
                                            charExpectError('\\');                          // 不允许跨行等无双引号结尾的字符串 TODO: 允许跨行定义字符串
                                        break;
                                    }
                                    default:
                                        codeError(ERROR_MSSG_INVALID_STRING);
                                        break;
                                }
                            } else
                                codeError(ERROR_MSSG_INVALID_OP);
                            break;
                        }
                        case TOKEN_TYPE_REG_RETVAL: {
                            if (currentOpTypes & OP_FLAG_TYPE_REG) {
                                currentOp.iType = OP_TYPE_REG;
                                currentOp.uiReg = 0;
                            } else
                                codeError(ERROR_MSSG_INVALID_OP);
                            break;
                        }
                        case TOKEN_TYPE_IDENT: {
                            // 标识符对应的操作数可能为：[变量、数组]、[行标识符]、[函数]、[系统调用]，且彼此之间不可能并存

                            if (currentOpTypes & OP_FLAG_TYPE_MEM_REF) {                    // 此时该标识符可能为变量或者数组
                                std::string currentIdent = lexer->getCurrentLexeme();
                                SymbolNode node = symbols->getSymbol(currentIdent, uiCurrentFuncIndex);
                                if (node.getIndex() == -1)                                  // 确保该变量或数组已被定义过
                                    codeError(ERROR_MSSG_UNDEFINED_IDENT);
                                int iBaseIndex = node.getStackIndex();
                                if (lexer->getLookAheadChar() != '[') {                     // 该标识符确定为非数组变量
                                    if (node.getSize() > 1)
                                        codeError(ERROR_MSSG_INVALID_ARRAY_NOT_INDEXED);
                                    currentOp.iType = OP_TYPE_ABS_STACK_INDEX;
                                    currentOp.iStackIndex = iBaseIndex;
                                } else {
                                    if (node.getSize() == 1)                                // 数组长度应当大于 1  TODO：允许数组长度声明为 0 或 1
                                        codeError(ERROR_MSSG_INVALID_ARRAY);
                                    if (lexer->getNextToken() != TOKEN_TYPE_OPEN_BRACKET)   // 确保数组后跟随索引 TODO：允许使用数组指针（需要支持指针类型）
                                        charExpectError('[');
                                    Token indexToken = lexer->getNextToken();
                                    if (indexToken == TOKEN_TYPE_INT) {
                                        int iOffsetIndex = (int)strtol(lexer->getCurrentLexeme().c_str(), nullptr, 10);
                                        if (iOffsetIndex < 0) {
                                            iOffsetIndex = node.getSize() + iOffsetIndex;
                                            if (iOffsetIndex < 0)                           // 允许数组下标为负数，但若绝对值超过数组长度则视作违例
                                                codeError(ERROR_MSSG_INVALID_ARRAY_INDEX);
                                        }
                                        currentOp.iType = OP_TYPE_ABS_STACK_INDEX;
                                        currentOp.iStackIndex = iBaseIndex + iOffsetIndex;
                                    } else if (indexToken == TOKEN_TYPE_IDENT) {            // 数组下标为标识符
                                        std::string indexIdent = lexer->getCurrentLexeme();
                                        SymbolNode indexNode = symbols->getSymbol(indexIdent, uiCurrentFuncIndex);
                                        if (indexNode.getIndex() == -1)
                                            codeError(ERROR_MSSG_UNDEFINED_IDENT);
                                        if (indexNode.getSize() > 1)                        // 指令下标只能为单个标识符而不能为数组元素 TODO：允许使用数组元素作为数组下标
                                            codeError(ERROR_MSSG_INVALID_ARRAY_INDEX);
                                        currentOp.iType = OP_TYPE_REL_STACK_INDEX;
                                        currentOp.iStackIndex = iBaseIndex;                 // 该数组下标为间接地址
                                        currentOp.iOffsetIndex = indexNode.getStackIndex();
                                    } else {
                                        codeError(ERROR_MSSG_INVALID_ARRAY_INDEX);
                                    }
                                    if (lexer->getNextToken() != TOKEN_TYPE_CLOSE_BRACKET)  // 下标应以右中括号结尾
                                        charExpectError(']');
                                }
                            }

                            else if (currentOpTypes & OP_FLAG_TYPE_LINE_LABEL) {            // 此时标识符可能为行标签
                                LabelNode labelNode = labels->getLabel(lexer->getCurrentLexeme(), uiCurrentFuncIndex);
                                if (labelNode.getIndex() == -1)                             // 行标签必须已定义
                                    codeError(ERROR_MSSG_UNDEFINED_LINE_LABEL);
                                currentOp.iType = OP_TYPE_INSTR_INDEX;                      // 操作数类型为指令地址
                                currentOp.uiInstrIndex = (unsigned int)labelNode.getIndex();
                            }

                            else if (currentOpTypes & OP_FLAG_TYPE_FUNC_NAME) {             // 此时标识符可能为函数名
                                FuncNode funcNode = functions->getFunction(lexer->getCurrentLexeme());
                                if (funcNode.getIndex() == -1)                              // 函数必须在第一遍扫描时定义
                                    codeError(ERROR_MSSG_UNDEFINED_FUNC);
                                currentOp.iType = OP_TYPE_FUNC_INDEX;
                                currentOp.iFuncIndex = funcNode.getIndex();
                            }

                            else if (currentOpTypes & OP_FLAG_TYPE_HOST_API_CALL) {         // 此时标识符可能为系统调用
                                unsigned int apiIndex = hostapis->insert(lexer->getCurrentLexeme());
                                currentOp.iType = OP_TYPE_HOST_API_CALL_INDEX;
                                currentOp.uiHostAPICallIndex = apiIndex;
                            }

                            break;
                        }
                        default: {
                            codeError(ERROR_MSSG_INVALID_OP);
                            break;
                        }
                    }
                    opList.emplace_back(currentOp);

                    if (uiOpIndex < instr.getOpCount() - 1 && lexer->getNextToken() != TOKEN_TYPE_COMMA)
                        charExpectError(',');                                               // 非最后一个参数，后要跟分隔符
                }

                instructions->setOpList(uiCurrentInstrIndex++, opList);
                break;
            }

            // 本轮扫描只生成指令，对其他 token 不关心
            default:
                break;
        }

        if (!lexer->skipLine())
            break;
    }
}

std::string Parser::status2string() {
    auto count = symbols->getSymbolCount();
    unsigned long uiVarCount = count.first, uiArrayCount = count.second, uiGlobalCount = symbols->getGlobalCount();
    std::ostringstream ss;
    ss << "汇编结束!" << std::endl;
    ss << "共处理 " << lexer->getSource()->getSize() << " 行源码" << std::endl;
    ss << "    堆栈大小: " << (uiStackSize > 0 ? std::to_string(uiStackSize) : "Default") << std::endl;
    ss << "    指令数量: " << iInstrStreamSize - functions->getSize() << std::endl;
    ss << "    变量数量: " << uiVarCount << std::endl;
    ss << "    数组数量: " << uiArrayCount << std::endl;
    ss << "    全局变量: " << uiGlobalCount << std::endl;
    ss << "    字符串表: " << strings->getSize() << std::endl;
    ss << "    行标签数: " << labels->getSize() << std::endl;
    ss << "    系统调用: " << hostapis->getSize() << std::endl;
    ss << "    函数定义: " << functions->getSize() << std::endl;
    ss << "主函数" << (isMainFunctionPresent ? "" : "不") << "存在"
       << (isMainFunctionPresent ? ": 主函数下标为 " + std::to_string(uiMainFuncIndex) : "") << std::endl;
    ss.flush();
    return ss.str();
}

void Parser::exportFEC() {
    std::ofstream writer;
    writer.open(execFilename, std::ios_base::binary | std::ios_base::out);
    if (writer.bad())
        exitOnError("无法打开文件 " + execFilename);
    writer.write(FEC_ID_STRING, 4);                                                             // 4B 可执行文件标识符
    char majorVersion = VERSION_MAJOR, minorVersion = VERSION_MINOR;
    writer.write(&majorVersion, 1);                                                             // 1B 主版本号
    writer.write(&minorVersion, 1);                                                             // 1B 次版本号

    writer.write((char *)&uiStackSize, 4);                                                      // 4B 堆栈大小
    writer.write((char *)&uiGlobalDataSize, 4);                                                 // 4B 全局数据大小

    char tmp = isMainFunctionPresent;
    writer.write(&tmp, 1);                                                                      // 1B 是否存在主函数
    writer.write((char *)&uiMainFuncIndex, 4);                                                  // 4B 主函数索引
    writer.write((char *)&iInstrStreamSize, 4);                                                 // 4B 指令流长度

    for (unsigned int i = 0; i < iInstrStreamSize; ++i) {
        Instr instruction = instructions->getInstr(i);
        writer.write((char *)&instruction.uiOpCode, 2);                                         // 2B 当前指令 Op
        writer.write((char *)&instruction.uiOpCount, 1);                                        // 1B 当前指令操作数数量

        for (unsigned int j = 0; j < instruction.uiOpCount; ++j) {
            Op operation = instruction.OpList[j];
            writer.write((char *)&operation.iType, 1);                                          // 1B 操作数类型
            switch (operation.iType) {
                case OP_TYPE_INT:
                    writer.write((char *)&operation.iIntLiteral, sizeof(int));                  // 2/4B int
                    break;
                case OP_TYPE_FLOAT:
                    writer.write((char *)&operation.fFloatLiteral, sizeof(float));              // 4B float
                    break;
                case OP_TYPE_STRING_INDEX:
                    writer.write((char *)&operation.uiStringTableIndex, sizeof(unsigned int));  // 2/4B unsigned int
                    break;
                case OP_TYPE_INSTR_INDEX:
                    writer.write((char *)&operation.uiInstrIndex, sizeof(unsigned int));        // 2/4B unsigned int
                    break;
                case OP_TYPE_ABS_STACK_INDEX:
                    writer.write((char *)&operation.iStackIndex, sizeof(int));                  // 2/4B int
                    break;
                case OP_TYPE_REL_STACK_INDEX:
                    writer.write((char *)&operation.iStackIndex, sizeof(int));                  // 2/4B int
                    writer.write((char *)&operation.iOffsetIndex, sizeof(int));                 // 2/4B int
                    break;
                case OP_TYPE_FUNC_INDEX:
                    writer.write((char *)&operation.iFuncIndex, sizeof(int));                   // 2/4B int
                    break;
                case OP_TYPE_HOST_API_CALL_INDEX:
                    writer.write((char *)&operation.uiHostAPICallIndex, sizeof(unsigned int));  // 2/4B unsigned int
                    break;
                case OP_TYPE_REG:
                    writer.write((char *)&operation.uiReg, sizeof(unsigned int));               // 2/4B unsigned int
                    break;
                default:
                    break;
            }
        }
    }

    // 写字符串表
    unsigned long stringCount = strings->getSize();
    writer.write((char *)&stringCount, sizeof(long));                                           // 4/8B 字符串表长度
    for (unsigned int i = 0; i < stringCount; ++i) {
        std::string currentStr = strings->getString(i);
        unsigned long strLength = currentStr.length();
        writer.write((char *)&strLength, sizeof(long));                                         // 4/8B long
        writer.write(currentStr.c_str(), currentStr.length());                                  // 4/8B long
    }

    // 写函数表
    auto functionSize = (unsigned int)functions->getSize();
    writer.write((char *)&functionSize, sizeof(unsigned int));                                  // 2/4B 函数表长度

    std::vector<std::string> functionNames = functions->getNameList();
    for (const auto& name: functionNames) {
        FuncNode function = functions->getFunction(name);
        int entryPoint = function.getEntryPoint();
        writer.write((char *)&entryPoint, sizeof(int));                                         // 2/4B 函数入口点
        unsigned int paramCount = function.getParamCount();
        writer.write((char *)&paramCount, sizeof(unsigned int));                                // 2/4B 函数参数数量
        unsigned int localDataSize = function.getLocalDataSize();
        writer.write((char *)&localDataSize, sizeof(unsigned int));                             // 2/4B 函数局部数据大小
    }

    // 写系统调用表
    auto apiSize = (unsigned int)hostapis->getSize();
    writer.write((char *)&apiSize, sizeof(unsigned int));                                       // 2/4B 系统调用表长度

    for (unsigned int i = 0; i < apiSize; i++) {
        std::string apiName = hostapis->getString(i);
        auto apiLength = (unsigned int)apiName.length();
        writer.write((char *)&apiLength, sizeof(unsigned int));                                 // 2/4B 系统调用名称长度
        writer.write(apiName.c_str(), apiLength);                                               // 系统调用名，长度不定
    }

    writer.close();
}