//
// Created by 王耀 on 2017/11/11.
//

#include <iostream>
#include <gflags/gflags.h>
#include "macro.h"

DEFINE_int32(n, 1, "虚拟机使用核心数");
DEFINE_bool(u, false, "反汇编并打印汇编指令");
DEFINE_bool(m, false, "显示 FEC 文件元信息");
DEFINE_bool(d, false, "单步执行并打印汇编指令");

void logo() {
    std::cout << "Fold-Script 虚拟机内核    当前版本: " << VERSION_MAJOR
              << "." << VERSION_MINOR << std::endl
              << "GitHub: https://github.com/forec/FoldScript" << std::endl;
}

void usage() {
    std::cout << "帮助:\t FVM [-i] bin.FEC [Option]" << std::endl
              << "\t [-n NUMBER] : FVM 虚拟机使用 CPU 核心数" << std::endl
              << "\t        [-u] : 反汇编并打印汇编指令" << std::endl
              << "\t        [-m] : 显示 FEC 文件元信息" << std::endl
              << "\t        [-d] : 单步执行并打印汇编指令" << std::endl;
}

int main(int argc, char * argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    logo();



    return 0;
}