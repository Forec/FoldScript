//
// Created by 王耀 on 2017/11/11.
//

#ifndef FOLDSCRIPT_VM_VM_H
#define FOLDSCRIPT_VM_VM_H

#include <string>

/*
 * VM: FoldScript 虚拟机
 * @loadExecutable(): 从可执行文件导入
 */

class VM {
private:
public:
    VM();
    ~VM();
    void loadExecutable(const std::string &path);
    void run();
};

#endif //FOLDSCRIPT_VM_VM_H
