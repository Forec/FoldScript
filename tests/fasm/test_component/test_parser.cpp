//
// Created by 王耀 on 2017/10/30.
//

#include <gtest/gtest.h>
#include "parser.h"

std::string SourceCode = \
        "setstacksize 20 ;; 设置堆栈大小                \n" \
        "Var Array[256]  ;; 声明数组 Array             \n" \
        "Var X;          ;; 声明全局变量 X              \n" \
        "Func MyAdd {    ;; 声明函数 MyAdd，将两个参数相加\n" \
        "  Param X2      ;; 声明参数 X2                  \n" \
        "  Param Y       ;; 声明参数 Y                  \n" \
        "  Var Sum       ;; 定义局部变量 Sum             \n" \
        "  Mov Sum, X2   ;; 将 X2 移至 Sum              \n" \
        "  Add Sum, Y    ;; 将 X2 与 Y 相加             \n" \
        "  Mov _RetVar, Sum ;; 将结果存储在返回值寄存器中  \n" \
        "  ;; Ret 指令会自动添加在这一行                  \n" \
        "}                                             \n" \
        "Func _Main {    ;; 主函数                      \n" \
        "  Var MySum     ;; 声明局部变量 MySum           \n" \
        "  Var Y         ;; 声明局部变量 Y               \n" \
        "  Mov Y, 10     ;; 给 Y 赋值 10                \n" \
        "  Mov X, 20     ;; 给 X 赋值 20                \n" \
        "  Push Y        ;; 压入参数 Y                  \n" \
        "  Push X        ;; 压入参数 X                  \n" \
        "  Call MyAdd    ;; 调用函数 MyAdd              \n" \
        "  Mov MySum, _RetVar   ;; 将结果压入 MySum     \n" \
        "  Mov Array[0], \"Hello, the result is \"     \n" \
        "  Mov Array[1], MySum                         \n" \
        "  Push Array[0] ;; 将待打印数组地址压入堆栈      \n" \
        "  Push Array[1] ;; 将待打印数组地址压入堆栈      \n" \
        "  Push 2        ;; 将待打印元素个数压入堆栈      \n" \
        "  CallHost Print;; 系统调用，打印结果           \n" \
        "}                                             \n";

std::string StandardStatus = \
        "default.XSE 汇编结束\n共处理 28 行源码\n" \
        "    堆栈大小: 20\n    指令数量: 15\n    变量数量: 6\n    数组数量: 1\n" \
        "    全局变量: 2\n    字符串表: 1\n    行标签数: 0\n    系统调用: 1\n" \
        "    函数定义: 2\n    主函数存在: 主函数下标为 1\n";

TEST(ParserTest, ParserTest_STATUS_Test) {
    Parser parser;
    parser.initFromString(SourceCode);
    parser.assemble();
    std::string status = parser.statusToString();
    EXPECT_EQ(StandardStatus, status);
}