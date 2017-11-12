//
// Created by 王耀 on 2017/11/12.
//

#include <gtest/gtest.h>
#include <string>
#include "macro.h"
#include "script.h"

std::string fecPath = "../../example/fec/ADD.FEC";

std::string standardStatus =
        "\"" + fecPath + "\" 加载成功!\n    文件版本: " +
        std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) +
        "\n    堆栈大小: 20\n    全局空间: 257\n    函数定义: 2" +
        "\n    指令长度: 17\n    系统调用: 1\n主函数存在, 主函数下标为 1\n";

TEST(ScriptTest, ScriptTest_LOAD_Test) {
    Script script;
    script.setExecutableFile(fecPath);
    EXPECT_EQ(LOAD_OK, script.loadHeader());
    EXPECT_TRUE(script.loadCode());
    EXPECT_EQ(standardStatus, script.status2string());
}