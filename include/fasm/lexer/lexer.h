//
// Created by 王耀 on 2017/10/10.
//

#ifndef FOLDSCRIPT_LEXER_H
#define FOLDSCRIPT_LEXER_H

#include <string>
#include "../framework/instruction/inslktable.h"

typedef unsigned char Token;
typedef unsigned char LexState;

class Lexer {
private:
    unsigned int uiCurrentSourceLine;
    unsigned int uiIndex0;
    unsigned int uiIndex1;
    std::string currentLexeme;
    Token currentToken;
    LexState currentLexState;
    InstrLookupTable * lookupTable;
public:
    Lexer();
    Token getCurrentToken();
    Token getNextToken();
    LexState getCurrentState();
    std::string getCurrentLexeme();
    void reset();
    bool skipLine();
};

#endif //FOLDSCRIPT_LEXER_H
