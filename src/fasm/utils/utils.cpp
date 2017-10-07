//
// Created by 王耀 on 2017/10/7.
//

#include <cctype>
#include <algorithm>
#include "utils.h"

bool isStringInt(const std::string &string) {
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