set(
        SRC_LIST
        strtable.cpp
        source.cpp
        function/functable.cpp
        function/funcnode.cpp
        symbol/symtable.cpp
        symbol/symnode.cpp
        label/labnode.cpp
        label/labtable.cpp
        instruction/instr.cpp
        instruction/inslktable.cpp
        instruction/instrlookup.cpp
        instruction/instable.cpp)


include_directories(
        ${PROJECT_SOURCE_DIR}/include/fasm/utils
        ${PROJECT_SOURCE_DIR}/include/fasm/framework
        ${PROJECT_SOURCE_DIR}/include/fasm/framework/function
        ${PROJECT_SOURCE_DIR}/include/fasm/framework/symbol
        ${PROJECT_SOURCE_DIR}/include/fasm/framework/label
        ${PROJECT_SOURCE_DIR}/include/fasm/framework/instruction
)

add_library(fasm-framework STATIC ${SRC_LIST})
