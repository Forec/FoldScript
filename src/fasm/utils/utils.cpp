//
// Created by 王耀 on 2017/10/7.
//

#include <cctype>
#include <algorithm>
#include <iostream>
#include "utils.h"

bool isStringInt(const std::string &string) {
    // TODO: 对十六进制、八进制、二进制的支持。返回值可以为识别出的进制。
    if (string.empty())
        return false;
    if (!isCharNumeric(string[0]) && string[0] != '-')
        return false;
    return std::all_of(string.begin() + 1, string.end(), isCharNumeric);
}

bool isStringFloat(const std::string &string) {
    if (string.empty())
        return false;
    if (!isCharNumeric(string[0]) && string[0] != '-' && string[0] != '.')
        return false;
    if (std::count(string.begin(), string.end(), '.') != 1)
        return false;
    return std::all_of(string.begin() + 1, string.end(), [](const char c) {
        return isCharNumeric(c) || c == '.'; });
}

bool isStringSpace(const std::string &string) {
    return !string.empty() && std::all_of(string.begin(), string.end(), isCharWhitespace);
}

bool isStringIdent(const std::string &string) {
    if (string.empty() || isCharNumeric(string[0]))
        return false;
    return std::all_of(string.begin(), string.end(), isCharIdent);
}

void shutdown() {
}

void exitOnError(const std::string &err) {
    std::cerr << "致命错误: " << err << "." << std::endl;
    shutdown();
    exit(1);
}
