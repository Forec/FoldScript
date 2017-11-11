//
// Created by 王耀 on 2017/10/10.
//

#ifndef FOLDSCRIPT_ASM_LEXER_H
#define FOLDSCRIPT_ASM_LEXER_H

#include <string>
#include "../framework/instruction/inslktable.h"
#include "source.h"

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
    SourceCode * source;
public:
    Lexer();
    ~Lexer();
    bool initFromFile(const std::string &path);
    void initFromString(const std::string &str);
    Token getCurrentToken();
    Token getNextToken();
    char getLookAheadChar();
    LexState getCurrentState();
    std::string getCurrentLexeme();
    unsigned int getCurrentSourceLine();
    unsigned int getFirstIndex();
    void reset();
    bool skipLine();
    SourceCode * getSource();
    InstrLookupTable * getLookupTable();
    InstrLookup getCurrentInstr();
};

#endif //FOLDSCRIPT_ASM_LEXER_H
