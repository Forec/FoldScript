cmake_minimum_required(VERSION 3.8)

include(CTest)
enable_testing()

set(
        test_SRCS
        test_framework/test_script.cpp
        test_framework/test_instr.cpp
        test_framework/test_instable.cpp
        test_framework/test_rstack.cpp
        test_framework/test_value.cpp
        test_framework/test_functable.cpp
        test_framework/test_hostapi.cpp
        test_utils/test_utils.cpp
)

include_directories(
        /usr/local/include
        ../../include/fvm/utils
        ../../include/fvm/framework
        ../../include/fvm/framework/instruction
        ../../include/fvm/vm
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

add_executable(test-fvm test_fvm.cpp ${test_SRCS})

# add all library below
target_link_libraries(
        test-fvm
        fvm-framework
        fvm-utils
        fvm-vm
)

target_link_libraries(test-fvm /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)
target_link_libraries(test-fvm /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a)
