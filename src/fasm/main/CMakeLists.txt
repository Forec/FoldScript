set(SRC_LIST main.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fasm/utils
        ${PROJECT_SOURCE_DIR}/include/fasm/framework
        ${PROJECT_SOURCE_DIR}/include/fasm/lexer
)

link_directories(
        ${LIBRARY_OUTPUT_PATH}
)

find_package(gflags REQUIRED)

add_executable(FASM ${SRC_LIST})

target_link_libraries(
        FASM
        fasm-utils
        fasm-framework
        fasm-lexer
        gflags
)