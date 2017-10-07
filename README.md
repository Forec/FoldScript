# Fold Script

* **当前开发进度**：FASM 汇编器

# 安装

## 下载二进制版本
* 暂无 Release 版本

## 从源码安装
* Fold Script 的编译、汇编、链接及虚拟机使用 C++ 14 标准
* 第三方库：[gflags](https://github.com/gflags/gflags)、[googleTest](https://github.com/google/googletest)
* 编译
  ```shell
  git clone https://github.com/Forec/FoldScript.git
  cd FoldScript
  mkdir build && cd build
  cmake ..
  make
  ```
* 编译完成后运行测试
  ```shell
  cd bin
  ./runUnitTests
  ```

# 许可证
本仓库中的代码均受仓库中 [LICENSE](https://github.com/forec/FoldScript/blob/master/LICENSE) 声明的许可证保护。
