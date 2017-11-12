#include <algorithm>
#include <string>
#include <iostream>
#include <gflags/gflags.h>
#include "macro.h"
#include "parser.h"

DEFINE_string(i, "", "Fold-Script-Assemble source file to be assembled");
DEFINE_string(o, "a.fec", "Output filename after assembled.");

void logo() {
    std::cout << "Fold-Script ASM Version " << VERSION_MAJOR
              << "." << VERSION_MINOR << std::endl
              << "Source in https://github.com/forec/FoldScript" << std::endl
              << std::endl;
}

void usage() {
    std::cout << "Usage:\t FASM -i Source.FASM [-o Executable.FEC]" << std::endl
              << std::endl
              << "\t- File extensions are not required." << std::endl
              << "\t- Optional executable output file." << std::endl;
}

int main(int argc, char * argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    logo();

    if (FLAGS_i == "") {
        usage();
        return 0;
    }

    std::string sourceFilename = FLAGS_i;
    std::transform(sourceFilename.begin(), sourceFilename.end(), sourceFilename.begin(), ::toupper);
    if (sourceFilename.rfind(FASM_FILE_EXT) == std::string::npos)
        sourceFilename += FASM_FILE_EXT;
    std::string targetFilename = FLAGS_o;
    std::transform(targetFilename.begin(), targetFilename.end(), targetFilename.begin(), ::toupper);
    if (targetFilename.rfind(EXEC_FILE_EXT) == std::string::npos)
        targetFilename += EXEC_FILE_EXT;

    Parser * parser = new Parser();
    if (!parser->initFromFile(sourceFilename)) {
        std::cerr << "无法读取源文件，请检查文件" << sourceFilename
                  << "是否存在，当前用户是否对该文件有读权限。" << std::endl;
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