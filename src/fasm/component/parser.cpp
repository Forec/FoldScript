//
// Created by 王耀 on 2017/10/14.
//

#include "parser.h"

Parser::Parser() {
    lexer = nullptr;
    reset();
}

Parser::~Parser() {
    delete lexer;
}

void Parser::reset() {
    uiStackSize = 0;
    uiInstrStreamSize = 0;
    uiGlobalDataSize = 0;
    isMainFunctionPresent = false;
    isSetStackSizeFound = false;
    isFuncActive = false;

    if (!lexer)
        lexer = new Lexer();
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
    
}