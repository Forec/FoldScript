//
// Created by 王耀 on 2017/10/10.
//

#include "macro.h"
#include "utils.h"
#include "source.h"
#include <iostream>

SourceCode * SourceCode::instance = nullptr;
bool SourceCode::initialized = false;

SourceCode * SourceCode::getInstance() {
    if (!instance)
        instance = new SourceCode();
    return instance;
}

void SourceCode::destroy() {
    delete instance;
    initialized = false;
}

SourceCode::SourceCode() {
    source.clear();
}

bool SourceCode::initFromFile(const std::string &path) {
    getInstance()->source.clear();
    // TODO: 读入代码
    initialized = true;
    return true;
}

void SourceCode::initFromString(const std::string &str) {
    getInstance()->source.clear();
    if (str.empty()) {
        initialized = true;
        return;
    }
    size_t last = 0;
    size_t index = str.find_first_of(CODE_LINE_DELIMITER, last);
    while (index != std::string::npos) {
        getInstance()->source.emplace_back(str.substr(last, index - last));
        last = index + 1;
        index = str.find_first_of(CODE_LINE_DELIMITER, last);
    }
    if (index > last)
        getInstance()->source.emplace_back(str.substr(last, index - last));
    initialized = true;
}

unsigned long SourceCode::getSize() {
    return source.size();
}

bool SourceCode::isInitialized() {
    return initialized;
}

void SourceCode::setLine(unsigned long index, const std::string &line) {
    if (index >= source.size()) {
        source.emplace_back(line);
    } else {
        source[index] = line;
    }
}

std::string SourceCode::readLine(unsigned long index) {
    if (index >= source.size())
        return "";
    return source[index];
}

void SourceCode::stripComments() {
    for (auto&& it : source) {
        bool inString = false;
        for (unsigned int i = 0; i < it.length(); i++) {
            char code = it.at(i);
            if (code == CODE_STRING_DELIMITER)
                inString ^= true;
            if (code == CODE_COMMENT_DELIMITER && !inString)
                it = it.substr(0, i);
        }
    }
}

void SourceCode::trimWhitespace() {
    std::vector<std::string> filterList;
    for (auto&& it : source) {
        unsigned long leftTrimIndex = 0;
        while (leftTrimIndex < it.length() && isCharWhitespace(it.at(leftTrimIndex++)));
        it = it.substr(leftTrimIndex == 0 ? 0 : leftTrimIndex - 1);
        if (it.empty())
            continue;
        unsigned long rightTrimIndex = it.length() - 1;
        while (rightTrimIndex > 0 && isCharWhitespace(it.at(rightTrimIndex--)));
        if (rightTrimIndex == 0 && isCharWhitespace(it.at(0)))
            it.clear();
        else
            it = it.substr(0, rightTrimIndex + 2);
        if (!it.empty())
            filterList.emplace_back(it);
    }
    source.clear();
    source = filterList;
}