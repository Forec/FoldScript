//
// Created by 王耀 on 2017/10/10.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include "macro.h"
#include "utils.h"
#include "lexer.h"

Lexer::Lexer() {
    source = new SourceCode();
    lookupTable = new InstrLookupTable();
    reset();
}

Lexer::~Lexer() {
    delete lookupTable;
    delete source;
}

bool Lexer::initFromFile(const std::string &path) {
    reset();
    if (!source->initFromFile(path))
        return false;
    if (!source->isInitialized()) {
        std::cerr << "源码 " << path << " 未载入" << std::endl;
        return false;
    }
    source->stripComments();
    source->trimWhitespace();
    return true;
}

void Lexer::initFromString(const std::string &str) {
    reset();
    source->initFromString(str);
    if (!source->isInitialized()) {
        std::cerr << "源码未载入" << std::endl;
    }
    source->stripComments();
    source->trimWhitespace();
}

std::string Lexer::getCurrentLexeme() {
    return currentLexeme;
}

LexState Lexer::getCurrentState() {
    return currentLexState;
}

Token Lexer::getCurrentToken() {
    return currentToken;
}

SourceCode* Lexer::getSource() {
    return source;
}

InstrLookupTable* Lexer::getLookupTable() {
    return lookupTable;
}

unsigned int Lexer::getFirstIndex() {
    return uiIndex0;
}

unsigned int Lexer::getCurrentSourceLine() {
    return uiCurrentSourceLine;
}

void Lexer::reset() {
    uiCurrentSourceLine = 0;
    uiIndex0 = uiIndex1 = 0;
    currentToken = TOKEN_TYPE_INVALID;
    currentLexState = LEX_STATE_NO_STRING;
    currentLexeme = "";
    lookupTable->init();
}

bool Lexer::skipLine() {
    ++uiCurrentSourceLine;
    if (uiCurrentSourceLine >= source->getSize())
        return false;
    uiIndex0 = uiIndex1 = 0;
    currentLexState = LEX_STATE_NO_STRING;   // 字符串不可跨越多行
    return true;
}

InstrLookup Lexer::getCurrentInstr() {
    return lookupTable->getInstrLookup(currentLexeme);
}

/*
 * getNextToken: 获取下一个属性字
 * @Requirement: 所有的代码行均已做过空字符的 trim 处理，且不存在空行
 */
