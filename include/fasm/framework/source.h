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
    static SourceCode * instance;
    static bool initialized;
    static bool isInitFromFile;
    static std::string filename;
    SourceCode();
public:
    static SourceCode * getInstance();
    static void destroy();
    static bool isInitialized();
    static bool initFromFile(const std::string &path);
    static void initFromString(const std::string &str);
    static std::string getFilename();
    unsigned long getSize();
    void setLine(unsigned long index, const std::string & line);
    std::string readLine(unsigned long index);
    std::string readCompressedLine(unsigned long index);
    void stripComments();
    void trimWhitespace();
};

#endif //FOLDSCRIPT_SOURCE_H
