set(
        SRC_LIST
        lexer.cpp
)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fasm/component
        ${PROJECT_SOURCE_DIR}/include/fasm/framework
        ${PROJECT_SOURCE_DIR}/include/fasm/utils
)

add_library(fasm-component STATIC ${SRC_LIST})