Token Lexer::getNextToken() {
    uiIndex0 = uiIndex1;    // 将索引移至上一个属性字末尾

    if (uiIndex0 >= source->readLine(uiCurrentSourceLine).length() &&
        !skipLine())
        return END_OF_TOKEN_STREAM;   // 本行已扫描完，跳至下一行

    if (currentLexState == LEX_STATE_END_STRING)
        currentLexState = LEX_STATE_NO_STRING;   // 若上一个属性字为字符串，则结束对其分析

    std::string line = source->readLine(uiCurrentSourceLine);

    // 如果当前没有检测到字符串，则跳过下一个属性字前的空白符
    if (currentLexState != LEX_STATE_IN_STRING) {
        while (uiIndex0 < line.length() && isCharWhitespace(line[uiIndex0]))
            uiIndex0++;
    }

    // 确定当前属性字对应单词的结束位置
    uiIndex1 = uiIndex0;
    while (true) {
        // 当前正在检测字符串
        if (currentLexState == LEX_STATE_IN_STRING) {
            // 在字符串模式下如果遇到行尾，说明字符串没有结束，词法错误
            if (uiIndex1 >= line.length()) {
                currentToken = TOKEN_TYPE_INVALID;
                return currentToken;
            }
            // 遇到转义字符向前跳跃
            if (line[uiIndex1] == '\\') {
                uiIndex1 += 2;
                continue;
            }
            // 当前字符不是双引号，向前移动一个索引，否则结束对字符串的检测
            if (line[uiIndex1] == '"')
                break;
            ++uiIndex1;
        }
        // 当前没有检测字符串
        else {
            // 遇行尾或分隔符表明当前单词结束
            if (uiIndex1 >= line.length() || isCharDelimiter(line[uiIndex1]))
                break;
            ++uiIndex1;
        }
    }

    // 对于分隔符（如,";）等单字符单词，此时 uiIndex1 与 uiIndex0 相等
    if (uiIndex1 == uiIndex0)
        uiIndex1++;

    // 从当前代码行提取当前属性字的单词
    std::stringstream ss;
    for (unsigned int i = uiIndex0; i < uiIndex1; i++) {
        if (currentLexState == LEX_STATE_IN_STRING && line[i] == '\\')
            i++;
        ss << line[i];
    }
    currentLexeme = ss.str();

    // 非字符串的情况下将单词切换为大写
    if (currentLexState != LEX_STATE_IN_STRING)
        std::transform(currentLexeme.begin(), currentLexeme.end(), currentLexeme.begin(), ::toupper);

    // 属性字识别
    currentToken = TOKEN_TYPE_INVALID;
    // 当前正识别字符串，且第一个字符不是双引号，说明字符串扫描完
    if (currentLexState == LEX_STATE_IN_STRING && currentLexeme.length() > 1 && currentLexeme[0] != '"') {
        currentToken = TOKEN_TYPE_STRING;
        return TOKEN_TYPE_STRING;
    }
    // 检查单字符属性字
    if (currentLexeme.length() == 1) {
        switch (currentLexeme[0]) {
            case '"':
                switch (currentLexState) {
                    case LEX_STATE_IN_STRING:
                        currentLexState = LEX_STATE_END_STRING;
                        break;
                    default:   // 正常模式，或结束状态之后立刻又跟随一个双引号
                        currentLexState = LEX_STATE_IN_STRING;
                        break;
                }
                currentToken = TOKEN_TYPE_QUOTE;
                break;
            case ',':
                currentToken = TOKEN_TYPE_COMMA;
                break;
            case ':':
                currentToken = TOKEN_TYPE_COLON;
                break;
            case '[':
                currentToken = TOKEN_TYPE_OPEN_BRACKET;
                break;
            case ']':
                currentToken = TOKEN_TYPE_CLOSE_BRACKET;
                break;
            case '{':
                currentToken = TOKEN_TYPE_OPEN_BRACE;
                break;
            case '}':
                currentToken = TOKEN_TYPE_CLOSE_BRACE;
                break;
            case '\n':
                currentToken = TOKEN_TYPE_NEWLINE;
                break;
            default:
                break;
        }
    }

    // 检查多字符属性字
    if (isStringInt(currentLexeme))
        currentToken = TOKEN_TYPE_INT;
    else if (isStringFloat(currentLexeme))
        currentToken = TOKEN_TYPE_FLOAT;
    else if (isStringIdent(currentLexeme))
        currentToken = TOKEN_TYPE_IDENT;   // 或行标签、指令

    // 检查保留字或寄存器
    if (currentLexeme == GRAMMAR_SET_STACK_SIZE)
        currentToken = TOKEN_TYPE_SETSTACKSIZE;
    else if (currentLexeme == GRAMMAR_VAR)
        currentToken = TOKEN_TYPE_VAR;
    else if (currentLexeme == GRAMMAR_FUNC)
        currentToken = TOKEN_TYPE_FUNC;
    else if (currentLexeme == GRAMMAR_PARAM)
        currentToken = TOKEN_TYPE_PARAM;
    else if (currentLexeme == GRAMMAR_RESULT_REGISTER)
        currentToken = TOKEN_TYPE_REG_RETVAL;

    // 检查是否为指令
    InstrLookup ilk = lookupTable->getInstrLookup(currentLexeme);
    if (ilk.getOpCode() != 0 || currentLexeme == INSTR_NOP_STR)
        currentToken = TOKEN_TYPE_INSTR;

    return currentToken;
}

char Lexer::getLookAheadChar() {
    unsigned int line = uiCurrentSourceLine, index = uiIndex1;
    if (currentLexState != LEX_STATE_IN_STRING) {
        while (true) {
            if (index >= source->readLine(line).length()) {
                if (++line >= source->getSize())
                    return 0;
                index = 0;
            }
            if (!isCharWhitespace(source->readLine(line).at(index)))
                break;
            ++index;
        }
    }
    if (source->readLine(line).length() > index)
        return source->readLine(line).at(index);
    return '\0';
}