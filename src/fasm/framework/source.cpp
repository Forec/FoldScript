//
// Created by 王耀 on 2017/10/10.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include "macro.h"
#include "utils.h"
#include "source.h"

SourceCode::SourceCode() {
    initialized = false;
    isInitFromFile = false;
    uiSkipLine = 0;
    source.clear();
}

SourceCode::~SourceCode() {
    source.clear();
}

bool SourceCode::initFromFile(const std::string &path) {
    source.clear();
    std::ifstream fin;
    fin.open(path, std::ios_base::in);
    if (fin.fail())
        return false;
    std::string sourceCode;
    std::string line;
    while (std::getline(fin, line)) {
        sourceCode += line + "\n";
    }
    fin.close();
    initFromString(sourceCode);
    filename = path;
    initialized = true;
    isInitFromFile = true;
    return true;
}

void SourceCode::initFromString(const std::string &str) {
    source.clear();
    if (str.empty()) {
        initialized = true;
        isInitFromFile = false;
        return;
    }
    size_t last = 0;
    size_t index = str.find_first_of(CODE_LINE_DELIMITER, last);
    while (index != std::string::npos) {
        source.emplace_back(str.substr(last, index - last));
        last = index + 1;
        index = str.find_first_of(CODE_LINE_DELIMITER, last);
    }
    if (index > last)
        source.emplace_back(str.substr(last, index - last));
    initialized = true;
    isInitFromFile = false;
}

std::string SourceCode::getFilename() {
    if (isInitFromFile)
        return filename;
    return "字符串导入代码";
}

unsigned long SourceCode::getSize() {
    return source.size() + uiSkipLine;
}

unsigned long SourceCode::getSkipLine() {
    return uiSkipLine;
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

std::string SourceCode::readCompressedLine(unsigned long index) {
    std::string line = readLine(index);
    std::transform(line.begin(), line.end(), line.begin(), [](char c) { return c == '\t' ? ' ' : c; });
    return line;
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
        else
            uiSkipLine++;
    }
    source.clear();
    source = filterList;
}