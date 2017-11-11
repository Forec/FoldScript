set(
        SRC_LIST
        utils.cpp
)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/fvm/utils
)

add_library(fvm-utils STATIC ${SRC_LIST})
