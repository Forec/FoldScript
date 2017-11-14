#include <algorithm>
#include <string>
#include <iostream>
#include <gflags/gflags.h>
#include "macro.h"
#include "parser.h"

DEFINE_string(i, "", "待汇编源文件");
DEFINE_string(o, "a.fec", "汇编结果输出路径");

void logo() {
    std::cout << "Fold-Script 汇编器    当前版本: " << VERSION_MAJOR
              << "." << VERSION_MINOR << std::endl
              << "GitHub: https://github.com/forec/FoldScript" << std::endl;
}

std::string usageMsg = "帮助:\tfasm [-i] Source.fasm [-o Executable.fec]";

int main(int argc, char * argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    gflags::SetUsageMessage(usageMsg);
    gflags::SetVersionString(std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR));

    logo();

    std::string sourceFilename = FLAGS_i, targetFilename = FLAGS_o;

    if (argc > 1 && FLAGS_i.empty()) {
        sourceFilename = argv[1];
    } else if (FLAGS_i == "") {
        std::cout << usageMsg << std::endl;
        return 0;
    }

    if (targetFilename.empty())
        targetFilename = "a.fec";

    std::transform(sourceFilename.begin(), sourceFilename.end(), sourceFilename.begin(), ::toupper);
    if (sourceFilename.rfind(FASM_FILE_EXT) == std::string::npos)
        sourceFilename += FASM_FILE_EXT;
    std::transform(targetFilename.begin(), targetFilename.end(), targetFilename.begin(), ::toupper);
    if (targetFilename.rfind(EXEC_FILE_EXT) == std::string::npos)
        targetFilename += EXEC_FILE_EXT;

    Parser * parser = new Parser();
    if (!parser->initFromFile(sourceFilename)) {
        std::cerr << "失败: 无法读取源文件，请检查文件 \"" << sourceFilename
                  << "\" 是否存在，或当前用户是否对该文件有读权限。" << std::endl;
        return 0;
    }

    std::cout << "正在汇编文件 " << sourceFilename << "..." << std::endl;
    parser->assemble();

    parser->setExecFilename(targetFilename);

    std::cout << "汇编完成，正在导出可执行文件到 " << targetFilename << "..." << std::endl;
    parser->exportFEC();

    std::cout << parser->status2string();

    delete parser;

    return 0;
}