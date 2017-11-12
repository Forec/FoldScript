//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_ASM_UTILS_H
#define FOLDSCRIPT_ASM_UTILS_H

#include <string>
#include <utility>
#include <functional>

/*
 * utils: FASM 中通用的帮助函数
 *
 * @hash_func: 对于 <string, uint> 组合的哈希函数
 * @cmp_func: 对于 <string, uint> 组合的比较函数，与 hash_func 一起作为 map 等 STL 容器的参数
 *
 * @isCharNumeric: 字符是否为阿拉伯数字
 * @isCharIdent: 字符是否为构建标识符的合法字符（数字、字母、下划线）
 * @isCharDelimiter: 字符是否为划分标识符、保留字等的特殊字符（冒号，逗号，引号，括号等）
 * @isStringInt: 字符串是否可被加载为整型
 * @isStringFloat: 字符串是否可被加载为浮点型
 * @isStringSpace: 字符串是否全为空白符
 * @isStringIdent: 字符串是否是合法的标识符
 *
 * @shutdown(): 主函数结束时的清理函数，可向其添加全局操作，或输出信息
 * @exitOnError(): 立即以异常方式结束 FASM，并返回错误信息
 */

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
