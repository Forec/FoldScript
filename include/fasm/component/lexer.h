//
// Created by 王耀 on 2017/10/10.
//

#ifndef FOLDSCRIPT_ASM_LEXER_H
#define FOLDSCRIPT_ASM_LEXER_H

#include <string>
#include "../framework/instruction/inslktable.h"
#include "source.h"

/*
 * Lexer: 词法分析器
 * @uiCurrentSourceLine: 当前读取的指令行数
 * @uiIndex0: 双指针中的后向指针，保留前一次检索到的最终位置
 * @uiIndex1: 双指针中的前向指针，向前扫描下一个词法单元
 * @currentLexeme: 当前词法单元
 * @currentToken: 当前词法单元类型
 * @currentLexState: 当前词法分析器所处的状态，如字符串中，字符串结束处等
 * @lookupTable: 指令查找表，用于确定当前词法单元是否为保留指令
 * @source: 指令流
 *
 * @initFromFile/String(): 从文件/字符串中导入 FASM 脚本
 * @getNextToken(): 前向搜索下一个词法单元并返回该词法单元的类型
 * @skipLine(): 跳过当前行
 * @getCurrentInstr(): 根据当前词法单元获取对应的指令
 */

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
