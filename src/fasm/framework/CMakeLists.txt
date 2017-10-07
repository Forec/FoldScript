set(
        SRC_LIST
        instr.cpp
        strtable.cpp
        function/functable.cpp
        function/funcnode.cpp
        symbol/symtable.cpp
        symbol/symnode.cpp)


include_directories(
        ${PROJECT_SOURCE_DIR}/include/fasm/framework
        ${PROJECT_SOURCE_DIR}/include/fasm/framework/function
        ${PROJECT_SOURCE_DIR}/include/fasm/framework/symbol
)

add_library(fasm-framework STATIC ${SRC_LIST})
