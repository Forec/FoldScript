//
// Created by 王耀 on 2017/11/12.
//

#ifndef FOLDSCRIPT_VM_SCRIPT_H
#define FOLDSCRIPT_VM_SCRIPT_H

#include "value.h"
#include "rstack.h"
#include "functable.h"
#include "hostapi.h"
#include "instruction/instable.h"

/*
 * Script: 脚本对象
 * @isMainFuncPresent: 脚本中主函数是否存在
 * @isPaused: 脚本当前是否处于暂停状态
 * @uiMainFuncIndex: 主函数索引
 * @uiGlobalDataSize: 脚本全局数据大小
 * @uiPauseEndStamp: 脚本继续运行时刻
 * @_RetVal: 返回值寄存器
 * @stack: 运行时堆栈
 * @instructions: 脚本指令流
 * @functions: 脚本函数表
 * @apis: 系统调用表
 *
 * @reset(): 脚本重置为空
 * @load(): 从指定文件加载脚本
 */

typedef unsigned char Status;

class Script {
private:
    bool isMainFuncPresent;
    bool isPaused;
    unsigned int uiMainFuncIndex;
    unsigned int uiGlobalDataSize;
    unsigned long ulPauseEndStamp;

    Value _RetVal;
    RuntimeStack * stack;
    InstrTable * instructions;
    FuncTable * functions;
    HostAPICallTable * apis;

public:
    Script();
    ~Script();
    void reset();
    Status load(const std::string &path);
};

#endif //FOLDSCRIPT_VM_SCRIPT_H
