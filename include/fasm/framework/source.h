//
// Created by 王耀 on 2017/10/10.
//

#ifndef FOLDSCRIPT_SOURCE_H
#define FOLDSCRIPT_SOURCE_H

#include <vector>
#include <string>

class SourceCode {
private:
    std::vector<std::string> source;
    bool initialized;
    bool isInitFromFile;
    std::string filename;
public:
    SourceCode();
    ~SourceCode();
    bool isInitialized();
    bool initFromFile(const std::string &path);
    void initFromString(const std::string &str);
    std::string getFilename();
    unsigned long getSize();
    void setLine(unsigned long index, const std::string & line);
    std::string readLine(unsigned long index);
    std::string readCompressedLine(unsigned long index);
    void stripComments();
    void trimWhitespace();
};

#endif //FOLDSCRIPT_SOURCE_H
