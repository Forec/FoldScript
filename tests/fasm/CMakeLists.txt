cmake_minimum_required(VERSION 3.8)

include(CTest)
enable_testing()

set(
        test_SRCS
        test_utils/test_utils.cpp
        test_framework/test_function.cpp
        test_framework/test_symbol.cpp
        test_framework/test_label.cpp
        test_framework/test_instrlookup.cpp
        test_framework/test_source.cpp
        test_component/test_lexer.cpp
        test_framework/test_instr_table.cpp
        test_component/test_parser.cpp
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
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

add_executable(test-fasm test_fasm.cpp ${test_SRCS})

# add all library below
target_link_libraries(
        test-fasm
        fasm-utils
        fasm-framework
        fasm-component
)

target_link_libraries(test-fasm /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)
target_link_libraries(test-fasm /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a)
