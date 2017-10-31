//
// Created by 王耀 on 2017/10/14.
//

#ifndef FOLDSCRIPT_PARSER_H
#define FOLDSCRIPT_PARSER_H

#include <string>
#include "function/functable.h"
#include "symbol/symtable.h"
#include "label/labtable.h"
#include "instruction/instable.h"
#include "strtable.h"
#include "lexer.h"

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
    std::string statusToString();

    // 错误处理
    void codeError(const std::string &err);
    void charExpectError(char code);
};

#endif //FOLDSCRIPT_PARSER_H
