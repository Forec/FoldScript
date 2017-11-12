cmake_minimum_required(VERSION 3.8)

include(CTest)
enable_testing()

# Enable the following part if GoogleTest is not configured global.
#set(REPO ${PROJECT_SOURCE_DIR}/.repo)
#include(${REPO}/DownloadProject/DownloadProject.cmake)
#download_project(
#        PROJ                googletest
#        GIT_REPOSITORY      https://github.com/google/googletest.git
#        GIT_TAG             master
#        UPDATE_DISCONNECTED 1
#)
#add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

set(
        test_SRCS
        ../gtest.cpp
        test_utils/test_utils.cpp
        test_framework/test_function.cpp
        test_framework/test_symbol.cpp
        test_framework/test_label.cpp
        test_framework/test_instrlookup.cpp
        test_framework/test_source.cpp
        test_component/test_lexer.cpp
        test_framework/test_instr_table.cpp
        test_component/test_parser.cpp

        ../fvm/test_framework/test_script.cpp
)

include_directories(
        /usr/local/include
        ../../include/fasm/utils
        ../../include/fasm/framework
        ../../include/fasm/framework/function
        ../../include/fasm/framework/symbol
        ../../include/fasm/framework/label
        ../../include/fasm/framework/instruction
        ../../include/fasm/component

        ../../include/fvm/utils
        ../../include/fvm/framework
        ../../include/fvm/framework/instruction
        ../../include/fvm/vm
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

add_executable(runUnitTests ../gtest.cpp ${test_SRCS})

# add all library below
target_link_libraries(
        runUnitTests
        fasm-utils
        fasm-framework
        fasm-component
        fvm-framework
        fvm-utils
        fvm-vm
)

target_link_libraries(runUnitTests /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)
target_link_libraries(runUnitTests /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a)
