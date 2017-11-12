//
// Created by 王耀 on 2017/11/12.
//

#include <fstream>
#include "macro.h"
#include "script.h"

Script::Script() {
    instructions = new InstrTable();
    stack = new RuntimeStack();
    functions = new FuncTable();
    apis = new HostAPICallTable();
    reset();
}

Script::~Script() {
    delete apis;
    delete functions;
    delete stack;
    delete instructions;
}

void Script::reset() {
    uiGlobalDataSize = 0;
    ulPauseEndStamp = 0;
    uiMainFuncIndex = 0;

    isMainFuncPresent = false;
    isPaused = false;

    instructions->reset();
    stack->reset();
    functions->reset();
    apis->reset();
}

Status Script::load(const std::string &path) {
    std::ifstream reader;
    reader.open(path, std::ios_base::binary | std::ios_base::in);
    if (reader.fail()) {                                                 // 文件不存在或无读权限
        return LOAD_ERROR_FILE_IO;
    }
    char buffer[8];
    memset(buffer, 0, sizeof(buffer));
    reader.read(buffer, 4);                                              // 4B FEC文件标识符
    if (std::string(buffer) != FEC_ID_STRING)                            // 可执行文件格式不正确
        return LOAD_ERROR_INVALID_FEC;

    char majorVersion = 0, minorVersion = 0;
    reader.read(&majorVersion, 1);                                       // 1B 主版本号
    reader.read(&minorVersion, 1);                                       // 1B 次版本号

    if (majorVersion != VERSION_MAJOR || minorVersion != VERSION_MINOR)  // 版本不兼容
        return LOAD_ERROR_UNSUPPORTED_VERS;

    unsigned int uiStackSize = 0;
    reader.read((char *)&uiStackSize, 4);                                // 4B 堆栈空间大小
    stack->setSize(uiStackSize == 0 ? DEF_STACK_SIZE : uiStackSize);

    reader.read((char *)&uiGlobalDataSize, 4);                           // 4B 全局数据大小

    char tmp = 0;
    reader.read(&tmp, 1);                                                // 1B 主函数存在标示
    isMainFuncPresent = tmp == 1;
    reader.read((char *)&uiMainFuncIndex, 4);                            // 4B 主函数索引

    unsigned int uiStreamSize = 0;
    reader.read((char *)&uiStreamSize, 4);                               // 4B 指令流长度
    instructions->resize(uiStreamSize);

    //TODO: 读取指令
}