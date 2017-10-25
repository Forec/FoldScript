//
// Created by 王耀 on 2017/10/14.
//

#include <cstdlib>
#include <iostream>
#include "macro.h"
#include "utils.h"
#include "instrlookup.h"
#include "parser.h"

Parser::Parser() {
    lexer = new Lexer();
    functions = new FuncTable();
    symbols = new SymbolTable();
    labels = new LabelTable();
    instructions = new InstrTable();
    reset();
}

Parser::~Parser() {
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
    iCurrentFuncIndex = -1;
    iMainFuncIndex = -1;
    isMainFunctionPresent = false;
    isSetStackSizeFound = false;
    isFuncActive = false;
    currentFunction = FuncNode(0, 0);

    lexer->reset();
    functions->reset();
    symbols->reset();
    labels->reset();
    instructions->reset();
}

void Parser::codeError(const std::string &err) {
    std::string LineInfo = "第 " + std::to_string(lexer->getCurrentSourceLine()) + " 行: ";
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
                iCurrentFuncIndex = functions->addFunction(lexer->getCurrentLexeme(), iInstrStreamSize);
                if (-1 == iCurrentFuncIndex)                            // 不可重复定义同名函数
                    codeError(ERROR_MSSG_FUNC_REDEFINITION);
                currentFuncName = lexer->getCurrentLexeme();
                if (currentFuncName == GRAMMAR_MAIN_FUNC_NAME) {        // 定义主函数
                    isMainFunctionPresent = true;
                    iMainFuncIndex = iCurrentFuncIndex;
                }
                isFuncActive = true;
                while (lexer->getNextToken() == TOKEN_TYPE_NEWLINE);    // 过滤掉函数标识符之后紧随的一系列空字符
                if (lexer->getCurrentToken() != TOKEN_TYPE_OPEN_BRACE)  // 函数标识符后必须跟随左花括号
                    charExpectError('{');
                ++iInstrStreamSize;                                     // 函数末尾自动附加 RET，因此增加指令流大小
                break;
            }
            case TOKEN_TYPE_CLOSE_BRACE:{
                    if (!isFuncActive)                                  // 出现花括号表明当前应处于函数内部
                        charExpectError('}');
                functions->setFunction(currentFuncName, uiCurrentFuncParamCount, uiCurrentFuncLocalDataSize);
                isFuncActive = false;
                break;
            }
            case TOKEN_TYPE_VAR: {
                if (lexer->getNextToken() != TOKEN_TYPE_IDENT)          // VAR 后应当跟随标识符定义变量
                    codeError(ERROR_MSSG_IDENT_EXPECTED);
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
                if (-1 == symbols->addSymbol(lexer->getCurrentLexeme(), uiSize, iStackIndex, (unsigned int) iCurrentFuncIndex))
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
                if (-1 == labels->addLabel(lexer->getCurrentLexeme(), iTargetIndex, (unsigned int)iCurrentFuncIndex))
                    codeError(ERROR_MSSG_LINE_LABEL_REDEFINITION);
                break;
            }
            case TOKEN_TYPE_INSTR: {
                if (isFuncActive)
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
                iCurrentFuncIndex = currentFunction.getIndex();         // 保存当前函数索引
                isFuncActive = true;
                uiCurrentFuncParamCount = 0;                            // 重置当前函数参数数量
                while (lexer->getNextToken() == TOKEN_TYPE_NEWLINE);
                break;
            }
            case TOKEN_TYPE_CLOSE_BRACE: {                              // 遇到右花括号时表示函数结束，增加额外的 RET 或 EXIT 指令
                Instr endInstr(INSTR_EXIT, 1);
                isFuncActive = false;
                if (currentFuncName == GRAMMAR_MAIN_FUNC_NAME) {        // 当前函数为 Main，退出时增加 exit 指令
                    endInstr.OpList.emplace_back(Op{OP_TYPE_INT, 0, 0});
                } else {
                    endInstr.uiOpCode = INSTR_RET;
                    endInstr.uiOpCount = 0;
                }
                instructions->setInstr(uiCurrentInstrIndex++, endInstr);// 将 RET 或 EXIT 指令加入函数末尾
                break;
            }
            case TOKEN_TYPE_PARAM: {                                    // 第二次遍历遇到参数时需要将其加入参数表
                if (lexer->getNextToken() != TOKEN_TYPE_IDENT)
                    codeError(ERROR_MSSG_IDENT_EXPECTED);
                int iStackIndex = - (currentFunction.getLocalDataSize() + 2 + uiCurrentFuncParamCount + 1);
                if (-1 == symbols->addSymbol(lexer->getCurrentLexeme(), 1, iStackIndex, (unsigned int)iCurrentFuncIndex))
                    codeError(ERROR_MSSG_IDENT_REDEFINITION);
                ++uiCurrentFuncParamCount;
                break;
            }
            case TOKEN_TYPE_INSTR: {
                InstrLookup instr = lexer->getLookupTable()->getInstrLookup(lexer->getCurrentLexeme());
                instructions->setOpCode((unsigned long)iCurrentFuncIndex, instr.getOpCode());
                instructions->setOpCount((unsigned long)iCurrentFuncIndex, instr.getOpCount());
                //TODO
            }
        }

    }
}