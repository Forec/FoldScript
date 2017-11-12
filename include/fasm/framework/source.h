//
// Created by 王耀 on 2017/10/10.
//

#ifndef FOLDSCRIPT_ASM_SOURCE_H
#define FOLDSCRIPT_ASM_SOURCE_H

#include <vector>
#include <string>

/*
 * SourceCode: 源码集合，并对源码做一定文本处理（去除注释、多余空白字符等）
 * @source: 以行为索引，对应源码每一行的容器
 * @initialized: 是否已通过某份源码初始化
 * @uiSkipLine: 因为文本处理而遗弃的代码行数
 *
 * @initFromFile/String(): 从文件/字符串中导入源码
 * @stripComments(): 去除源码中的注释，此操作为原地操作
 * @trimWhiteSpace(): 去除源码中多余的空白字符，此操作为原地操作
 */

class SourceCode {
private:
    std::vector<std::string> source;
    bool initialized;
    bool isInitFromFile;
    unsigned long uiSkipLine;
    std::string filename;
public:
    SourceCode();
    ~SourceCode();
    bool isInitialized();
    bool initFromFile(const std::string &path);
    void initFromString(const std::string &str);
    std::string getFilename();
    unsigned long getSize();
    unsigned long getSkipLine();
    void setLine(unsigned long index, const std::string & line);
    std::string readLine(unsigned long index);
    std::string readCompressedLine(unsigned long index);
    void stripComments();
    void trimWhitespace();
};

#endif //FOLDSCRIPT_ASM_SOURCE_H
