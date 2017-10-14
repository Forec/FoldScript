//
// Created by 王耀 on 2017/10/14.
//

#ifndef FOLDSCRIPT_PARSER_H
#define FOLDSCRIPT_PARSER_H

#include <string>
#include "function/funcnode.h"
#include "lexer.h"

class Parser {
private:
    unsigned long uiStackSize;
    unsigned long uiGlobalDataSize;
    unsigned long uiInstrStreamSize;
    bool isMainFunctionPresent;
    bool isSetStackSizeFound;

    bool isFuncActive;
    std::string currentFuncName;
    FuncNode currentFunc;

    Lexer * lexer;
public:
    Parser();
    ~Parser();
    bool initFromFile(const std::string &path);
    void initFromString(const std::string &str);
    void reset();
    void assemble();
};

#endif //FOLDSCRIPT_PARSER_H
