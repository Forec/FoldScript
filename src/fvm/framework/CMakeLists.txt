set(
        SRC_LIST
        rstack.cpp
)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fvm/framework
)

add_library(fvm-framework STATIC ${SRC_LIST})
