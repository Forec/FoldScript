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
        fasm/test_utils/test_utils.cpp
        fasm/test_framework/test_function.cpp
        fasm/test_framework/test_symbol.cpp
        fasm/test_framework/test_label.cpp
        fasm/test_framework/test_instrlookup.cpp
        fasm/test_framework/test_source.cpp
        fasm/test_component/test_lexer.cpp
        fasm/test_framework/test_instr_table.cpp
        fasm/test_component/test_parser.cpp
)

include_directories(
        /usr/local/include
        ../include/fasm/utils
        ../include/fasm/framework
        ../include/fasm/framework/function
        ../include/fasm/framework/symbol
        ../include/fasm/framework/label
        ../include/fasm/framework/instruction
        ../include/fasm/component
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

add_executable(runUnitTests gtest.cpp ${test_SRCS})

# add all library below
target_link_libraries(
        runUnitTests
        fasm-utils
        fasm-framework
        fasm-component
        fvm-utils
        fvm-framework
        fvm-vm
)

target_link_libraries(runUnitTests /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)
target_link_libraries(runUnitTests /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a)
