//
// Created by 王耀 on 2017/11/11.
//

#include <iostream>
#include <gflags/gflags.h>
#include "macro.h"
#include "script.h"

DEFINE_string(i, "", "可执行 FEC 文件");
DEFINE_int32(n, 1, "虚拟机使用核心数");
DEFINE_bool(u, false, "反汇编并打印汇编指令");
DEFINE_bool(m, false, "显示 FEC 文件元信息");
DEFINE_bool(d, false, "单步执行并打印汇编指令");
DEFINE_bool(e, false, "输出信息同时执行脚本");
DEFINE_bool(h, false, "查看帮助信息");

void logo() {
    std::cout << "Fold-Script 虚拟机内核    当前版本: " << VERSION_MAJOR
              << "." << VERSION_MINOR << std::endl
              << "GitHub: https://github.com/forec/FoldScript" << std::endl;
}

std::string usageMsg = std::string("") +
        "帮助: fvm [-i] bin.FEC [Option]\n" +
        "[Option]: \n" +
        "  [-n N]  FVM 虚拟机使用 CPU 核心数\n" +
        "    [-u]  反汇编并打印汇编指令\n" +
        "    [-m]  显示 FEC 文件元信息\n" +
        "    [-d]  单步执行并打印汇编指令\n" +
        "    [-h]  帮助信息\n" +
        "    [-e]  在打印上述信息时仍执行脚本";

int main(int argc, char * argv[]) {
    gflags::SetUsageMessage(usageMsg);
    gflags::SetVersionString(std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR));
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    logo();

    std::string executableFile = FLAGS_i;
    if (argc > 1 && FLAGS_i.empty()) {
        executableFile = argv[1];
    } else {
        std::cout << usageMsg << std::endl;
        return 0;
    }

    Script * script = new Script();
    script->setExecutableFile(executableFile);
    if (!script->isValid()) {
        std::cerr << "失败: 可执行文件不存在或与当前 FVM 版本不兼容，请检查文件 \"" << executableFile
                  << "\" 是否存在或损坏，并确保当前用户对该文件有读/执行权限。" << std::endl;
        return 0;
    }
    if (!script->loadCode()) {
        std::cerr << "失败: 文件 \"" << executableFile
                  << "\" 已损坏或不是标准的 FEC 可执行文件格式。" << std::endl;
        return 0;
    }

    if (FLAGS_u) {
        // TODO: 反汇编并打印
    }

    if (FLAGS_d) {
        script->setDebugMode();
    }

    if (FLAGS_m) {
        std::cout << script->status2string();
    }

    if (FLAGS_h)
        std::cout << usageMsg << std::endl;

    if (FLAGS_e || !(FLAGS_u || FLAGS_m || FLAGS_h))
        script->run();

    delete script;

    return 0;
}