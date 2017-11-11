//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_ASM_UTILS_H
#define FOLDSCRIPT_ASM_UTILS_H

#include <string>
#include <utility>
#include <functional>

typedef std::pair<std::string, unsigned int> kpair;

struct hash_func {
    size_t operator()(const kpair &pair) const {
        std::hash<std::string> h;
        size_t string_hash = h(pair.first);
        return string_hash + pair.second;
    }
};

struct cmp_func {
    bool operator()(const kpair &k1, const kpair &k2) const {
        return k1.first == k2.first && k1.second == k2.second;
    }
};

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

/*
 * 错误处理函数
 */
void shutdown();
void exitOnError(const std::string & err);

#endif //FOLDSCRIPT_ASM_UTILS_H
