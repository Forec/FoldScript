//
// Created by 王耀 on 2017/10/10.
//

#ifndef FOLDSCRIPT_LEXER_H
#define FOLDSCRIPT_LEXER_H

typedef unsigned char Token;
typedef unsigned char LexState;

class Lexer {
private:
    unsigned int uiCurrentSourceLine;
    unsigned int uiIndex0;
    unsigned int uiIndex1;
    Token currentToken;
    LexState currentLexState;
public:
    Lexer();
    Token getNextToken();
    void reset();
    bool skipLine();
};

#endif //FOLDSCRIPT_LEXER_H
