//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_UTILS_H
#define FOLDSCRIPT_UTILS_H

#include <string>

inline bool isCharNumeric(char character) {
    return isdigit(character);
}

inline bool isCharWhitespace(char character) {
    return isspace(character);
}

inline bool isCharIdent(char character) {
    return isalnum(character) || character == '_';
}

inline bool isCharDelimiter(char character) {
    return character == ':' || character == ',' || character == '"' ||
           character == '[' || character == ']' ||
           character == '{' || character == '}' ||
           isCharWhitespace(character);
}

bool isStringInt(const std::string &string);
bool isStringFloat(const std::string &string);
bool isStringSpace(const std::string &string);
bool isStringIdent(const std::string &string);

#endif //FOLDSCRIPT_UTILS_H
