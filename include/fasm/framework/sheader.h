//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_SHEADER_H
#define FOLDSCRIPT_SHEADER_H

/*
 * ScriptHeader: 脚本头部元数据
 * @iStackSize: 为程序分配的堆栈大小
 * @iGlobalDataSize: 静态数据区域大小
 * @iIsMainFuncPresent: 主函数是否存在
 * @iMainFuncIndex: 主函数在函数表中的索引
 */

struct ScriptHeader {
    unsigned int iStackSize;
    unsigned int iGlobalDataSize;
    bool iIsMainFuncPresent;
    unsigned int iMainFuncIndex;
};

#endif //FOLDSCRIPT_SHEADER_H
