//
// Created by 王耀 on 2017/10/10.
//

#include <iostream>
#include "macro.h"
#include "lexer.h"
#include "source.h"

Lexer::Lexer() {
    reset();
    if (!SourceCode::isInitialized()) {
        std::cerr << "源码未载入" << std::endl;
        exit(1);
    }
}

void Lexer::reset() {
    uiCurrentSourceLine = 0;
    uiIndex0 = uiIndex1 = 0;
    currentToken = TOKEN_TYPE_INVALID;
    currentLexState = LEX_STATE_NO_STRING;
}

bool Lexer::skipLine() {
    ++uiCurrentSourceLine;
    if (uiCurrentSourceLine > SourceCode::getInstance()->getSize())
        return false;
    uiIndex0 = uiIndex1 = 0;
    currentLexState = LEX_STATE_NO_STRING;   // 字符串不可跨越多行
    return true;
}