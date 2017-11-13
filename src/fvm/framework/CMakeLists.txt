set(
        SRC_LIST
        rstack.cpp
        instruction/instr.cpp
        instruction/instable.cpp
        functable.cpp
        hostapi.cpp
        value.cpp
        script.cpp
)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fvm/utils
        ${PROJECT_SOURCE_DIR}/include/fvm/framework
        ${PROJECT_SOURCE_DIR}/include/fvm/framework/instruction
)

add_library(fvm-framework STATIC ${SRC_LIST})
