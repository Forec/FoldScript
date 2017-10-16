//
// Created by 王耀 on 2017/10/14.
//

#ifndef FOLDSCRIPT_PARSER_H
#define FOLDSCRIPT_PARSER_H

#include <string>
#include "function/functable.h"
#include "symbol/symtable.h"
#include "label/labtable.h"
#include "lexer.h"

class Parser {
private:
    unsigned long uiStackSize;
    unsigned long uiGlobalDataSize;
    int iInstrStreamSize;
    int iMainFuncIndex;
    unsigned int uiCurrentFuncParamCount;
    unsigned int uiCurrentFuncLocalDataSize;
    int iCurrentFuncIndex;

    bool isMainFunctionPresent;
    bool isSetStackSizeFound;

    bool isFuncActive;
    std::string currentFuncName;
    FuncTable * functions;
    SymbolTable * symbols;
    LabelTable * labels;

    Lexer * lexer;
public:
    Parser();
    ~Parser();
    bool initFromFile(const std::string &path);
    void initFromString(const std::string &str);
    void reset();
    void assemble();

    // 错误处理
    void codeError(const std::string &err);
    void charExpectError(char code);
};

#endif //FOLDSCRIPT_PARSER_H
