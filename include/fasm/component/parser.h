//
// Created by 王耀 on 2017/10/14.
//

#ifndef FOLDSCRIPT_ASM_PARSER_H
#define FOLDSCRIPT_ASM_PARSER_H

#include <string>
#include "function/functable.h"
#include "symbol/symtable.h"
#include "label/labtable.h"
#include "instruction/instable.h"
#include "strtable.h"
#include "lexer.h"

/*
 * Parser: 语法分析器
 * @uiStackSize: 脚本定义的堆栈大小
 * @uiGlobalDataSize: 脚本定义的全局数据大小
 * @iInstrStreamSize: 脚本指令流大小（包含了隐式添加的 ret 指令和 exit 指令）
 * @uiCurrentInstrIndex: 当前分析的指令行索引
 * @uiCurrentFuncParamCount: 当前分析所在函数的参数数量
 * @uiCurrentFuncLocalDataSize: 当前分析所在函数的局部数据大小
 * @uiCurrentFuncIndex: 当前分析所在函数对应函数表中的索引
 * @uiMainFuncIndex: 主函数索引
 * @isFuncActive: 当前分析位置是否在函数中
 *
 * @functions: 函数表
 * @symbols: 符号表（包括 Param 和 Var 定义的符号）
 * @labels: 行标签表
 * @instructions: 指令流
 * @strings: 字符串表
 * @hostapis: 系统调用表
 * @execFilename: 导出 FEC 文件名
 * @lexer: 词法分析器
 *
 * @initFromFile/String(): 从文件/字符串中导入脚本
 * @assemble(): 汇编脚本
 * @exportFEC(): 将汇编后的内容导出到 FEC 文件
 * @statusToString(): 将汇编报告以字符串方式返回
 */

class Parser {
private:
    unsigned long uiStackSize;
    unsigned long uiGlobalDataSize;
    int iInstrStreamSize;
    unsigned int uiCurrentInstrIndex;
    unsigned int uiCurrentFuncParamCount;
    unsigned int uiCurrentFuncLocalDataSize;
    unsigned int uiCurrentFuncIndex;
    unsigned int uiMainFuncIndex;

    bool isMainFunctionPresent;
    bool isSetStackSizeFound;

    bool isFuncActive;
    std::string currentFuncName;
    FuncNode currentFunction;
    FuncTable * functions;
    SymbolTable * symbols;
    LabelTable * labels;
    InstrTable * instructions;
    StringTable * strings;
    StringTable * hostapis;

    std::string execFilename;

    Lexer * lexer;
public:
    Parser();
    ~Parser();
    bool initFromFile(const std::string &path);
    void initFromString(const std::string &str);
    void setExecFilename(const std::string &name);
    void reset();
    void assemble();
    void exportFEC();
    std::string statusToString();

    // 错误处理
    void codeError(const std::string &err);
    void charExpectError(char code);
};

#endif //FOLDSCRIPT_ASM_PARSER_H
